#include "Lexer.h"

int main(int argc, char* argv[]) {
  std::string str = 
    "model Test {\n"
    " id Int @db.Int @id @unique @default(autoincrement())\n"
    " name String @db.VarChar(36)\n"
    "}\n";

  std::vector<Token> tokens = Lexer::tokenizer(str);

  for (int i = 0; i < tokens.size(); i++) {
    std::cout << i << ": (" << tokens[i].type << ") " << tokens[i].value << std::endl;
  }

  return 0;
}
