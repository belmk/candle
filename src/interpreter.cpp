#include "../include/interpreter.hpp"

void handle_ascii_token(const Token& t, std::ofstream& output);
void handle_int_stack_arithmetic(const Token& t, std::ofstream& output);

void interpret_to_cpp(const std::vector<Token>& tokens, const std::string& output_path){
    std::ofstream out(output_path);
    out << "#include <iostream>\n#include <vector>\n\nint main(){\n";
    out << "\tstd::vector<int> integer_stack;\n";

    for (const auto& token : tokens) {                       
        switch(token.type){
            
            case TokenType::t_PRINT_ASCII:{

                handle_ascii_token(token, out);
                break;
            }

            case TokenType::t_USER_INPUT:{
                out << "\t{\n\tint _temp;\n\tstd::cin >> _temp;\n\tinteger_stack.push_back(_temp);\n\t}\n";
                break;
            }

            case TokenType::t_INT_STACK_PEEK:{
                out << "\tstd::cout << integer_stack.back();\n";
                break;
            }

            case TokenType::t_INT_STACK_ARITHMETIC:{
                handle_int_stack_arithmetic(token, out);
                break;
            }

            case TokenType::t_RETURN:{
                out << "\treturn " << token.value.value() << ";\n";
                break;
            }

            default:
                break;
        }
    }

    out << "}\n";
    out.close();
}


void handle_ascii_token(const Token& t, std::ofstream& output){
    std::istringstream iss(t.value.value());
    std::string ascii_code;
    std::string result;

    while (iss >> ascii_code) {
        int val = std::stoi(ascii_code);
        switch (val) {
            case 10: result += "\\n"; break;         // Newline case
            case 9:  result += "\\t"; break;         // Tab case
            default: result += static_cast<char>(val); break;
        }
    }

    output << "    std::cout << \"" << result << "\";\n";
}


void handle_int_stack_arithmetic(const Token& t, std::ofstream& output){
    std::istringstream iss(t.value.value());
    std::string arithmetic_operation_id, pop_operands;
    iss >> arithmetic_operation_id >> pop_operands;             // Extracting the two arguments for the int stack arithmetic

    int operation_opcode = std::stoi(arithmetic_operation_id);
    int pop_opcode = std::stoi(pop_operands);                   // Converting them to integers

    char operation;
    switch(operation_opcode){
        case 0:                                                 // Addition
        operation = '+';
        break;

        case 1:                                                 // Subtraction
        operation = '-';
        break;

        case 2:                                                 // Multiplication
        operation = '*';
        break;

        case 3:                                                 // Division
        operation = '/';
        break;

        case 4:                                                 // Modulo
        operation = '%';
        break;
    }

    output << "\n\tinteger_stack.push_back(integer_stack.at(integer_stack.size() - 1) " << operation << " integer_stack.at(integer_stack.size() - 2));\n";

    if(pop_opcode == 1){
        output << "\tinteger_stack.erase(integer_stack.begin() + (integer_stack.size() - 2));\n";
        output << "\tinteger_stack.erase(integer_stack.begin() + (integer_stack.size() - 2));\n";
    }
}