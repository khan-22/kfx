/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MATERIAL_PARSER_H
#define MATERIAL_PARSER_H

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "kfx/Result.h"

namespace kfx {

/*
  Grammar:
  SHADER_TYPE: [a-zA-Z][a-zA-Z]*
  OPEN: '{'
  CLOSE: '}'
  PARAMETER: '$' [a-zA-Z][a-zA-Z]*
  STRING: \"[a-zA-Z\.]*\"
  EQUALS: '='
  END_OF_STATEMENT: ';'

  END_FIELD: FIELD | empty
  FIELD: PARAMETER EQUALS STRING END_OF_STATEMENT END_FIELD
  MATERIAL: SHADER_TYPE OPEN FIELD CLOSE
*/

/*
MATERIAL:
  SHADER_TYPE: Basic

  OPEN:
  FIELD:
  CLOSE:
*/

class MaterialParser {
 public:
  struct Fields {
    void setType(std::string type);
    std::string getType() const;

    bool find(std::string parameter, std::string& value);

    void add(std::string parameter, std::string value);

   private:
    std::string m_type;
    std::unordered_map<std::string, std::string> m_fields;
  };

  MaterialParser();
  KfxResult<Fields> parse(std::istringstream& stream);

 private:
  struct ParseTree {
    void addChild(ParseTree child);

    void print(int depth = 0);

    ParseTree* goTo(std::string tag, bool include_self = true);

    std::string tag;
    std::string lexeme;
    std::vector<ParseTree> children;
  };

  void registerFunction(
      std::string name,
      std::function<bool(ParseTree&, std::istringstream& stream)> func);

  void registerRule(std::string name, std::string rule_string);

  bool parseRule(MaterialParser::ParseTree& tree, std::istringstream& stream,
                 std::string name);

  bool parseFunction(MaterialParser::ParseTree& tree,
                     std::istringstream& stream, std::string name);

  static bool SHADER_TYPE(ParseTree& tree, std::istringstream& stream);
  static bool OPEN(ParseTree& tree, std::istringstream& stream);
  static bool CLOSE(ParseTree& tree, std::istringstream& stream);
  static bool PARAMETER(ParseTree& tree, std::istringstream& stream);
  static bool STRING(ParseTree& tree, std::istringstream& stream);
  static bool EQUALS(ParseTree& tree, std::istringstream& stream);
  static bool END_OF_STATEMENT(ParseTree& tree, std::istringstream& stream);

  std::unordered_map<
      std::string, std::function<bool(ParseTree&, std::istringstream& stream)>>
      m_functions;
  std::unordered_map<std::string, std::string> m_rules;
};
}
#endif  // MATERIAL_PARSER_H
