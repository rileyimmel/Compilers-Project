#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SIP Parser: boolean in an if", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
			  if ( x == true ) {
					y = 42;
				} else if ( x == false ){
					y = 43;
				}
        return y;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean as var", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
			  y = true;
				y = false;
        return y;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean as while cond.", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
			  while ( true ){
					y = 42;
				}
        return y;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean and negation", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
			  while ( not true ){
					y = 42;
				}
        return y;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: unary not", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
			  if ( not x ) {
					y = 42;
				}
        return y;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: and", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
				y = true;
				x = true;
			  while ( x and y ){
					z = 42;
				}
        return z;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: or", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
				y = true;
				x = true;
			  while ( x or y ){
					z = 42;
				}
        return z;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array and array index", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0, 1];
				b = [];
				c = a[0];
        return a;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array of", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [5 of 3];
        return a;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: len op", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0, 1];
				b = #a;
        return a;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: %, -, and relational operators", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = y % 1;
        x = -1;
        x = -x;
        x = 1 < 0;
        x = 1 <= 0;
        x = 1 >= 0;
        return z;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: ternary", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, x, y, z;
				x = 1;
				y = 2;
				z = 3;
				a = x ? y : z;
        return a;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: inc", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x;
			  x++;
        return x;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: dec", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x;
			  x--;
        return x;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for each", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x, y, z;
			  for (x : x) {
			 	  z = z + 1;
			  }
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for range", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
			  for (x : 0 .. 4 by 1) {
			 	  z = z + 1;
			  }
				for (x : 0 .. 4) {
			 	  z = z + 1;
			  }
				for (0 : 0 .. 4 by 1) {
			 	  z = z + 1;
			  }
				for (0 : 0 .. 4) {
			 	  z = z + 1;
			  }
				for (x : y .. z by x) {
			 	  z = z + 1;
			  }
				for (x : y .. z) {
			 	  z = z + 1;
			  }
        return z;
      }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

/************ The following are expected to fail parsing ************/

TEST_CASE("SIP Parser: bad unary not", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y;
				y = 0;
				x = not y
        return x;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad and", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
				y = true;
				x = true;
			  while ( x and @ ){
					z = 42;
				}
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad or", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
				y = true;
				x = true;
			  while ( x or @ ){
					z = 42;
				}
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad array decl. right side", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0,];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream)
);
}

TEST_CASE("SIP Parser: bad array decl. left side", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				@ = [0, 1];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad array of, non expr", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [5 of @];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad array of, missing expr", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [5 of ];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad len op", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0, 1];
				b = #@;
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad array element reference inside", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0, 1];
				b = a[@];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad array element reference outside", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, b, c;
				a = [0, 1];
				b = @[0];
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad modulo", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = y % @;
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad negation", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = -@;
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad LT", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = 1 < @;
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad LE", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = 1 <= @;
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad GE", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      operators() {
        var x;
        x = 1 >= @;
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad ternary", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var a, x, y, z;
				x = 1;
				y = 2;
				z = 3;
				a = x ? @ : z;
        return a;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad inc", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x;
			  @++;
        return x;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bad dec", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x;
			  @--;
        return x;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for each with non-expr as second expr", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, z;
          for ( x : @ ) {
						z = z + 1;
					}
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for range without ..", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
			  for (x : 0 4 by 1) {
			 	  z = z + 1;
			  }
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for range non-expr", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
			  for (x : 0 .. 4 by @) {
			 	  z = z + 1;
			  }
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: for range missing required expr", "[SIP Parser]") {
std::stringstream stream;
stream << R"(
      short() {
        var x, y, z;
			  for (x : .. 4 by 1) {
			 	  z = z + 1;
			  }
        return z;
      }
    )";

REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

/* These tests checks for operator precedence.
 * They access the parse tree and ensure that the higher precedence
 * operator is nested more deeply than the lower precedence operator.
 */

/*------------------------------*/

TEST_CASE("SIP Lexer: mul / div operator associativity, pt1", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 * 2 / 3; })";
    std::string expected = "(expr (expr 1) * (expr 2)) / (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Lexer: mul / div operator associativity, pt2", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 / 2 * 3; })";
    std::string expected = "(expr (expr 1) / (expr 2)) * (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Lexer: mul / mod operator associativity, pt1", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 % 2 * 3; })";
    std::string expected = "(expr (expr 1) % (expr 2)) * (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Lexer: mul / mod operator associativity, pt2", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 * 2 % 3; })";
    std::string expected = "(expr (expr 1) * (expr 2)) % (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}
//thus, we know that the mul, mod, and div operators are lexically equivalent, with left to right associativity.

