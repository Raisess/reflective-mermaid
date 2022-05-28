#pragma once

#include <iostream>
#include <regex>
#include "../Common/LinkedList.h"

#define BLANK_SPACE " |\t"
#define EOL "\n"
#define SEPARATOR "[(){}:,\\n]"

namespace Syntax {

typedef struct {
  std::string type;
  std::string match;
} TokenMatcher;

typedef struct {
  std::string type;
  std::string value;
} Token;

class Lexer {
  public:
    static Common::LinkedList<Token>* tokenizer(std::string str);

  private:
    static std::string match(std::string token);
    static Common::LinkedList<std::string>* split_str(std::string str);
};

}
