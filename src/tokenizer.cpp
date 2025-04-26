#include "../include/tokenizer.hpp"

bool is_number(const std::string& s);


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

        if(opcode.at(0) == '@'){                                    // Comment check, increment line num and ignore
            line_num++;
            continue;
        }

        if(!is_number(opcode)){                                     // Checking for a non-numeric value in order to safely use stoi after
            std::cerr << "Invalid operand in line " << line_num << ": \"" << opcode << "\" " << std::endl;
            exit(EXIT_FAILURE);
            continue;
        }

        Token token;                                                
        int opcode_integer = std::stoi(opcode);                                  // We now know its a numeric value so we can use a switch statement

        switch(opcode_integer){

            case 0:                                                 // Return opcode
            token.type = TokenType::t_RETURN;               token.min_args = 1; token.max_args = 1;
            break;

            case 1:                                                 // Print opcode
            token.type = TokenType::t_PRINT_ASCII;          token.min_args = 1; token.max_args = std::nullopt;                
            break;

            case 2:                                                 // User input opcode
            token.type = TokenType::t_USER_INPUT;           token.min_args = 0; token.max_args = 0;
            break;

            case 3:                                                 // Int stack peek opcode
            token.type = TokenType::t_INT_STACK_PEEK;       token.min_args = 0; token.max_args = 0;
            break;

            case 4:                                                 // Int stack arithmetic opcode
            token.type = TokenType::t_INT_STACK_ARITHMETIC; token.min_args = 2; token.max_args = 2;
            break;

            default:                                                // Non-defined opcode
            std::cerr << "Unknown operand in line " << line_num << ": \"" << opcode << "\" " << std::endl;
            exit(EXIT_FAILURE);
            break;
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


bool is_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}