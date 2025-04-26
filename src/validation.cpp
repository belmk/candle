#include "../include/validation.hpp"

void numeric_value_validation(const Token& t);                      // Checks if all of the tokens have strictly numerical arguments
void ascii_range_validation(const Token& t);                        // Checks if the ASCII values appear in the correct range
void arg_num_validation(const Token& t);                            // Checks if each opcode got an expected number of arguments
void integer_stack_validation(const std::vector<Token>& tokens);    // Checks for invalid operations on the integer stack (popping empty stack, etc.)


void validate_tokens(const std::vector<Token>& tokens) {            
    for (const auto& token : tokens) {                              
        numeric_value_validation(token);
        ascii_range_validation(token);
        arg_num_validation(token);
    }

    integer_stack_validation(tokens);
}

void numeric_value_validation(const Token& t){
    if(t.value.has_value()){
    for (const auto& c : t.value.value()){
        if(!(std::isdigit(c) || std::isspace(c))){
            std::cerr << "Error on line " << t.line_number
                      << ": Invalid non-numeric argument " << '\n';
        }
    }
    }
}


void ascii_range_validation(const Token& t){                         // ASCII value range validation
    if (t.type == TokenType::t_PRINT_ASCII) {                       
        std::istringstream iss(t.value.value());
        std::string ascii_code;
        while (iss >> ascii_code) {
            int val = std::stoi(ascii_code);
            if (val < 0 || val > 127) {
                std::cerr << "Error on line " << t.line_number
                          << ": ASCII value out of range (0-127): " << val << '\n';
                exit(EXIT_FAILURE);
            }
        }
    }
}


void arg_num_validation(const Token& t){                            // Argument number validation
    if (t.value.has_value()) {                                       
        std::istringstream iss(t.value.value());
    
        int count = std::distance(std::istream_iterator<std::string>(iss),
                                  std::istream_iterator<std::string>());
    
        if (t.min_args.has_value() && count < t.min_args.value()) {
            std::cerr << "Error on line " << t.line_number
                      << ": Expected at least " << t.min_args.value()
                      << " arguments, got " << count << ".\n";
            exit(EXIT_FAILURE);
        }
        if (t.max_args.has_value() && count > t.max_args.value()) {
            std::cerr << "Error on line " << t.line_number
                      << ": Expected at most " << t.max_args.value()
                      << " arguments, got " << count << ".\n";
            exit(EXIT_FAILURE);
        }
    }
}

void integer_stack_validation(const std::vector<Token>& tokens){    // Stack operations validation
    int stack_var_counter = 0;
    for(const auto& t : tokens){
        if(t.type == TokenType::t_USER_INPUT){                      // Increase var counter by 1 for t_USER_INPUT token
            stack_var_counter++;
        }

        else if(t.type == TokenType::t_INT_STACK_ARITHMETIC){       // Check the t_INT_STACK_ARITHMETIC token for the argument of the operation
            std::istringstream iss(t.value.value());
            std::string _temp, arg;
            iss >> _temp >> arg;                                    // _temp var only used to get the value of the second argument from the iss

            if(std::stoi(arg) == 1){                                // If the operation will pop the operands after it's done, decrement the var counter 
                stack_var_counter--;
            }
            else{                                                   // If the operation will NOT pop the operands after it's done, increment the var counter
                stack_var_counter++;
            }

            if(stack_var_counter < 0){                                  // Terminate the compilation if the var counter were to fall below 0 at any point
                std::cerr << "Error on line " << t.line_number << ":\n"
                          << "Insufficient stack variables for this operation!" << '\n';
                exit(EXIT_FAILURE);
            }
        }
        
    }
}

