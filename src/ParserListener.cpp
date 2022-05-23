#include "ParserListener.h"

std::string ParserListener::transpile() {
  for (Statement stmt : this->stmts) {
    switch (stmt.id) {
      case -1:
      case 0:
        break;
      case 1:
        this->enter_model_stmt(stmt);
        break;
      case 2:
        this->enter_enum_stmt(stmt);
        break;
      default:
        std::cout << "Error: Invalid statement" << stmt.type << std::endl;
        exit(1);
    }
  }

  return this->ctx.str();
}

void ParserListener::enter_model_stmt(Statement stmt) {
  this->ctx << "\tclass " << stmt.constructor << " {\n";
  this->ctx << "\t}\n";
}

void ParserListener::enter_enum_stmt(Statement stmt) {
  this->ctx << "\tclass " << stmt.constructor << "_Enum" << " {\n";
  this->ctx << "\t}\n";
}
