#include "../include/utils.hpp"

std::string parse_file(char* &path){                         // Create a string representation of the input code
    std::string code_content;
    std::fstream input(path, std::ios::in);
    std::stringstream code;
    code << input.rdbuf();
    input.close();

    code_content = code.str();                         

    return code_content;
}