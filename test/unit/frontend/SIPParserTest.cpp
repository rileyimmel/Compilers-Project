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
