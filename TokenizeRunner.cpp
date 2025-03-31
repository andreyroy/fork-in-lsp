#include "TokenizeRunner.h"
#include "json.hpp"

#include <sys/fcntl.h>
#include <sys/mman.h>

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <fstream>

using namespace std::literals::string_literals;

std::string trim(const std::string_view & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}

void TokenizeRunner::Run(fs::path input_file_path, fs::path raw_output_file_path, fs::path output_file_path) {
    fs::file_status input_file_status = fs::status(input_file_path);
    if (input_file_status.type() == fs::file_type::not_found) {
        throw std::invalid_argument("Unexistent file : " + input_file_path.string());
    }
    if (input_file_status.type() != fs::file_type::regular) {
        throw std::invalid_argument("Can't parse non regular file : " +
                                    input_file_path.string());
    }

    size_t input_file_size = fs::file_size(input_file_path);
    const char* input_file_mem;
    try {
        input_file_mem = MmapFile(input_file_path.string().c_str(), input_file_size);
    } catch (std::exception& ex) {
        throw std::runtime_error("mmap: "s + ex.what());
    }

    std::string_view input_file(input_file_mem, input_file_size);

    std::unique_ptr<Tokenizer> tokenizer;
    std::vector<TokenInfo> tokens_info;
    try {
        tokenizer = GetTokenizer(input_file,
                                 input_file_path.string(), raw_output_file_path.string());
        tokens_info = tokenizer->GetTokensInfo();

        std::vector<std::string> tokens;
        for (auto i : tokens_info) {
            const auto token = trim(tokenizer->Decode(i));
            if (token.size() > 0) {
                tokens.push_back(token);
            }
        }
        nlohmann::json output = {
            {"tokens", tokens}
        };
        std::ofstream out(output_file_path.string());
        if (!out.is_open()) {
            throw std::runtime_error("Cannot create output file: " + output_file_path.string());
        }
        out << output.dump(2) << std::endl;
    } catch (const std::exception& ex) {
        throw std::runtime_error("Tokenizer error: "s + ex.what());
    }
}

const char* TokenizeRunner::MmapFile(const char* file_path, size_t file_size) {
    if (file_size == 0) {
        return nullptr;
    }
    int fd = open(file_path, O_RDONLY);
    errno = 0;
    void* mem = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED) {
        throw std::runtime_error(std::strerror(errno));
    }
    return static_cast<const char*>(mem);
}
