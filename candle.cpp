#include <iostream>
#include "include/token.hpp"
#include "include/validation.hpp"
#include "include/utils.hpp"
#include "include/tokenizer.hpp"
#include "include/interpreter.hpp"

void print_tokens(const std::vector<Token>& tokens);                                                        // Prints the tokens to the terminal (debug only)

int main(int argc, char** argv){

    if(argc != 2) {
        std::cerr << "---ERROR---\nInvalid command line arguments!\nCorrect usage: ./candle.exe file.cndl";
        return -1;
    }

    std::string data = parse_file(argv[1]);

    std::vector<Token> tokens = tokenize(data);                          // Create a vector of tokens with values from the code text

    print_tokens(tokens);                                                // Useful for debugging

    validate_tokens(tokens);                                             // Make sure the tokens are used correctly, display error messages otherwise

    interpret_to_cpp(tokens);                                            // If no error in validation, create a C++ intermediate file from the tokens 

    int compilation_result = system("g++ output.cpp -o output");         // Compile the intermediate C++ file using g++
    if(compilation_result != 0){
        std::cerr << "Compilation failed!\n";
        return 1;
    }

    if (std::remove("output.cpp") != 0) {                                // If compilation succeeded, remove the intermediate file to avoid clutter
        std::cerr << "Failed to delete temporary file output.cpp!\n";
    }

    //system("output.exe");

    return 0;
}








void print_tokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::string type_str;

        switch (token.type) {
            case TokenType::t_RETURN:            type_str = "RETURN"; break;
            case TokenType::t_PRINT_ASCII:       type_str = "PRINT_ASCII"; break;
            default:                             type_str = "UNKNOWN"; break;
        }

        std::cout << "Token: " << type_str;
        if (token.value.has_value()) {
            std::cout << ", Value: \"" << token.value.value() << "\"";
        }
        std::cout << ", Line: " << token.line_number;
        std::cout << '\n';
    }
}