TEST_CASE("SIP Lexer: add / sub operator associativity, pt1", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 + 2 - 3; })";
    std::string expected = "(expr (expr 1) + (expr 2)) - (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Lexer: add / sub operator associativity, pt2", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 - 2 + 3; })";
    std::string expected = "(expr (expr 1) - (expr 2)) + (expr 3))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}
//thus, we know that the add and sub operators are lexically equivalent, with left to right associativity.

TEST_CASE("SIP Lexer: mul / add operator precedence test", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 + 2 * 3; })";
    std::string expected = "(expr (expr 1) + (expr (expr 2) * (expr 3)))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Lexer: checking equal relational operator associativity", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() {
        var x, y, z, w, a, b, c, d;
        x = 1 > 2 < 3;
        y = 4 < 5 >= 6;
        z = 7 >= 8 <= 9;
        w = 10 <= 11 > 12;
        a = 13 < 14 > 15;
        b = 16 >= 17 < 18;
        c = 19 <= 20 >= 21;
        d = 22 > 23 <= 24;
    })";
    std::string expected1 = "(expr (expr 1) > (expr 2)) < (expr 3))";
    std::string expected2 = "(expr (expr 4) < (expr 5)) >= (expr 6))";
    std::string expected3 = "(expr (expr 7) >= (expr 8)) <= (expr 9))";
    std::string expected4 = "(expr (expr 10) <= (expr 11)) > (expr 12))";
    std::string expected5 = "(expr (expr 13) < (expr 14)) > (expr 15))";
    std::string expected6 = "(expr (expr 16) >= (expr 17)) < (expr 18))";
    std::string expected7 = "(expr (expr 19) <= (expr 20)) >= (expr 21))";
    std::string expected8 = "(expr (expr 22) > (expr 23)) <= (expr 24))";
    std::string tree = ParserHelper::parsetree(stream);
    bool test = tree.find(expected1) != std::string::npos &&
                tree.find(expected2) != std::string::npos &&
                tree.find(expected3) != std::string::npos &&
                tree.find(expected4) != std::string::npos &&
                tree.find(expected5) != std::string::npos &&
                tree.find(expected6) != std::string::npos &&
                tree.find(expected7) != std::string::npos &&
                tree.find(expected8) != std::string::npos;
    REQUIRE(test);
}

TEST_CASE("SIP Lexer: checking additive / relational operator precedence", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() {
        var x, y;
        x = 1 + 2 >= 3;
        y = 4 < 5 - 6;
    })";
    std::string expected1 = "(expr (expr 1) + (expr 2)) >= (expr 3))";
    std::string expected2 = "(expr (expr 4) < (expr (expr 5) - (expr 6)))";
    std::string tree = ParserHelper::parsetree(stream);
    bool test = tree.find(expected1) != std::string::npos &&
                tree.find(expected2) != std::string::npos;
    REQUIRE(test);
}

TEST_CASE("SIP Lexer: checking eq / ne operator associativity", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() {
        var x, y;
        x = 1 == 2 != 3;
        y = 4 != 5 == 6;
    })";
    std::string expected1 = "(expr (expr 1) == (expr 2)) != (expr 3))";
    std::string expected2 = "(expr (expr 4) != (expr 5)) == (expr 6))";
    std::string tree = ParserHelper::parsetree(stream);
    bool test = tree.find(expected1) != std::string::npos &&
                tree.find(expected2) != std::string::npos;
    REQUIRE(test);
}

TEST_CASE("SIP Lexer: checking relational / equality operator precedence", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() {
        var x, y;
        x = 1 >= 2 != 3;
        y = 4 == 5 < 6;
    })";
    std::string expected1 = "(expr (expr 1) >= (expr 2)) != (expr 3))";
    std::string expected2 = "(expr (expr 4) == (expr (expr 5) < (expr 6)))";
    std::string tree = ParserHelper::parsetree(stream);
    bool test = tree.find(expected1) != std::string::npos &&
                tree.find(expected2) != std::string::npos;
    REQUIRE(test);
}

TEST_CASE("SIP Lexer: add higher precedence than gt", "[SIP Lexer]") {
    std::stringstream stream;
    stream << R"(main() { return 1 > 2 + 3; })";
    std::string expected = "(expr (expr 1) > (expr (expr 2) + (expr 3)))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

// these tests check new operators.
TEST_CASE("SIP Lexer: new relational op, LE", "[SIP Lexer]") {
std::stringstream stream;
stream << R"(
      operators() { var x; if (x <= 0) x = x + 1; return x; }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: new op, modulo", "[SIP Lexer]") {
std::stringstream stream;
stream << R"(
      operators() { var x; if (x == 0) x = x % 2; return x; }
    )";

REQUIRE(ParserHelper::is_parsable(stream));
}
