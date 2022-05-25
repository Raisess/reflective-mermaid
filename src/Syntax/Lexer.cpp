#include "Lexer.h"
#include "../Utils/Error.h"

std::vector<Syntax::Token> Syntax::Lexer::tokenizer(std::string str) {
  std::vector<std::string> str_vec = Lexer::split_str(str);
  std::vector<Token> tokens;

  for (std::string word : str_vec) {
    Token token;
    token.type = Lexer::match(word);
    token.value = token.type == "EOL" ? "\\n" : word;

    tokens.push_back(token);
  }

  return tokens;
}

std::string Syntax::Lexer::match(std::string token) {
  std::vector<TokenMatcher> valid_matches = {
    { "EOL", EOL },
    { "Symbol", "[@A-Z._a-z?]+" },
    { "Number", "\\d+" },
    { "String", "'(.*?)'" },
    { "String", "\"(.*?)\"" },
    { "Operator", "[-+*/=]" },
    { "Colon", "[:]" },
    { "Comma", "[,]" },
    { "LeftBrace", "[{]" },
    { "RightBrace", "[}]" },
    { "LeftParens", "[(]" },
    { "RightParens", "[)]" },
    { "LeftSquare", "[\[]" },
    { "RightSquare", "[\\]]" },
  };

  for (TokenMatcher token_match : valid_matches) {
    if (std::regex_match(token, std::regex(token_match.match))) {
      return token_match.type;
    }
  }

  throw new Utils::Error({ "Invalid token ", token });
}

std::vector<std::string> Syntax::Lexer::split_str(std::string str) {
  std::vector<std::string> str_vec;
  std::string tmp_word = "";

  for (int i = 0; i < str.length(); i++) {
    std::string curr_char = str.substr(i, 1);

    if (std::regex_match(curr_char, std::regex(SEPARATOR))) {
      if (tmp_word != "") {
        str_vec.push_back(tmp_word);
        tmp_word = "";
      }

      str_vec.push_back(curr_char);
      continue;
    } else if (!std::regex_match(curr_char, std::regex(BLANK_SPACE))) {
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
