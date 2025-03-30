#include <iostream>
#include <string>

#include "argparse.hpp"
#include "TokenizeRunner.h"

using namespace std::literals::string_literals;

int main(int argc, char* argv[]) {
    argparse::ArgumentParser args("tokenize");
    args.add_argument("input").help("input file path");
    args.add_argument("raw_output").help("output file path for raw tokens");
    args.add_argument("output").help("output file path for tokens");
    try {
        args.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << args;
        return 1;
    }

    auto input_file_path = args.get<std::string>("input");
    auto raw_output_file_path = args.get<std::string>("raw_output");
    auto output_file_path = args.get<std::string>("output");
    TokenizeRunner diff_runner;

    try {
        diff_runner.Run(input_file_path, raw_output_file_path, output_file_path);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
    return 0;
}
