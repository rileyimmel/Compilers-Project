#include "CheckAssignable.h"
#include "ASTHelper.h"
#include "ExceptionContainsWhat.h"
#include "SemanticError.h"

#include "catch2/catch_test_macros.hpp"

#include <iostream>

TEST_CASE("Check Assignable: array index lhs", "[Symbol]") {
  std::stringstream stream;
  stream << R"(arrindexlhs() { var x, y; x = [0,1,2,3,4,5]; y = x[1]; return 0; })";
  auto ast = ASTHelper::build_ast(stream);
  REQUIRE_NOTHROW(CheckAssignable::check(ast.get()));
}


/************** the following are expected to fail the check ************/

//TEST_CASE("Check Assignable: constant lhs", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(constlhs() { var x; 7 = x; return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("7 not an l-value"));
//}
//
//TEST_CASE("Check Assignable: binary lhs", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(binlhs() { var x; x+1 = x; return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("(x+1) not an l-value"));
//}
//
//TEST_CASE("Check Assignable: function lhs", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(foo() { return 0; } funlhs() { var x; foo() = x; return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("foo() not an l-value"));
//}
//
//TEST_CASE("Check Assignable: alloc lhs", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(alloclhs() { var x; alloc 1 = x; return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("alloc 1 not an l-value"));
//}
//
//TEST_CASE("Check Assignable: record lhs", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(recordlhs() { var x; {f:0, g:1} = x; return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("{f:0,g:1} not an l-value"));
//}
//
//TEST_CASE("Check Assignable: address of pointer", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(recordlhs(p) { var x; x = &(*p); return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("(*p) not an l-value"));
//}
//
//TEST_CASE("Check Assignable: address of expr", "[Symbol]") {
//  std::stringstream stream;
//  stream << R"(recordlhs(p) { var x, y; x = &(y*y); return 0; })";
//  auto ast = ASTHelper::build_ast(stream);
//  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
//                         ContainsWhat("(y*y) not an l-value"));
//}
