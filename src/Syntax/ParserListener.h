#pragma once

#include <vector>
#include "Parser.h"

namespace Syntax {

class ParserListener {
  public:
    ParserListener(std::vector<Statement> stmts) {
      this->stmts = stmts;
      this->ctx << "classDiagram\n";
    }

    std::string transpile();

  private:
    std::vector<Statement> stmts;
    std::ostringstream ctx;

    void enter_model_stmt(Statement stmt);
    void enter_enum_stmt(Statement stmt);
};

}
