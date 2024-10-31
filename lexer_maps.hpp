#pragma once
#include "lexer.hpp"

namespace occult {
  std::unordered_map<char, token_type> whitespace_map = {
      {' ', whitespace_tt},
      {'\t', whitespace_tt},
      {'\r', whitespace_tt},
      {'\n', whitespace_tt},
      {'\v', whitespace_tt},
      {'\f', whitespace_tt}};

  std::unordered_map<char, token_type> operator_map_single = {
      {'>', greater_than_operator_tt},
      {'<', less_than_operator_tt},
      {'!', unary_not_operator_tt},
      {'+', add_operator_tt},
      {'-', subtract_operator_tt}, // we don't include unary plus and minus here
      {'*', multiply_operator_tt},
      {'/', division_operator_tt},
      {'%', modulo_operator_tt},
      {'^', xor_operator_tt},
      {'&', bitwise_and_tt},
      {'~', unary_bitwise_not_tt},
      {'|', bitwise_or_tt},
      {'=', assignment_tt}};

  std::unordered_map<std::string, token_type> operator_map_double = {
      {"&&", and_operator_tt},
      {"||", or_operator_tt},
      {"==", equals_operator_tt},
      {"!=", not_equals_operator_tt},
      {">=", greater_than_or_equal_operator_tt},
      {"<=", less_than_or_equal_operator_tt},
      {"<<", bitwise_lshift_tt},
      {">>", bitwise_rshift_tt}};

  std::unordered_map<char, token_type> delimiter_map = {
      {')', right_paren_tt},
      {'(', left_paren_tt},
      {']', right_bracket_tt},
      {'[', left_bracket_tt},
      {'}', right_curly_bracket_tt},
      {'{', left_curly_bracket_tt},
      {';', semicolon_tt},
      {',', comma_tt}};

  std::unordered_map<std::string, token_type> keyword_map = {
      {"fn", function_keyword_tt},
      {"if", if_keyword_tt},
      {"else", else_keyword_tt},
      {"elif", elseif_keyword_tt},
      {"loop", loop_keyword_tt},
      {"return", return_keyword_tt},
      {"break", break_keyword_tt},
      {"continue", continue_keyword_tt},
      {"while", while_keyword_tt},
      {"for", for_keyword_tt},
      {"include", include_keyword_tt},
      {"int64", int64_keyword_tt},
      {"int32", int32_keyword_tt},
      {"int16", int16_keyword_tt},
      {"int8", int8_keyword_tt},
      {"uint64", uint64_keyword_tt},
      {"uint32", uint32_keyword_tt},
      {"uint16", uint16_keyword_tt},
      {"uint8", uint8_keyword_tt},
      {"float32", float32_keyword_tt},
      {"float64", float64_keyword_tt},
      {"bool", boolean_keyword_tt},
      {"char", char_keyword_tt},
      {"string", string_keyword_tt},
      {"false", false_keyword_tt},
      {"true", true_keyword_tt}};

  std::unordered_set<char> alnumeric_set = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
      'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
      'u', 'v', 'w', 'x', 'y', 'z',
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
      'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
      'U', 'V', 'W', 'X', 'Y', 'Z',
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
      '_'};

  std::unordered_set<char> numeric_set = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  std::unordered_map<token_type, std::string> token_typename_map = {
      {whitespace_tt, "whitespace"},
      {comment_tt, "comment"},
      {multiline_comment_tt, "multiline_comment"},

      {number_literal_tt, "number_literal"},
      {string_literal_tt, "string_literal"},
      {char_literal_tt, "char_literal"},
      {float_literal_tt, "float_literal"},

      {add_operator_tt, "add_operator"},
      {subtract_operator_tt, "subtract_operator"},
      {unary_minus_operator_tt, "unary_minus_operator"},
      {unary_plus_operator_tt, "unary_plus_operator"},
      {multiply_operator_tt, "multiply_operator"},
      {division_operator_tt, "division_operator"},
      {modulo_operator_tt, "modulo_operator"},
      {xor_operator_tt, "xor_operator"},
      {and_operator_tt, "and_operator"},
      {or_operator_tt, "or_operator"},
      {unary_not_operator_tt, "not_operator"},
      {equals_operator_tt, "equals_operator"},
      {not_equals_operator_tt, "not_equals_operator"},
      {greater_than_operator_tt, "greater_than_operator"},
      {less_than_operator_tt, "less_than_operator"},
      {greater_than_or_equal_operator_tt, "greater_than_or_equal_operator"},
      {less_than_or_equal_operator_tt, "less_than_or_equal_operator"},
      {assignment_tt, "assignment"},
      {right_paren_tt, "right_paren"},
      {left_paren_tt, "left_paren"},
      {right_bracket_tt, "right_bracket"},
      {left_bracket_tt, "left_bracket"},
      {right_curly_bracket_tt, "right_curly_bracket"},
      {left_curly_bracket_tt, "left_curly_bracket"},
      {semicolon_tt, "semicolon"},
      {comma_tt, "comma"},
      {identifier_tt, "identifier"},
      {function_keyword_tt, "function"},
      {if_keyword_tt, "if"},
      {else_keyword_tt, "else"},
      {elseif_keyword_tt, "elseif"},
      {loop_keyword_tt, "loop"},
      {return_keyword_tt, "return"},
      {break_keyword_tt, "break"},
      {continue_keyword_tt, "continue"},
      {while_keyword_tt, "while"},
      {for_keyword_tt, "for"},
      {include_keyword_tt, "include"},
      {int64_keyword_tt, "int64"},
      {int32_keyword_tt, "int32"},
      {int16_keyword_tt, "int16"},
      {int8_keyword_tt, "int8"},
      {uint64_keyword_tt, "uint64"},
      {uint32_keyword_tt, "uint32"},
      {uint16_keyword_tt, "uint16"},
      {uint8_keyword_tt, "uint8"},
      {float32_keyword_tt, "float32"},
      {float64_keyword_tt, "float64"},
      {boolean_keyword_tt, "boolean"},
      {char_keyword_tt, "char"},
      {string_keyword_tt, "string"},
      {false_keyword_tt, "false"},
      {true_keyword_tt, "true"},
      {end_of_file_tt, "end_of_file"},
      {unkown_tt, "unknown"},
      {function_call_parser_tt, "function_call_parser"},
      {argument_count_tt, "argument_count"}};
} // namespace occult
