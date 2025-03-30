cmake_minimum_required(VERSION 3.16)
project(fork-in-lsp)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_library(TokenizeRunner STATIC TokenizeRunner.cpp)

add_executable(tokenize main.cpp)

add_subdirectory(lib/LSCommunicator)
add_subdirectory(lib/Tokenizer)

target_link_libraries(tokenize TokenizeRunner TokenizerLib)
