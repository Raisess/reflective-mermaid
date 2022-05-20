#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
}

std::vector<Statement> Parser::parse() {
  ParseStep step = (ParseStep) 0;

  std::vector<Statement> stmts;
  Statement stmt;

  for (int i = 0; i < this->tokens.size(); i++) {
    Token token = tokens[i];

    stmt.value.append(token.value);
    stmt.value.append(" ");

    // statement identifier
    if (token.type == "Symbol" && (token.value == "datasource" || token.value == "generator" || token.value == "model" || token.value == "enum")) {
      step = (ParseStep) 0;
    }

    // start of statement
    if (token.type == "LeftCurly") {
      step = (ParseStep) 1;
      continue;
    }

    // end of statement
    if (token.type == "RightCurly") {
      step = (ParseStep) 2;
    }

    switch (step) {
      case 0:
        stmt.id = (StatementEnum)
          (token.value == "datasource" || token.value == "generator"
           ? 0
           : token.value == "model"
             ? 1 : 2);

        stmt.type = token.value;
        i += 1;
        stmt.constructor = this->tokens[i].value;
        break;
      case 1:
        // enter property statement generator
        switch (stmt.id) {
          case 0:
            break;
          case 1:
            // model property statement
            break;
          case 2:
            // enum property statement
            break;
        }
        break;
      case 2:
        stmts.push_back(stmt);
        stmt = {};
        break;
    }
  }

  return stmts;
}
