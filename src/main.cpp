#include "Lexer.h"

int main(int argc, char* argv[]) {
  std::string str = 
    "model User {\n"
    " id Int @db.Int @id @unique @default(autoincrement())\n"
    " name String @db.VarChar(36)\n"
    " role_id Int"
    " role Role @relation(fields: [role_id], references: [id], name: \"user_role\")\n"
    "}"
    "model Role {\n"
    " id Int @db.Int @id @unique @default(autoincrement())\n"
    " role_name String @db.VarChar(50)\n"
    "}";

  std::cout << str << std::endl;
  std::cout << "\n============================================\n" << std::endl;

  std::vector<Token> tokens = Lexer::tokenizer(str);

  for (int i = 0; i < tokens.size(); i++) {
    std::cout << i << ": (" << tokens[i].type << ") " << tokens[i].value << std::endl;
  }

  return 0;
}
