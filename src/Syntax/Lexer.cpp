#include <vector>
#include "Lexer.h"
#include "../Utils/Error.h"

Common::LinkedList<Syntax::Token>* Syntax::Lexer::tokenizer(std::string str) {
  Common::LinkedList<Token>* token_list = new Common::LinkedList<Token>();
  Common::LinkedList<std::string>* str_list = Lexer::split_str(str);

  str_list->iterate([&](std::string tmp_str) {
    Token token;
    token.type = Lexer::match(tmp_str);
    token.value = token.type == "EOL" ? "\\n" : tmp_str;
    token_list->create_node(token);
  });

  delete str_list;
  return token_list;
}

std::string Syntax::Lexer::match(std::string token) {
  std::vector<TokenMatcher> valid_matches = {
    { "EOL", EOL },
    { "Symbol", "[A-Z_a-z?\[\\]]+" },
    { "NativeType", "@db.[A-Za-z]+" },
    { "Flag", "@[a-z]+" },
    { "Functor", "@@[a-z]+" },
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
  };

  for (TokenMatcher token_match : valid_matches) {
    if (std::regex_match(token, std::regex(token_match.match))) {
      return token_match.type;
    }
  }

  throw new Utils::Error({ "Invalid token ", token });
}

Common::LinkedList<std::string>* Syntax::Lexer::split_str(std::string str) {
  Common::LinkedList<std::string>* str_list = new Common::LinkedList<std::string>();
  std::string tmp_word = "";

  for (int i = 0; i < str.length(); i++) {
    std::string curr_char = str.substr(i, 1);

    if (std::regex_match(curr_char, std::regex(SEPARATOR))) {
      if (tmp_word != "") {
        str_list->create_node(tmp_word);
        tmp_word = "";
      }

      str_list->create_node(curr_char);
      continue;
    } else if (!std::regex_match(curr_char, std::regex(BLANK_SPACE))) {
      tmp_word.append(curr_char);
      continue;
    }

    if (tmp_word != "") {
      str_list->create_node(tmp_word);
      tmp_word = "";
    }
  }

  return str_list;
}
