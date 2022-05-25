#pragma once

#include <iostream>
#include <regex>
#include <vector>

#define BLANK_SPACE " |\t"
#define EOL "\n"
#define SEPARATOR "[(){}:,\[\\]\\n]"

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
    static std::vector<Token> tokenizer(std::string str);

  private:
    static std::string match(std::string token);
    static std::vector<std::string> split_str(std::string str);
};
