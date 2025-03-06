#include "ir_gen.hpp"
#include "../lexer/number_parser.hpp"

/*
 * This IR generation is really crappy and disorganized, I will make it organized later on, and I'll probably move to SSA or TAC
 * later on as well, but this is what I can do for now, as I want to make actual progress on the language, but we can still do some stack optimisations
 * we can use this paper (http://www.rigwit.co.uk/thesis/chap-5.pdf) as an example, and other theories too.
*/

namespace occult {
  ir_function ir_gen::generate_function(ast_function* func_node) {
    ir_function function;
    
    for (const auto& c : func_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::int8_datatype: 
        case ast_type::int16_datatype:
        case ast_type::int32_datatype:
        case ast_type::int64_datatype:
        case ast_type::uint8_datatype:
        case ast_type::uint16_datatype:
        case ast_type::uint32_datatype:
        case ast_type::uint64_datatype:
        case ast_type::float32_datatype:
        case ast_type::float64_datatype:
        case ast_type::string_datatype: {
          function.type = c->to_string().substr(4, c->to_string().size());

          break;
        }
        case ast_type::functionarguments: {
          generate_function_args(function, ast::cast_raw<ast_functionargs>(c.get()));
          
          break;
        }
        case ast_type::identifier: {
          function.name = c->content;
          
          break;
        }
        case ast_type::block: {
          generate_block(function, ast::cast_raw<ast_block>(c.get()));
          
          break;
        }
        default: {
          break;
        }
      }
    }
    
