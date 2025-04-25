#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <string>
#include <algorithm>

enum class TokenType {t_RETURN, t_INTEGER, t_PRINT_ASCII, t_PRINT_INTEGER};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};


std::string parse_file(char*& path);                                                                        // Reads the file and turns it into a string
std::vector<Token> tokenize(const std::string& data);                                                       // Creates tokens based on the code from the file
void print_tokens(const std::vector<Token>& tokens);                                                        // Prints the tokens to the terminal (debug only)
void interpret_to_cpp(const std::vector<Token>& tokens, const std::string& output_path = "output.cpp");     // Creates a .cpp file that gets compiled into the final .exe




int main(int argc, char** argv){

    if(argc != 2) {
        std::cerr << "---ERROR---\nInvalid command line arguments!\nCorrect usage: ./numlang.exe file.cndl";
        return -1;
    }

    std::string data = parse_file(argv[1]);

    std::vector<Token> tokens = tokenize(data);

    print_tokens(tokens);                           // Useful for debugging

    interpret_to_cpp(tokens);

    int compilation_result = system("g++ output.cpp -o output");
    if(compilation_result != 0){
        std::cerr << "Compilation failed!\n";
        return 1;
    }

    std::cin.get();
    return 0;
}





std::string parse_file(char* &path){                         // Create a string representation of the input code
    std::string code_content;
    std::fstream input(path, std::ios::in);
    std::stringstream code;
    code << input.rdbuf();
    input.close();

    code_content = code.str();                         

    return code_content;
}

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

        Token token;

        if (opcode == "0") {                                        // Return opcode case
            token.type = TokenType::t_RETURN;
        } else if (opcode == "1") {                                 // Character print opcode case
            token.type = TokenType::t_PRINT_ASCII;                  
        } else if (opcode.at(0) == '@'){                            // Comment opcode case, ignore line
            line_num++;
            continue;
        }
        else {
            std::cerr << "Invalid or unknown operand in line " << line_num << ": \"" << opcode << "\" " <<std::endl;
            exit(EXIT_FAILURE);
            continue;
        }

        std::string value;
        std::getline(line_stream, value); 
        if (!value.empty() && value[0] == ' ') value.erase(0, 1); 
        token.value = value;

        tokens.push_back(token);
        line_num++;
    }

    return tokens;
}


void interpret_to_cpp(const std::vector<Token>& tokens, const std::string& output_path){
    std::ofstream out(output_path);
    out << "#include <iostream>\n\nint main(){\n";

    for (const auto& token : tokens) {
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




void print_tokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::string type_str;

        switch (token.type) {
            case TokenType::t_RETURN:      type_str = "RETURN"; break;
            case TokenType::t_PRINT_ASCII:       type_str = "PRINT_ASCII"; break;
            case TokenType::t_PRINT_INTEGER:       type_str = "PRINT_INTEGER"; break;
            case TokenType::t_INTEGER:   type_str = "INTEGER"; break;
            default:                       type_str = "UNKNOWN"; break;
        }

        std::cout << "Token: " << type_str;
        if (token.value.has_value()) {
            std::cout << ", Value: \"" << token.value.value() << "\"";
        }
        std::cout << '\n';
    }
}

