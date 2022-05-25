#include "Parser.h"
#include "../Utils/Error.h"

std::vector<Syntax::Statement> Syntax::Parser::parse() {
  Statement stmt;
  PropertyStatement pstmt;

  for (int i = 0; i < this->tokens.size(); i++) {
    Token token = this->tokens[i];

    if (token.type == "Symbol" && (token.value == "datasource" || token.value == "generator" || token.value == "model" || token.value == "enum")) {
      this->step = (ParseStep) 0;
    } else if (token.type == "RightBrace") {
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
            throw new Utils::Error({ "Unrecognized statement ", stmt.type, " ", stmt.constructor });
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
            } else if (pstmt.constructor == "") {
              if (token.value == "@@map") {
                i += 2; // skip to map value
                pstmt.constructor = this->tokens[i].value;
                pstmt.type = TTABLE_MAP;
              } else {
                pstmt.constructor = token.value;
                i += 1; // skip to type value
                pstmt.type = this->tokens[i].value;
              }
            }

            break;
          // enum property statement
          case 2:
            pstmt.constructor = token.value;
            pstmt.type = TENUM_PROP;
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
