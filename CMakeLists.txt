cmake_minimum_required(VERSION 3.16)
project(mycompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Bison
BISON_TARGET(
    Parser
    src/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
)

# Flex
FLEX_TARGET(
    Lexer
    src/lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

# Ensure Flex runs after Bison (for token headers)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_executable(main
    main.cpp
    src/visitor.cpp
    src/semerror.cpp
    src/typecheck.cpp
    src/flowcheck.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Lexer_OUTPUTS}
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    src
)

target_compile_options(main PRIVATE -g)