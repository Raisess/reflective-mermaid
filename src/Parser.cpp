#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
}

std::vector<Statement> Parser::parse() {
  Statement stmt;
  PropertyStatement pstmt;

  for (int i = 0; i < this->tokens.size(); i++) {
    Token token = this->tokens[i];

    if (token.type == "Symbol" && (token.value == "datasource" || token.value == "generator" || token.value == "model" || token.value == "enum")) {
      this->step = (ParseStep) 0;
    } else if (token.type == "RightCurly") {
      this->step = (ParseStep) 2;
    }

    // skip outside statement EOL's
    if ((this->step == 0 || this->step == 2) && token.type == "EOL") continue;

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
        i += 3; // skip Constructor, {, EOL
        this->step = (ParseStep) 1;
        break;
      case 1:
        switch (stmt.id) {
          // invalid statement
          case -1:
            std::cout << "Parser error: unrecognized statement \"" << stmt.type << " " << stmt.constructor << "\"" << std::endl;
            exit(1);
            break;
          // datasource and generator skip
          case 0:
            break;
          // model property statement
          case 1:
            if (token.type == "EOL" && pstmt.constructor == "") {
              break;
            } else if (token.type == "EOL") {
              stmt.properties.push_back(pstmt);
              pstmt = {};
              break;
            } else if (pstmt.constructor == "") {
              pstmt.constructor = token.value;
              break;
            }

            pstmt.type.append(token.value.append(","));
            break;
          // enum property statement
          case 2:
            pstmt.type = "enum_property";
            pstmt.constructor = token.value;
            stmt.properties.push_back(pstmt);
            pstmt = {};
            i += 1; // skip EOL
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
