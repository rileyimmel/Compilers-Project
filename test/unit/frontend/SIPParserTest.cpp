#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SIP Parser: for each", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x, y, z;
			  for ( x : x ) {
			 	  z = z + 1;
			  }
        return z;
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

TEST_CASE("SIP Parser: operators", "[SIP Parser]") {
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

/* These tests checks for operator precedence.
 * They access the parse tree and ensure that the higher precedence
 * operator is nested more deeply than the lower precedence operator.
 */

/*------------------------------*/

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

/************ The following are expected to fail parsing ************/

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
