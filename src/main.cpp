#include <iostream>
#include "Utils/File.h"
#include "Syntax/Lexer.h"
#include "Syntax/Parser.h"
#include "Syntax/ParserListener.h"

int main(int argc, char* argv[]) {
  auto* input_file = new Utils::File("./public/input.prisma");

  std::vector<Syntax::Token> tokens = Syntax::Lexer::tokenizer(input_file->read());

  std::ostringstream ostr;
  for (int i = 0; i < tokens.size(); i++) {
    ostr << i << ": (" << tokens[i].type << ") " << tokens[i].value << "\n";
  }

  auto* tokenizer_output_file = new Utils::File("./public/tokenizer_output.txt");
  tokenizer_output_file->write(ostr.str());

  auto* parser = new Syntax::Parser(tokens);
  std::vector<Syntax::Statement> stmts = parser->parse();

  for (Syntax::Statement stmt : stmts) {
    std::cout << stmt.id << ": (" << stmt.type << ") " << stmt.constructor << std::endl;

    for (Syntax::PropertyStatement pstmt : stmt.properties) {
      std::cout << "---> " << pstmt.type << ": " << pstmt.constructor << std::endl;
    }
  }

  auto* transpiler = new Syntax::ParserListener(stmts);
  std::string final_output = transpiler->transpile();

  auto* output_file = new Utils::File("./public/output.mmd");
  output_file->write(final_output);

  std::cout << final_output << std::endl;

  return 0;
}
