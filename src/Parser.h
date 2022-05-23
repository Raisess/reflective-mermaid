#pragma once

#include <iostream>
#include <vector>
#include "Lexer.h"

#define TTABLE_MAP "TABLE_MAPPER"
#define TENUM_PROP "ENUM_PROPERTY"

enum ParseStep {
  constructor_stp = 0,
  property_stp,
  exit_stp,
};

enum StatementEnum {
  undefined_stmt = -1,
  datasource_generator_stmt = 0,
  model_stmt,
  enum_stmt,
};

typedef struct PropertyStatement {
  std::string type;
  std::string constructor;
} PropertyStatement;

typedef struct Statement {
  StatementEnum id;
  std::string type;
  std::string constructor;
  std::vector<PropertyStatement> properties;
} Statement;

class Parser {
  public:
    Parser(std::vector<Token> tokens) {
      this->tokens = tokens;
    }

    std::vector<Statement> parse();

  private:
    std::vector<Token> tokens;
    std::vector<Statement> stmts;
    ParseStep step = (ParseStep) 0;
};
