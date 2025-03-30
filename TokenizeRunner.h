#pragma once

#include <filesystem>
#include <iostream>

#include "lib/Tokenizer/Tokenizer.h"

namespace fs = std::filesystem;

class TokenizeRunner {
public:

    void Run(fs::path input_file_path, fs::path raw_output_file_path, fs::path output_file_path);
private:
    const char* MmapFile(const char* file_path, size_t file_size);
};
