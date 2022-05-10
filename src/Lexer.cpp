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
    { "EOL", "\r\n|\r|\n" },
    { "NativeType", "@db.[A-Za-z]+" },
    { "InlineFlag", "@[a-z]+" },
    { "Flag", "@@[a-z]+" },
    { "Symbol", "[A-Za-z]+" },
    { "Symbol", "[A-Za-z]+_[A-Za-z]+" },
    { "Number", "\\d+" },
    { "String", "'(.*?)'" },
    { "String", "\"(.*?)\"" },
    { "Operator", "[-+*/=]" },
    { "TwoPoints", "[:]" },
    { "LeftCurly", "[{]" },
    { "RightCurly", "[}]" },
    { "LeftParen", "[(]" },
    { "RightParen", "[)]" },
    { "LeftSquare", "[\[]" },
    { "RightSquare", "[\\]]" },
    { "Comma", "[,]" },
    { "Optinal", "[?]" },
  };

  for (int i = 0; i < valid_matches.size(); i++) {
    if (std::regex_match(str, std::regex(valid_matches[i].matches))) {
      return valid_matches[i].type;
    }
  }

  std::cout << "Error: Invalid token " << str << std::endl;
  exit(1);
}

std::vector<std::string> Lexer::split_str(std::string str) {
  std::vector<std::string> str_vec;
  std::string tmp_word = "";

  for (int i = 0; i < str.length(); i++) {
    std::string curr_char = str.substr(i, 1);

    if (std::regex_match(curr_char, std::regex("[(){}:,?\[\\]]"))) {
      if (tmp_word != "") {
        str_vec.push_back(tmp_word);
        tmp_word = "";
      }

      str_vec.push_back(curr_char);
      continue;
    } else if (!std::regex_match(curr_char, std::regex(" ")) && !std::regex_match(curr_char, std::regex("\n"))) {
      tmp_word.append(curr_char);
      continue;
    }

    if (tmp_word != "") {
      str_vec.push_back(tmp_word);
      tmp_word = "";
    }
  }

  return str_vec;
}