    return function;
  }
  
  void ir_gen::generate_function_args(ir_function& function, ast_functionargs* func_args_node) {
    for (const auto& arg : func_args_node->get_children()) {
      for (const auto& c : arg->get_children()) {
        function.args.emplace_back(c->content, arg->to_string().substr(4, arg->to_string().size()));
      }
    }
  }
  
  template<typename IntType>
  void ir_gen::generate_arg(ir_function& function, ast_functionarg* arg_node) {
    for (const auto& c : arg_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::number_literal: {
          function.code.emplace_back(op_push, from_numerical_string<IntType>(c->content));
          
          break;
        }
        case ast_type::add_operator: {
          function.code.emplace_back(op_add);
          
          break;
        }
        case ast_type::subtract_operator: {
          function.code.emplace_back(op_sub);
          
          break;
        }
        case ast_type::multiply_operator: {
          function.code.emplace_back(op_mul);
          
          break;
        }
        case ast_type::division_operator: {
          function.code.emplace_back(op_div);
          
          break;
        }
        case ast_type::modulo_operator: {
          function.code.emplace_back(op_mod);
          
          break;
        }
        case ast_type::identifier: {
          function.code.emplace_back(op_load, c->content);
          
          break;
        }
        case ast_type::stringliteral: {
          function.code.emplace_back(op_push, c->content);
          
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            generate_arg<IntType>(function, arg_node);
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          
          break;
        }
        case ast_type::bitwise_and: {
          break;
        }
        case ast_type::bitwise_or: {
          break;
        }
        case ast_type::xor_operator: {
          break;
        }
        case ast_type::bitwise_lshift: {
          break;
        }
        case ast_type::bitwise_rshift: {
          break;
        }
        case ast_type::unary_plus_operator: {
          break;
        }
        case ast_type::unary_minus_operator: {
          break;
        }
        case ast_type::unary_bitwise_not: {
          break;
        }
        case ast_type::unary_not_operator: {
          break;
        }
        case ast_type::or_operator: {
          break;
        }
        case ast_type::and_operator: {
          break;
        }
        case ast_type::equals_operator: {
          break;
        }
        case ast_type::not_equals_operator: {
          break;
        }
        case ast_type::greater_than_operator: {
          break;
        }
        case ast_type::less_than_operator: {
          break;
        }
        case ast_type::greater_than_or_equal_operator: {
          break;
        }
        case ast_type::less_than_or_equal_operator: {
          break;
        }
        default: {
          break;
        }
      }
    }
  } 
  
  template<typename IntType>
  void ir_gen::generate_int(ir_function& function, ast_assignment* assignment_node) {
    for (const auto& c : assignment_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::number_literal: {
          function.code.emplace_back(op_push, from_numerical_string<IntType>(c->content));
          
          break;
        }
        case ast_type::add_operator: {
          function.code.emplace_back(op_add);
          
          break;
        }
        case ast_type::subtract_operator: {
          function.code.emplace_back(op_sub);
          
          break;
        }
        case ast_type::multiply_operator: {
          function.code.emplace_back(op_mul);
          
          break;
        }
        case ast_type::division_operator: {
          function.code.emplace_back(op_div);
          
          break;
        }
        case ast_type::modulo_operator: {
          function.code.emplace_back(op_mod);
          
          break;
        }
        case ast_type::identifier: {
          function.code.emplace_back(op_load, c->content);
          
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            generate_arg<IntType>(function, arg_node);
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          
          break;
        }
        case ast_type::bitwise_and: {
          break;
        }
        case ast_type::bitwise_or: {
          break;
        }
        case ast_type::xor_operator: {
          break;
        }
        case ast_type::bitwise_lshift: {
          break;
        }
        case ast_type::bitwise_rshift: {
          break;
        }
        case ast_type::unary_plus_operator: {
          break;
        }
        case ast_type::unary_minus_operator: {
          break;
        }
        case ast_type::unary_bitwise_not: {
          break;
        }
        case ast_type::unary_not_operator: {
          break;
        }
        case ast_type::or_operator: {
          break;
        }
        case ast_type::and_operator: {
          break;
        }
        case ast_type::equals_operator: {
          break;
        }
        case ast_type::not_equals_operator: {
          break;
        }
        case ast_type::greater_than_operator: {
          break;
        }
        case ast_type::less_than_operator: {
          break;
        }
        case ast_type::greater_than_or_equal_operator: {
          break;
        }
        case ast_type::less_than_or_equal_operator: {
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_return(ir_function& function, ast_returnstmt* return_node, std::string type) {
    for (const auto& c : return_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::number_literal: {
          auto it = ir_typemap.find(type);
          
          if (it != ir_typemap.end()) {
            switch (it->second) {
              case signed_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::int64_t>(c->content));
                
                break;
              }
              case unsigned_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::uint64_t>(c->content));
                
                break;
              }
              case floating_point: {
                function.code.emplace_back(op_push, from_numerical_string<double>(c->content));
                
                break;
              }
              case string: {
                function.code.emplace_back(op_push, from_numerical_string<std::string>(c->content));
                
                break;
              }
            }
          }
          
          break;
        }
        case ast_type::add_operator: {
          function.code.emplace_back(op_add);
          
          break;
        }
        case ast_type::subtract_operator: {
          function.code.emplace_back(op_sub);
          
          break;
        }
        case ast_type::multiply_operator: {
          function.code.emplace_back(op_mul);
          
          break;
        }
        case ast_type::division_operator: {
          function.code.emplace_back(op_div);
          
          break;
        }
        case ast_type::modulo_operator: {
          function.code.emplace_back(op_mod);
          
          break;
        }
        case ast_type::identifier: {
          function.code.emplace_back(op_load, c->content);
          
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            auto it = ir_typemap.find(type);
            
            if (it != ir_typemap.end()) {
              switch (it->second) {
                case signed_int:{
                  generate_arg<std::int64_t>(function, arg_node);
                  
                  break;
                }
                case unsigned_int:{
                  generate_arg<std::uint64_t>(function, arg_node);
                  
                  break;
                }
                case floating_point: {
                  generate_arg<double>(function, arg_node);
                  
                  break;
                }
                case string: {
                  generate_arg<std::string>(function, arg_node);
                  
                  break;
                }
              }
            }
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          
          break;
        }
        case ast_type::bitwise_and: {
          break;
        }
        case ast_type::bitwise_or: {
          break;
        }
        case ast_type::xor_operator: {
          break;
        }
        case ast_type::bitwise_lshift: {
          break;
        }
        case ast_type::bitwise_rshift: {
          break;
        }
        case ast_type::unary_plus_operator: {
          break;
        }
        case ast_type::unary_minus_operator: {
          break;
        }
        case ast_type::unary_bitwise_not: {
          break;
        }
        case ast_type::unary_not_operator: {
          break;
        }
        case ast_type::or_operator: {
          break;
        }
        case ast_type::and_operator: {
          break;
        }
        case ast_type::equals_operator: {
          break;
        }
        case ast_type::not_equals_operator: {
          break;
        }
        case ast_type::greater_than_operator: {
          break;
        }
        case ast_type::less_than_operator: {
          break;
        }
        case ast_type::greater_than_or_equal_operator: {
          break;
        }
        case ast_type::less_than_or_equal_operator: {
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_if(ir_function& function, ast_ifstmt* if_node) {
    for (const auto& c : if_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::block: {
          generate_block(function, ast::cast_raw<ast_block>(c.get()));
          
          break;
        }
        case ast_type::number_literal: {
          auto it = ir_typemap.find(function.type);
          
          if (it != ir_typemap.end()) {
            switch (it->second) {
              case signed_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::int64_t>(c->content));
                
                break;
              }
              case unsigned_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::uint64_t>(c->content));
                
                break;
              }
              case floating_point: {
                function.code.emplace_back(op_push, from_numerical_string<double>(c->content));
                
                break;
              }
              case string: {
                function.code.emplace_back(op_push, from_numerical_string<std::string>(c->content));
                
                break;
              }
            }
          }
          
          break;
        }
        case ast_type::add_operator: {
          function.code.emplace_back(op_add);
          
          break;
        }
        case ast_type::subtract_operator: {
          function.code.emplace_back(op_sub);
          
          break;
        }
        case ast_type::multiply_operator: {
          function.code.emplace_back(op_mul);
          
          break;
        }
        case ast_type::division_operator: {
          function.code.emplace_back(op_div);
          
          break;
        }
        case ast_type::modulo_operator: {
          function.code.emplace_back(op_mod);
          
          break;
        }
        case ast_type::identifier: {
          function.code.emplace_back(op_load, c->content);
          
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            auto it = ir_typemap.find(function.type);
            
            if (it != ir_typemap.end()) {
              switch (it->second) {
                case signed_int:{
                  generate_arg<std::int64_t>(function, arg_node);
                  
                  break;
                }
                case unsigned_int:{
                  generate_arg<std::uint64_t>(function, arg_node);
                  
                  break;
                }
                case floating_point: {
                  generate_arg<double>(function, arg_node);
                  
                  break;
                }
                case string: {
                  generate_arg<std::string>(function, arg_node);
                  
                  break;
                }
              }
            }
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          
          break;
        }
        case ast_type::bitwise_and: {
          break;
        }
        case ast_type::bitwise_or: {
          break;
        }
        case ast_type::xor_operator: {
          break;
        }
        case ast_type::bitwise_lshift: {
          break;
        }
        case ast_type::bitwise_rshift: {
          break;
        }
        case ast_type::unary_plus_operator: {
          break;
        }
        case ast_type::unary_minus_operator: {
          break;
        }
        case ast_type::unary_bitwise_not: {
          break;
        }
        case ast_type::unary_not_operator: {
          break;
        }
        case ast_type::or_operator: {
          break;
        }
        case ast_type::and_operator: {
          break;
        }
        case ast_type::equals_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jnz, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::not_equals_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jz, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::greater_than_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jl, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::less_than_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jg, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::greater_than_or_equal_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jle, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::less_than_or_equal_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jge, "label_" + std::to_string(label_count));
          
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_elseif(ir_function& function, ast_elseifstmt* elseif_node) {
    for (const auto& c : elseif_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::block: {
          generate_block(function, ast::cast_raw<ast_block>(c.get()));
          
          break;
        }
        case ast_type::number_literal: {
          auto it = ir_typemap.find(function.type);
          
          if (it != ir_typemap.end()) {
            switch (it->second) {
              case signed_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::int64_t>(c->content));
                
                break;
              }
              case unsigned_int:{
                function.code.emplace_back(op_push, from_numerical_string<std::uint64_t>(c->content));
                
                break;
              }
              case floating_point: {
                function.code.emplace_back(op_push, from_numerical_string<double>(c->content));
                
                break;
              }
              case string: {
                function.code.emplace_back(op_push, from_numerical_string<std::string>(c->content));
                
                break;
              }
            }
          }
          
          break;
        }
        case ast_type::add_operator: {
          function.code.emplace_back(op_add);
          
          break;
        }
        case ast_type::subtract_operator: {
          function.code.emplace_back(op_sub);
          
          break;
        }
        case ast_type::multiply_operator: {
          function.code.emplace_back(op_mul);
          
          break;
        }
        case ast_type::division_operator: {
          function.code.emplace_back(op_div);
          
          break;
        }
        case ast_type::modulo_operator: {
          function.code.emplace_back(op_mod);
          
          break;
        }
        case ast_type::identifier: {
          function.code.emplace_back(op_load, c->content);
          
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            auto it = ir_typemap.find(function.type);
            
            if (it != ir_typemap.end()) {
              switch (it->second) {
                case signed_int:{
                  generate_arg<std::int64_t>(function, arg_node);
                  
                  break;
                }
                case unsigned_int:{
                  generate_arg<std::uint64_t>(function, arg_node);
                  
                  break;
                }
                case floating_point: {
                  generate_arg<double>(function, arg_node);
                  
                  break;
                }
                case string: {
                  generate_arg<std::string>(function, arg_node);
                  
                  break;
                }
              }
            }
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          function.code.emplace_back(op_cmp);
          
          break;
        }
        case ast_type::bitwise_and: {
          break;
        }
        case ast_type::bitwise_or: {
          break;
        }
        case ast_type::xor_operator: {
          break;
        }
        case ast_type::bitwise_lshift: {
          break;
        }
        case ast_type::bitwise_rshift: {
          break;
        }
        case ast_type::unary_plus_operator: {
          break;
        }
        case ast_type::unary_minus_operator: {
          break;
        }
        case ast_type::unary_bitwise_not: {
          break;
        }
        case ast_type::unary_not_operator: {
          break;
        }
        case ast_type::or_operator: {
          break;
        }
        case ast_type::and_operator: {
          break;
        }
        case ast_type::equals_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jnz, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::not_equals_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jz, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::greater_than_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jl, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::less_than_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jg, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::greater_than_or_equal_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jle, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::less_than_or_equal_operator: {
          function.code.emplace_back(op_cmp);
          function.code.emplace_back(op_jge, "label_" + std::to_string(label_count));
          
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_else(ir_function& function, ast_elsestmt* else_node) {
    for (const auto& c : else_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::block: {
          generate_block(function, ast::cast_raw<ast_block>(c.get()));
          
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_loop(ir_function& function, ast_loopstmt* loop_node) {
    for (const auto& c : loop_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::block: {
          generate_block(function, ast::cast_raw<ast_block>(c.get()));
          
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void ir_gen::generate_block(ir_function& function, ast_block* block_node) {
    for (const auto& c : block_node->get_children()) {
      switch(c->get_type()) {
        case ast_type::int8_datatype:
        case ast_type::int16_datatype:
        case ast_type::int32_datatype: 
        case ast_type::int64_datatype: {
          auto node = c.get();
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name
          auto assignment = ast::cast_raw<ast_assignment>(node->get_children().back().get()); // expression stuff
          
          generate_int<std::int64_t>(function, assignment);
          
          function.code.emplace_back(op_store, identifier->content, c->to_string().substr(4, c->to_string().size()));
          
          break;
        }
        case ast_type::uint8_datatype:
        case ast_type::uint16_datatype:
        case ast_type::uint32_datatype: 
        case ast_type::uint64_datatype: {
          auto node = c.get();
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); 
          auto assignment = ast::cast_raw<ast_assignment>(node->get_children().back().get()); 
          
          generate_int<std::uint64_t>(function, assignment);
          
          function.code.emplace_back(op_store, identifier->content, c->to_string().substr(4, c->to_string().size()));
          
          break;
        }
        case ast_type::float32_datatype: 
        case ast_type::float64_datatype: {
          break;
        }
        case ast_type::string_datatype: {
          break;
        }
        case ast_type::identifier: {
          break;
        }
        case ast_type::functioncall: {
          auto node = ast::cast_raw<ast_functioncall>(c.get());
          
          auto identifier = ast::cast_raw<ast_identifier>(node->get_children().front().get()); // name of call
          
          auto arg_location = 1;
          while (node->get_children().at(arg_location).get()->content != "end_call") {
            auto arg_node = ast::cast_raw<ast_functionarg>(node->get_children().at(arg_location).get());
            
            auto it = ir_typemap.find(function.type);
            
            if (it != ir_typemap.end()) {
              switch (it->second) {
                case signed_int:{
                  generate_arg<std::int64_t>(function, arg_node);
                  
                  break;
                }
                case unsigned_int:{
                  generate_arg<std::uint64_t>(function, arg_node);
                  
                  break;
                }
                case floating_point: {
                  generate_arg<double>(function, arg_node);
                  
                  break;
                }
                case string: {
                  generate_arg<std::string>(function, arg_node);
                  
                  break;
                }
              }
            }
            
            arg_location++;
          }
          
          function.code.emplace_back(op_call, identifier->content);
          
          break;
        }
        case ast_type::ifstmt: {
          generate_if(function, ast::cast_raw<ast_ifstmt>(c.get()));
          
          function.code.emplace_back(label, "label_" + std::to_string(label_count++));
          label_map.insert({"label_" + std::to_string(label_count), label_count});
          
          break;
        }
        case ast_type::elseifstmt: {
          generate_elseif(function, ast::cast_raw<ast_elseifstmt>(c.get()));
          
          function.code.emplace_back(label, "label_" + std::to_string(label_count++));
          label_map.insert({"label_" + std::to_string(label_count), label_count});
          
          break;
        }
        case ast_type::elsestmt: {
          generate_else(function, ast::cast_raw<ast_elsestmt>(c.get()));
          
          break;
        }
        case ast_type::loopstmt: {
          function.code.emplace_back(label, "label_" + std::to_string(label_count));
          label_map.insert({"label_" + std::to_string(label_count), label_count});
          
          generate_loop(function, ast::cast_raw<ast_loopstmt>(c.get()));
          
          function.code.emplace_back(op_jmp, "label_" + std::to_string(label_count));
          
          break;
        }
        case ast_type::whilestmt: {
          break;
        }
        case ast_type::forstmt: {
          break;
        }
        case ast_type::returnstmt: {
          generate_return(function, ast::cast_raw<ast_returnstmt>(c.get()), function.type);
          
          function.code.emplace_back(op_ret);
          
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  struct visitor {
    void operator()(const float& v){ std::cout << v << "\n"; };
    void operator()(const double& v){ std::cout << v << "\n"; };
    void operator()(const std::int64_t& v){ std::cout << v << "\n"; };
    void operator()(const std::uint64_t& v){ std::cout << v << "\n"; };
    void operator()(const std::string& v){ std::cout << v << "\n"; };
    void operator()(std::monostate){ std::cout << "\n"; };
  };
  
  void ir_gen::visualize(std::vector<ir_function> funcs) {
    for (auto& func : funcs) {
      std::cout << "\n" << func.type << "\n";
      std::cout << func.name << "\n";
      
      std::cout << "args:\n";
      for (auto& arg : func.args) {
        std::cout << "\t" << arg.type << "\n";
        std::cout << "\t" << arg.name << "\n";
      }
      
      std::cout << "code:\n";
      for (auto& i : func.code) {
        std::cout << occult::opcode_to_string(i.op) << " ";
        std::visit(visitor(), i.operand);
      }
    }
  }
  
  std::vector<ir_function> ir_gen::lower() {
    std::vector<ir_function> functions;
    
    for (const auto& c : root->get_children()) {
      auto type = c->get_type();
      
      if (type == ast_type::function) {
        functions.emplace_back(generate_function(ast::cast_raw<ast_function>(c.get())));
      }
    }
    
    return functions;
  }
} // namespace occult
