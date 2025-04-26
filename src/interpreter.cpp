#include "../include/interpreter.hpp"

void interpret_to_cpp(const std::vector<Token>& tokens, const std::string& output_path){
    std::ofstream out(output_path);
    out << "#include <iostream>\n\nint main(){\n";

    for (const auto& token : tokens) {                       // TODO: implement a switch statement over the type enum
        if (token.type == TokenType::t_PRINT_ASCII) {        // ASCII Print handler
            std::istringstream iss(token.value.value());
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
        
            out << "    std::cout << \"" << result << "\";\n";
        }else if (token.type == TokenType::t_RETURN) {       // Return token handler
            out << "    return " << token.value.value() << ";\n";
        }
    }

    out << "}\n";
    out.close();
}