#include "../include/tokenizer.hpp"

std::vector<Token> tokenize(const std::string& data) {       // Create tokens using the input code string
    std::vector<Token> tokens;
    std::istringstream stream(data);
    std::string line;

    int line_num = 1;
    while (std::getline(stream, line)) {

        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {       // Ignore empty lines
            line_num++;
            continue;
        }

        std::istringstream line_stream(line);
        std::string opcode;
        line_stream >> opcode;

        Token token;                                                // TODO: Make the comment-case-check first so that after that you know you have an integer,
                                                                    // so that you can turn it to an int and then use a switch
        if (opcode == "0") {                                        // Return opcode case
            token.type = TokenType::t_RETURN; token.min_args = 1; token.max_args = 1;
        } else if (opcode == "1") {                                 // Character print opcode case
            token.type = TokenType::t_PRINT_ASCII;  token.min_args = 1; token.max_args = std::nullopt;                
        } else if (opcode.at(0) == '@'){                            // Comment opcode case, ignore line
            line_num++;
            continue;
        }
        else {
            std::cerr << "Invalid or unknown operand in line " << line_num << ": \"" << opcode << "\" " << std::endl;
            exit(EXIT_FAILURE);
            continue;
        }

        token.line_number = line_num;

        std::string value;
        std::getline(line_stream, value); 
        if (!value.empty() && value[0] == ' ') value.erase(0, 1); 
        token.value = value;

        tokens.push_back(token);
        line_num++;
    }

    return tokens;
}