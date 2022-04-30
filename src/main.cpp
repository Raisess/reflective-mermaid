#include "Lexer.h"

int main(int argc, char* argv[]) {
  std::string str = "string test = 'hello'\nint x = 1\nint y = 1\nx + y\n";

  std::vector<Token> tokens = Lexer::tokenizer(str);

  for (int i = 0; i < tokens.size(); i++) {
    std::cout << i << ": (" << tokens[i].type << ") " << tokens[i].value << std::endl;
  }

  return 0;
}
