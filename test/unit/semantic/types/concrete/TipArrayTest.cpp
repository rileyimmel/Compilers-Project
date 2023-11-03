#include "TipArray.h"
#include "TipVar.h"
#include "TipInt.h"
#include "TipBool.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipArray: test TipArray is a TipCons"
          "[tip_array]") {
  auto intType = std::make_shared<TipInt>();
  TipArray t(intType);
  REQUIRE_FALSE(nullptr == dynamic_cast<TipCons *>(&t));
}

TEST_CASE("TipArray: test TipArray is a TipType"
          "[tip_array]") {
  auto intType = std::make_shared<TipInt>();
  TipArray t(intType);
  REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&t));
}

TEST_CASE("TipArray: test toString returns [] \alpha, using int here", "[tip_array]") {
  auto intType = std::make_shared<TipInt>();
  TipArray t(intType);
  std::stringstream stream;
  stream << t;
  REQUIRE("[] int" == stream.str());
}

TEST_CASE("TipArray: test equality", "[tip_array]") {
  auto intType = std::make_shared<TipInt>();
  TipArray t1(intType);
  auto elementsOf1 = t1.getElems();

  SECTION("same types and lengths") {
    TipArray t2(intType);
    auto elementsOf2 = t2.getElems();

    REQUIRE(t1 == t2);
    REQUIRE(elementsOf1.size() == elementsOf2.size());
  }

  SECTION("different types") {
    TipArray t2(std::make_shared<TipBool>());
    auto elementsOf2 = t2.getElems();

    REQUIRE(t1 != t2);
  }

  SECTION("array type different from element type") {
    TipInt tipInt;

    REQUIRE(t1 != tipInt);
  }
}

TEST_CASE("TipArray: test get elements", "[tip_array]") {
  auto intType = std::make_shared<TipInt>();
  TipArray t(intType);
  REQUIRE(!t.getElems().empty());
}