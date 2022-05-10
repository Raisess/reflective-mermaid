#include "File.h"
#include "Lexer.h"

int main(int argc, char* argv[]) {
  File* ifile = new File("./public/input.prisma");

  std::string str;
  std::vector<Token> tokens = Lexer::tokenizer(ifile->read());

  for (int i = 0; i < tokens.size(); i++) {
    str.append(std::to_string(i));
    str.append(": (");
    str.append(tokens[i].type);
    str.append(") ");
    str.append(tokens[i].value);
    str.append("\n");
  }

  File* tofile = new File("./public/toutput.txt");
  tofile->write(str);

  return 0;
}
