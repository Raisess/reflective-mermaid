#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
}

std::vector<Statement> Parser::parse() {
  Statement stmt;

  for (int i = 0; i < this->tokens.size(); i++) {
    Token token = this->tokens[i];

    stmt.value.append(token.value);
    stmt.value.append(" ");

    if (token.type == "Symbol" && (token.value == "datasource" || token.value == "generator" || token.value == "model" || token.value == "enum")) {
      this->step = (ParseStep) 0;
    } else if (token.type == "RightCurly") {
      this->step = (ParseStep) 2;
    }

    // skip exit statement EOL's
    if (this->step == 2 && token.type == "EOL") continue;

    switch (this->step) {
      case 0:
        stmt.id = (StatementEnum)
          (token.value == "datasource" || token.value == "generator"
           ? 0
           : token.value == "model"
             ? 1
             : token.value == "enum"
               ? 2 : -1);

        stmt.type = token.value;
        stmt.constructor = this->tokens[i + 1].value;
        this->step = (ParseStep) 1;
        break;
      case 1:
        switch (stmt.id) {
          case -1:
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
        this->stmts.push_back(stmt);
        stmt = {};
        break;
    }
  }

  return this->stmts;
}
