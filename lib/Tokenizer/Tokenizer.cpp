#include "Tokenizer.h"
#include "lib/LSCommunicator/LSCommunicator.h"

#include <stdexcept>
#include <cctype>

TokenInfo::TokenInfo(TokenId id, uint32_t begin_pos) : id_(id), begin_pos_(begin_pos) {
}

TokenId TokenInfo::GetId() const {
    return id_;
}

uint32_t TokenInfo::GetBegin() const {
    return begin_pos_;
}

Tokenizer::Tokenizer(std::string_view input_data,
    const std::string& path_to_input_file,
    const std::string& raw_output_file_path)
    : input_file_data_(input_data) {
    parsed_tokens_ = LSCommunicator::GetParseResult(path_to_input_file, raw_output_file_path);
}

std::optional<TokenType> Tokenizer::GetSymbol(std::string_view input, size_t pos) {
    if (pos >= input.size()) {
        return std::nullopt;
    }
    unsigned char byte = input[pos];
    if (!(byte >> 7)) {
        return input.substr(pos, 1);
    }
    unsigned char octets = 2;
    unsigned char mask = 1 << 5;
    while (byte & mask) {
        ++octets;
        mask >>= 1;
        if (octets > 4) {
            throw std::invalid_argument("not a utf-8 file: invalid byte sequence");
        }
    }
    size_t start = pos;
    while (--octets) {
        if (++pos >= input.size()) {
            throw std::invalid_argument("not a utf-8 file: unexpected EOF");
        }
        byte = input[pos];
        if ((byte & (0b11 << 6)) != (1 << 7)) {
            throw std::invalid_argument("not a utf-8 file: invalid byte sequence");
        }
    }
    return input.substr(start, pos - start + 1);
}

std::vector<TokenInfo> Tokenizer::GetTokensInfo() {
    return GetTokenInfos(input_file_data_);
}

TokenType Tokenizer::Decode(const TokenInfo& code) {
    return GetToken(input_file_data_, code.GetBegin()).value();
}

std::vector<TokenInfo> Tokenizer::GetTokenInfos(std::string_view input) {
    std::vector<TokenInfo> ids;
    size_t pos = 0;
    while (std::optional<TokenType> token = GetToken(input, pos)) {
        size_t hash_val = GetHash(token.value());
        while (hash2id_.contains(hash_val) &&
               !IsEqual(tokens_[hash2id_[hash_val]], token.value())) {
            ++hash_val;
        }
        if (!hash2id_.contains(hash_val)) {
            hash2id_[hash_val] = last_code_++;
            tokens_.push_back(token.value());
        }
        ids.emplace_back(hash2id_[hash_val], pos);
        pos += token.value().size();
    }
    return ids;
}

bool Tokenizer::IsEqual(TokenType lhs, TokenType rhs) {
    return lhs == rhs;
}

size_t Tokenizer::GetHash(TokenType token) {
    return std::hash<TokenType>{}(token);
}

std::optional<TokenType> Tokenizer::GetToken(std::string_view input, size_t pos) {
    if (pos >= input.size()) {
        return std::nullopt;
    }
    size_t start = pos;
    while (std::optional<TokenType> symbol = GetSymbol(input, pos)) {
        if ((symbol.value().size() == 1 && symbol.value() == "\n") ||
            (parsed_tokens_.contains(pos) && start != pos)) {
            break;
        }
        pos += symbol.value().size();
    }
    if (pos == start) {
        return input.substr(start, 1);
    }
    return input.substr(start, pos - start);
}

std::unique_ptr<Tokenizer> GetTokenizer(std::string_view input_data,
    const std::string& path_to_input_file,
    const std::string& raw_output_file_path) {
    return std::make_unique<Tokenizer>(input_data,
        path_to_input_file,
        raw_output_file_path);
}
