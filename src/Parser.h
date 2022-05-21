#pragma once

#include <iostream>
#include <vector>
#include "Lexer.h"

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
  std::string value;

  std::vector<PropertyStatement> properties;
} Statement;

class Parser {
  public:
    Parser(std::vector<Token> tokens);

    std::vector<Statement> parse();

  private:
    std::vector<Token> tokens;
    std::vector<Statement> stmts;
    ParseStep step = (ParseStep) 0;
};
