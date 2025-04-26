#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <optional>
#include <string>

enum class TokenType { t_RETURN, 
    t_PRINT_ASCII, 
    t_USER_INPUT, 
    t_INT_STACK_PEEK,
    t_INT_STACK_ARITHMETIC
    };

struct Token {
    TokenType type;
    std::optional<std::string> value;
    std::optional<int> max_args;
    std::optional<int> min_args;
    int line_number;
};

#endif  
