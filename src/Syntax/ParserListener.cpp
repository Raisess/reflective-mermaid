#include "ParserListener.h"
#include "../Utils/Error.h"

std::string Syntax::ParserListener::transpile() {
  for (Statement stmt : this->stmts) {
    switch (stmt.id) {
      case -1:
        throw new Utils::Error({ "Invalid statement ", stmt.type});
      case 0:
        break;
      case 1:
        this->enter_model_stmt(stmt);
        break;
      case 2:
        this->enter_enum_stmt(stmt);
        break;
    }
  }

  return this->ctx.str();
}

void Syntax::ParserListener::enter_model_stmt(Statement stmt) {
  this->ctx << "\tclass " << stmt.constructor << " {\n";

  for (PropertyStatement prop : stmt.properties) {
    this->ctx << "\t\t" << prop.type << " " << prop.constructor << "\n";
  }

  this->ctx << "\t}\n";
}

void Syntax::ParserListener::enter_enum_stmt(Statement stmt) {
  this->ctx << "\tclass " << stmt.constructor << " {\n";

  for (PropertyStatement prop : stmt.properties) {
    this->ctx << "\t\t" << prop.constructor << "\n";
  }

  this->ctx << "\t}\n";
}
