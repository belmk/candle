#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <algorithm>
#include <vector>
#include <sstream>
#include <optional>
#include <iostream>
#include "token.hpp"

std::vector<Token> tokenize(const std::string& data); 

#endif