#include <iostream>
#include "File.h"
#include "Lexer.h"
#include "Parser.h"

#define DEBUG 1

int main(int argc, char* argv[]) {
  File* input_file = new File("./public/input.prisma");

  std::vector<Token> tokens = Lexer::tokenizer(input_file->read());

  if (DEBUG) {
    std::string str;
    for (int i = 0; i < tokens.size(); i++) {
      str.append(std::to_string(i));
      str.append(": (");
      str.append(tokens[i].type);
      str.append(") ");
      str.append(tokens[i].value);
      str.append("\n");
    }

    File* tokenizer_output_file = new File("./public/tokenizer_output.txt");
    tokenizer_output_file->write(str);
  }

  Parser* parser = new Parser(tokens);
  std::vector<Statement> stmts = parser->parse();

  for (Statement stmt : stmts) {
    std::cout << stmt.id << ": (" << stmt.type << ") " << stmt.constructor << std::endl;
    //std::cout << stmt.id << ": (" << stmt.type << ") " << stmt.constructor << " | value: " << stmt.value << std::endl;

    for (PropertyStatement pstmt : stmt.properties) {
      std::cout << "---> " << pstmt.constructor << ": " << pstmt.type << std::endl;
    }
  }

  return 0;
}
