#include "Lexer.h"

std::vector<Token> Lexer::tokenizer(std::string str) {
  std::vector<std::string> str_vec = Lexer::split_str(str);
  std::vector<Token> tokens;

  for (int i = 0; i < str_vec.size(); i++) {
    Token token;
    token.type = Lexer::match(str_vec[i]);
    token.value = str_vec[i];

    tokens.push_back(token);
  }

  return tokens;
}

std::string Lexer::match(std::string str) {
  std::vector<TokenMatcher> valid_matches = {
    { "Type", "int|string" },
    { "Operator", "[-+*/=]" },
    { "Symbol", "[A-Za-z]+" },
    { "Int", "[0-9]" },
    { "String", "'(.*?)'" },
  };

  for (int i = 0; i < valid_matches.size(); i++) {
    if (std::regex_match(str, std::regex(valid_matches[i].matches))) {
      return valid_matches[i].type;
    }
  }

  std::cout << "Error: Invalid entry " << str << std::endl;
  exit(1);
}

std::vector<std::string> Lexer::split_str(std::string str) {
  std::vector<std::string> str_vec;
  std::string tmp_word;

  for (int i = 0; i < str.length(); i++) {
    if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
      tmp_word.append(str.substr(i, 1));
      continue;
    }

    str_vec.push_back(tmp_word);
    tmp_word = "";
  }

  return str_vec;
}
