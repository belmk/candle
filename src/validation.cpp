#include "../include/validation.hpp"

void validate_tokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        if (token.type == TokenType::t_PRINT_ASCII) {                       // ASCII value range validation
            std::istringstream iss(token.value.value());
            std::string ascii_code;
            while (iss >> ascii_code) {
                int val = std::stoi(ascii_code);
                if (val < 0 || val > 127) {
                    std::cerr << "Error on line " << token.line_number
                              << ": ASCII value out of range (0-127): " << val << '\n';
                    exit(EXIT_FAILURE);
                }
            }
        }

        if (token.value.has_value()) {                                      // Argument number validation 
            std::istringstream iss(token.value.value());
        
            int count = std::distance(std::istream_iterator<std::string>(iss),
                                      std::istream_iterator<std::string>());
        
            if (token.min_args.has_value() && count < token.min_args.value()) {
                std::cerr << "Error on line " << token.line_number
                          << ": Expected at least " << token.min_args.value()
                          << " arguments, got " << count << ".\n";
                exit(EXIT_FAILURE);
            }
            if (token.max_args.has_value() && count > token.max_args.value()) {
                std::cerr << "Error on line " << token.line_number
                          << ": Expected at most " << token.max_args.value()
                          << " arguments, got " << count << ".\n";
                exit(EXIT_FAILURE);
            }
        }
    }
}
