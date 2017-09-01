#include "kfx/resources/MaterialParser.h"

#include <iostream>
#include <regex>

namespace kfx {
MaterialParser::MaterialParser() {
  registerRule("END_FIELD", "FIELD | empty");
  registerRule("FIELD", "PARAMETER EQUALS STRING END_OF_STATEMENT END_FIELD");
  registerRule("MATERIAL", "SHADER_TYPE OPEN FIELD CLOSE");

  registerFunction("SHADER_TYPE", &MaterialParser::SHADER_TYPE);
  registerFunction("OPEN", &MaterialParser::OPEN);
  registerFunction("CLOSE", &MaterialParser::CLOSE);
  registerFunction("PARAMETER", &MaterialParser::PARAMETER);
  registerFunction("STRING", &MaterialParser::STRING);
  registerFunction("EQUALS", &MaterialParser::EQUALS);
  registerFunction("END_OF_STATEMENT", &MaterialParser::END_OF_STATEMENT);
}

KfxResult<MaterialParser::Fields> MaterialParser::parse(
    std::istringstream& stream) {
  ParseTree root;
  parseRule(root, stream, "MATERIAL");
  // root.print();

  KfxResult<MaterialParser::Fields> result;
  result.second = KfxStatus::SUCCESS;

  ParseTree* current_node = &root;

  ParseTree* shader_type_node = current_node->goTo("SHADER_TYPE");
  if (shader_type_node == nullptr) {
    result.second = KfxStatus::FAILURE;
    return result;
  }

  result.first.setType(shader_type_node->lexeme);

  while ((current_node = current_node->goTo("FIELD", false)) != nullptr) {
    std::string parameter = current_node->goTo("PARAMETER")->lexeme;
    std::string value = current_node->goTo("STRING")->lexeme;

    // Strip the \" from either end.
    value = value.substr(1, value.length() - 2);
    result.first.add(parameter, value);
  }

  return result;
}

void MaterialParser::Fields::setType(std::string type) { m_type = type; }

std::string MaterialParser::Fields::getType() const { return m_type; }

bool MaterialParser::Fields::find(std::string parameter, std::string& value) {
  auto it = m_fields.find(parameter);
  if (it != m_fields.end()) {
    value = it->second;
    return true;
  } else {
    return false;
  }
}

void MaterialParser::Fields::add(std::string parameter, std::string value) {
  m_fields[parameter] = value;
}

void MaterialParser::ParseTree::addChild(
    //   std::string tag, std::string lexeme) {
    ParseTree child) {
  children.push_back(child);
  // children.emplace_back();
  // ParseTree& child = children.back();
  // child.tag = tag;
  // child.lexeme = lexeme;
  // return child;
}

void MaterialParser::ParseTree::print(int depth) {
  std::string indent = "";
  for (int i = 0; i < depth; i++) {
    indent += " ";
  }

  std::cout << indent << tag << ": " << lexeme << std::endl;

  for (auto& child : children) {
    child.print(depth + 1);
  }
}

MaterialParser::ParseTree* MaterialParser::ParseTree::goTo(std::string tag,
                                                           bool include_self) {
  if (include_self) {
    if (this->tag == tag) {
      return this;
    }
  }

  for (ParseTree& child : children) {
    ParseTree* result = child.goTo(tag);
    if (result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

void MaterialParser::registerFunction(
    std::string name,
    std::function<bool(ParseTree&, std::istringstream& stream)> func) {
  m_functions[name] = func;
}

void MaterialParser::registerRule(std::string name, std::string rule_string) {
  m_rules[name] = rule_string;
}

bool MaterialParser::parseRule(MaterialParser::ParseTree& tree,
                               std::istringstream& stream, std::string name) {
  tree.tag = name;
  tree.lexeme = "<>";

  // Get the rule's string if it exists...
  auto it_rule = m_rules.find(name);
  if (it_rule != m_rules.end()) {
    std::string rule_string = it_rule->second;
    std::istringstream full_rule_buffer(rule_string);

    // Split the rule string at ever '|' to handle branching
    std::vector<std::istringstream> rule_buffers;
    std::string segment;
    while (std::getline(full_rule_buffer, segment, '|')) {
      rule_buffers.emplace_back(segment);
    }

    // Go through the branching paths until a successful branch is found, then
    // return after adding the children from that branch.
    std::vector<ParseTree> potential_children;
    bool success = true;
    for (auto& rule_buffer : rule_buffers) {
      auto backup_position = stream.tellg();

      std::string current_word;
      success = true;
      while (rule_buffer >> current_word) {
        // If the branch ends on empty (should be the only thing in the branch,
        // but we'll ignore other cases) then it's an automatic success.
        if (current_word == "empty") {
          break;
        }

        ParseTree child;
        if (parseRule(child, stream, current_word)) {
          potential_children.push_back(child);
        } else {
          // If not successful, abort the current branch.
          success = false;
          break;
        }
      }

      // If successful, keep the children from this branch,
      // otherwise, clear and try the next branch if it exists.
      if (success) {
        break;
      } else {
        stream.seekg(backup_position);
        potential_children.clear();
      }
    }

    // If success is false here, then there were no successful branches!
    if (!success) {
      return false;
    }

    for (auto& child : potential_children) {
      tree.addChild(child);
    }
    return true;

  } else {
    // If the rule was not defined as a sequence of other rules,
    // execute it as a function.
    return parseFunction(tree, stream, name);
  }
}

bool MaterialParser::parseFunction(MaterialParser::ParseTree& tree,
                                   std::istringstream& stream,
                                   std::string name) {
  auto it_func = m_functions.find(name);
  if (it_func != m_functions.end()) {
    std::function<bool(ParseTree&, std::istringstream & stream)> func =
        it_func->second;

    auto backup_position = stream.tellg();

    if (func(tree, stream)) {
      return true;
    } else {
      stream.seekg(backup_position);
      return false;
    }
  }
  return false;
}

bool MaterialParser::SHADER_TYPE(ParseTree& tree, std::istringstream& stream) {
  std::regex expr("[a-zA-Z][a-zA-Z]*");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::OPEN(ParseTree& tree, std::istringstream& stream) {
  std::regex expr("\\{");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::CLOSE(ParseTree& tree, std::istringstream& stream) {
  std::regex expr("\\}");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::PARAMETER(ParseTree& tree, std::istringstream& stream) {
  std::regex expr("\\$[a-zA-Z]+");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::STRING(ParseTree& tree, std::istringstream& stream) {
  // std::regex expr("\\\"[a-zA-Z0-9\\.\/\\\\[\\]\\(\\)\\{\\}]\\\"");
  std::regex expr(R"(\"[\/a-zA-Z\.0-9\_]*\")");

  auto backup_position = stream.tellg();

  std::string word;
  stream >> word;

  std::smatch match;

  std::regex_search(word, match, expr);
  if (match[0].matched) {
    stream.seekg(backup_position);
    stream.seekg(match[0].length() + 1, stream.cur);

    // tree.lexeme = word.substr(0, match[0].length());
    tree.lexeme = match[0];
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::EQUALS(ParseTree& tree, std::istringstream& stream) {
  std::regex expr("\\=");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}

bool MaterialParser::END_OF_STATEMENT(ParseTree& tree,
                                      std::istringstream& stream) {
  std::regex expr("\\;");

  std::string word;
  stream >> word;
  if (std::regex_match(word, expr)) {
    tree.lexeme = word;
    return true;
  } else {
    return false;
  }
}
}
