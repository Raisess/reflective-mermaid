#include <iostream>
#include "Utils/File.h"
#include "Lexer.h"
#include "Parser.h"
#include "ParserListener.h"

int main(int argc, char* argv[]) {
  auto* input_file = new Utils::File("./public/input.prisma");

  std::vector<Token> tokens = Lexer::tokenizer(input_file->read());

  std::ostringstream ostr;
  for (int i = 0; i < tokens.size(); i++) {
    ostr << i << ": (" << tokens[i].type << ") " << tokens[i].value << "\n";
  }

  auto* tokenizer_output_file = new Utils::File("./public/tokenizer_output.txt");
  tokenizer_output_file->write(ostr.str());

  auto* parser = new Parser(tokens);
  std::vector<Statement> stmts = parser->parse();

  for (Statement stmt : stmts) {
    std::cout << stmt.id << ": (" << stmt.type << ") " << stmt.constructor << std::endl;

    for (PropertyStatement pstmt : stmt.properties) {
      std::cout << "---> " << pstmt.type << ": " << pstmt.constructor << std::endl;
    }
  }

  auto* transpiler = new ParserListener(stmts);
  std::string final_output = transpiler->transpile();

  auto* output_file = new Utils::File("./public/output.mmd");
  output_file->write(final_output);

  std::cout << final_output << std::endl;

  return 0;
}
