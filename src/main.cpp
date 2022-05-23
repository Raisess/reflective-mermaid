#include <iostream>
#include "File.h"
#include "Lexer.h"
#include "Parser.h"
#include "ParserListener.h"

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

    for (PropertyStatement pstmt : stmt.properties) {
      std::cout << "---> " << pstmt.type << ": " << pstmt.constructor << std::endl;
    }
  }

  ParserListener* transpiler = new ParserListener(stmts);
  std::string final_output = transpiler->transpile();

  std::cout << final_output << std::endl;

  return 0;
}
