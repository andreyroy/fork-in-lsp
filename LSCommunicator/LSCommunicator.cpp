#include "LSCommunicator.h"
#include "json.hpp"

#include <QCoreApplication>
#include <QProcess>
#include <QString>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

namespace LSCommunicator {

constexpr int MAX_RESPONSE_ATTEMPTS = 10;

class ProcessManager {
public:
    explicit ProcessManager(const std::string& executable_path) {
        process_ = std::make_unique<QProcess>();
        process_->start(QString::fromStdString(executable_path), QStringList{});
        if (!process_->waitForStarted()) {
            throw std::runtime_error("Failed to start LSP process");
        }
    }

    ~ProcessManager() {
        if (process_) {
            process_->terminate();
            if (!process_->waitForFinished(3000)) { // Wait up to 3 seconds
                process_->kill(); // Force kill if not terminated
            }
        }
    }

    void sendRequest(const std::string& content, const std::string& header) {
        if (!process_) return;
        process_->write(header.c_str());
        process_->write(content.c_str());
    }

    std::string receiveResponse() {
        if (!process_) return "";
        process_->waitForReadyRead(-1);
        return process_->readAll().toStdString();
    }

private:
    std::unique_ptr<QProcess> process_;
};

class MessageFormatter {
public:
    static std::pair<std::string, std::string> format(const nlohmann::json& content) {
        std::string content_str = content.dump();
        std::stringstream header;
        header << "Content-Length: " << content_str.length() << "\n\n";
        return {header.str(), content_str};
    }

    static nlohmann::json parse(const std::string& response) {
        auto json_start = response.find_first_of('{');
        return (json_start != std::string::npos) 
            ? nlohmann::json::parse(response.substr(json_start))
            : nlohmann::json{};
    }
};

class FileOperations {
public:
    static std::string readContent(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filepath);
        }
        return std::string(std::istreambuf_iterator<char>(file),
                          std::istreambuf_iterator<char>());
    }

    static void writeJSON(const std::string& filepath, const nlohmann::json& data) {
        std::ofstream out(filepath);
        if (!out.is_open()) {
            throw std::runtime_error("Cannot create output file: " + filepath);
        }
        out << data.dump(2) << std::endl;
    }
};

class TokenCalculator {
public:
    static std::vector<size_t> processTokenPositions(const std::vector<size_t>& raw_tokens,
                                                    const std::string& source) {
        std::vector<size_t> positions;
        size_t line_offset = 0;
        size_t current_pos = 0;

        for (size_t i = 0; i < raw_tokens.size(); i += 5) {
            const size_t line = raw_tokens[i];
            const size_t start = raw_tokens[i + 1];
            const size_t length = raw_tokens[i + 2];

            if (line > 0) {
                current_pos = 0;
                for (size_t j = 0; j < line; ++j) {
                    line_offset = source.find('\n', line_offset) + 1;
                }
            }

            const size_t token_start = line_offset + start + current_pos;
            current_pos = start;
            
            positions.push_back(token_start);
            positions.push_back(token_start + length);
        }
        return positions;
    }
};

std::string detectLSPPath([[maybe_unused]] const std::string& filepath) {
    #if defined(__APPLE__) || defined(__MACH__)
        return "clangd";
    #elif __linux__
        return "clangd-12";
    #else
        throw std::runtime_error("Unsupported platform");
    #endif
}

class LSPProtocol {
public:
    static nlohmann::json createInitRequest(const std::string& root_path) {
        return {
            {"jsonrpc", "2.0"},
            {"id", 0},
            {"method", "initialize"},
            {"params", {
                {"processId", 0},
                {"rootUri", root_path},
                {"capabilities", nlohmann::json::array()}
            }}
        };
    }

    static nlohmann::json createOpenRequest(const std::string& uri, 
                                          const std::string& content) {
        return {
            {"jsonrpc", "2.0"},
            {"method", "textDocument/didOpen"},
            {"params", {
                {"textDocument", {
                    {"uri", "file://" + uri},
                    {"languageId", "cpp"},
                    {"version", 0},
                    {"text", content}
                }}
            }}
        };
    }

    static nlohmann::json createTokenRequest(const std::string& uri) {
        return {
            {"jsonrpc", "2.0"},
            {"id", 0},
            {"method", "textDocument/semanticTokens/full"},
            {"params", {
                {"textDocument", {
                    {"uri", "file://" + uri}
                }}
            }}
        };
    }
};

std::vector<size_t> extractTokenData(ProcessManager& process_mgr) {
    for (int attempt = 0; attempt < MAX_RESPONSE_ATTEMPTS; ++attempt) {
        auto response = MessageFormatter::parse(process_mgr.receiveResponse());
        if (response.contains("result") && response["result"].contains("data")) {
            return response["result"]["data"].get<std::vector<size_t>>();
        }
    }
    return {};
}

std::unordered_set<size_t> GetParseResult(const std::string& input_path,
                                          const std::string& output_path) {
    try {
        const auto workspace_path = std::filesystem::current_path().string();
        const auto absolute_path = workspace_path + "/" + input_path;
        const auto source_content = FileOperations::readContent(absolute_path);
        
        ProcessManager process_mgr(detectLSPPath(input_path));

        // Send LSP requests
        auto sendFormattedRequest = [&](const nlohmann::json& request) {
            auto [header, content] = MessageFormatter::format(request);
            process_mgr.sendRequest(content, header);
        };

        sendFormattedRequest(LSPProtocol::createInitRequest(workspace_path));
        sendFormattedRequest(LSPProtocol::createOpenRequest(absolute_path, source_content));
        sendFormattedRequest(LSPProtocol::createTokenRequest(absolute_path));

        // Process response
        auto raw_tokens = extractTokenData(process_mgr);

        // Save results
        nlohmann::json output = {
            {"jsonrpc", "2.0"},
            {"id", 0},
            {"result", {
                {"data", raw_tokens}
            }}
        };
        FileOperations::writeJSON(output_path, output);

        // Calculate token positions
        auto token_positions = TokenCalculator::processTokenPositions(raw_tokens, source_content);
        return {token_positions.begin(), token_positions.end()};
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error during file parsing: " + std::string(e.what()));
    }
}

} // namespace LSCommunicator
