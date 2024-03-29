#include "PrettyPrinter.h"
#include "ASTHelper.h"
#include "GeneralHelper.h"

#include "catch2/catch_test_macros.hpp"

#include <iostream>

TEST_CASE("SIPPrettyPrinter: Test error stmt printing", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream << R"(prog() { var x, y; x = 3; y = 2; if(x < y) { error 0;} return 3;})";

    std::string expected = R"(prog()
{
  var x, y;
  x = 3;
  y = 2;
  if ((x < y))
    {
      error 0;
    }
  return 3;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test inc dec statement printing", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream << R"(prog() { var x, y; x = 0; y = 1; x--; y++; return 0;})";

    std::string expected = R"(prog()
{
  var x, y;
  x = 0;
  y = 1;
  x--;
  y++;
  return 0;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test records and record access", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream
            << R"(prog() { var x, y, a; a = 3; x = {f1:0, f2:13}; y = x.f1; x.f2 = y + a; return x.f2; })";

    std::string expected = R"(prog()
{
  var x, y, a;
  a = 3;
  x = {f1:0, f2:13};
  y = x.f1;
  x.f2 = (y + a);
  return x.f2;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test for range statement", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream
            << R"(prog() { var x, z; z = 5; for (x : 0 .. 4 by 1) { z = z + 1; }  return z;})";

    std::string expected = R"(prog()
{
  var x, z;
  z = 5;
  for (x : 0 .. 4 by 1)
    {
      z = (z + 1);
    }
  return z;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test for range statement with missing step", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream << R"(prog() { var x, z; z = 5; for (x : 0 .. 4) { z = z + 1; }  return z;})";

    std::string expected = R"(prog()
{
  var x, z;
  z = 5;
  for (x : 0 .. 4 by 1)
    {
      z = (z + 1);
    }
  return z;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test ternary operator", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream
            << R"(prog() { var x, y, z; x = 3; y = 4; z = (x < y) ? 2 : 3; return (x > y) ? 3 : 1;})";

    std::string expected = R"(prog()
{
  var x, y, z;
  x = 3;
  y = 4;
  z = (x < y) ? 2 : 3;
  return (x > y) ? 3 : 1;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test bool expressions", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream
            << R"(prog() { var x, z; x = true; z = false;  return z;})";

    std::string expected = R"(prog()
{
  var x, z;
  x = true;
  z = false;
  return z;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test RefExpr printing", "[SIPPrettyPrinter]") {
    std::stringstream stream;
    stream << R"(prog() { var x, y; y = &x; return 0;})";

    std::string expected = R"(prog()
{
  var x, y;
  y = &x;
  return 0;
}
)";

    std::stringstream pp;
    auto ast = ASTHelper::build_ast(stream);
    PrettyPrinter::print(ast.get(), pp, ' ', 2);
    std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
    expected = GeneralHelper::removeTrailingWhitespace(expected);
    REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test array, indexing, and length", "[SIPPrettyPrinter]") {
std::stringstream stream;
stream << R"(prog(){var x, y, z, a; a = [[1,2,3],[4,5,6]]; y = a[0][1]; z = [7,8,9]; y = z[2]; x = ##a; return #z;})";

std::string expected = R"(prog()
{
  var x, y, z, a;
  a = [[1, 2, 3], [4, 5, 6]];
  y = a[0][1];
  z = [7, 8, 9];
  y = z[2];
  x = ##a;
  return #z;
}
)";

std::stringstream pp;
auto ast = ASTHelper::build_ast(stream);
PrettyPrinter::print(ast.get(), pp, ' ', 2);
std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
expected = GeneralHelper::removeTrailingWhitespace(expected);
REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test array of operator", "[SIPPrettyPrinter]") {
std::stringstream stream;
stream << R"(prog(){var x, a; a = [1,2,3]; x = [5 of a[1]]; return 0;})";

std::string expected = R"(prog()
{
  var x, a;
  a = [1, 2, 3];
  x = [5 of a[1]];
  return 0;
}
)";

std::stringstream pp;
auto ast = ASTHelper::build_ast(stream);
PrettyPrinter::print(ast.get(), pp, ' ', 2);
std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
expected = GeneralHelper::removeTrailingWhitespace(expected);
REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test unary not operator", "[SIPPrettyPrinter]") {
std::stringstream stream;
stream << R"(prog(){var x; x = 0; return not x;})";

std::string expected = R"(prog()
{
  var x;
  x = 0;
  return not x;
}
)";

std::stringstream pp;
auto ast = ASTHelper::build_ast(stream);
PrettyPrinter::print(ast.get(), pp, ' ', 2);
std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
expected = GeneralHelper::removeTrailingWhitespace(expected);
REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test for each statement", "[SIPPrettyPrinter]") {
std::stringstream stream;
stream << R"(prog(){ var x, y, z; for (x : x) {z = z + 1 - 3; } return z;})";

std::string expected = R"(prog()
{
  var x, y, z;
  for (x : x)
    {
      z = ((z + 1) - 3);
    }
  return z;
}
)";

std::stringstream pp;
auto ast = ASTHelper::build_ast(stream);
PrettyPrinter::print(ast.get(), pp, ' ', 2);
std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
expected = GeneralHelper::removeTrailingWhitespace(expected);
REQUIRE(ppString == expected);
}

TEST_CASE("SIPPrettyPrinter: Test multiple functions", "[SIPPrettyPrinter]") {
std::stringstream stream;
stream << R"(foo(f, a){ return f(a);} bar(x){ return x + 1;} baz(y){ return foo(bar, y);} main(){ var z; z = 3; return baz(z);})";

std::string expected = R"(foo(f, a)
{
  return f(a);
}

bar(x)
{
  return (x + 1);
}

baz(y)
{
  return foo(bar, y);
}

main()
{
  var z;
  z = 3;
  return baz(z);
}
)";

std::stringstream pp;
auto ast = ASTHelper::build_ast(stream);
PrettyPrinter::print(ast.get(), pp, ' ', 2);
std::string ppString = GeneralHelper::removeTrailingWhitespace(pp.str());
expected = GeneralHelper::removeTrailingWhitespace(expected);
REQUIRE(ppString == expected);
}