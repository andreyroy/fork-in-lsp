#pragma once

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <unordered_set>

using TokenId = uint32_t;
using TokenType = std::string_view;

class TokenInfo {
public:
    TokenInfo(TokenId code, uint32_t begin_pos);

    bool operator==(const TokenInfo& rhs) const;

    TokenId GetId() const;
    uint32_t GetBegin() const;

private:
    TokenId id_;
    uint32_t begin_pos_;
};

class Tokenizer {
public:
    Tokenizer(std::string_view input_data,
        const std::string& path_to_input_file,
        const std::string& raw_output_file_path);

    std::vector<TokenInfo> GetTokensInfo();
    TokenType Decode(const TokenInfo& code);
    virtual ~Tokenizer() = default;

private:
    std::optional<TokenType> GetToken(std::string_view input, size_t pos);
    std::optional<TokenType> GetSymbol(std::string_view input, size_t pos);
    std::vector<TokenInfo> GetTokenInfos(std::string_view input);
    bool IsEqual(TokenType lhs, TokenType rhs);
    size_t GetHash(TokenType token);

    std::string_view input_file_data_;
    std::unordered_map<size_t, TokenId> hash2id_;
    std::vector<TokenType> tokens_;
    TokenId last_code_ = 0;
    std::unordered_set<size_t> parsed_tokens_;
    std::string path_to_human_output_;
};

std::unique_ptr<Tokenizer> GetTokenizer(std::string_view input_data,
                                      const std::string& path_to_input_file,
                                      const std::string& raw_output_file_path);

inline bool TokenInfo::operator==(const TokenInfo& rhs) const {
    return id_ == rhs.id_;
}
