#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <optional>
#include <iterator>
#include <iostream>
#include <fstream>
#include "token.hpp" 

void interpret_to_cpp(const std::vector<Token>& tokens, const std::string& output_path = "output.cpp");     

#endif  
