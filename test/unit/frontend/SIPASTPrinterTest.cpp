#include "ASTHelper.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>



TEST_CASE("SIPASTPrinterTest: sip statement printers", "[SIPASTNodePrint]") {
    std::stringstream stream;
    stream << R"(
      fun() {
        var x, y, z, a, b;
        y = 1;
        a = 10;
        for(x : y .. a by b) {
            b = 6;
        }
        for (x : y .. a) {
            b = 6;
        }
        for (x : y) {
            b = 6;
        }
        x = 1;
        x++;
        x--;
        return 0;
      }
    )";

    std::vector<std::string> expected{"var x, y, z, a, b;",
                                      "y = 1;",
                                      "a = 10;",
                                      "for (x : y .. a by b) { b = 6; }",
                                      "for (x : y .. a) { b = 6; }",
                                      "for (x : y) { b = 6; }",
                                      "x = 1;",
                                      "x++;",
                                      "x--;",
                                      "return 0;"};

    auto ast = ASTHelper::build_ast(stream);

    auto f = ast->findFunctionByName("fun");

    int i = 0;
    for (auto d : f->getDeclarations()) {
        stream = std::stringstream();
        stream << *d;
        auto actual = stream.str();
        REQUIRE(actual == expected.at(i++));
    }

    for (auto s : f->getStmts()) {
        stream = std::stringstream();
        stream << *s;
        auto actual = stream.str();
        REQUIRE(actual == expected.at(i++));
    }
}

TEST_CASE("SIPASTPrinterTest: SIP expression printers", "[SIPASTNodePrint]") {
    std::stringstream stream;
    stream << R"(
      fun() {
        var x, y, z;
        x = true;
        y = false;
        x = y < z ? y : z;
        y = [1,2,3];
        x = [1 of 2];
        z = y[0];
        x = #y;
        y = not false;
        y = -1;
        z = -y;
        x = y and z;
        x = y or z;
        x = y % z;
        return 0;
      }
    )";

    std::vector<std::string> expected{"true",
                                      "false",
                                      "(y<z) ? y : z",
                                      "[1,2,3]",
                                      "[1 of 2]",
                                      "y[0]",
                                      "#y",
                                      "not false",
                                      "-1",
                                      "-y",
                                      "(yandz)",
                                      "(yorz)",
                                      "(y%z)"};

    auto ast = ASTHelper::build_ast(stream);

    auto f = ast->findFunctionByName("fun");

    int i = 0;
    int numStmts = f->getStmts().size() - 1; // skip the return
    for (auto s : f->getStmts()) {
        auto a = dynamic_cast<ASTAssignStmt *>(s);
        stream = std::stringstream();
        stream << *a->getRHS();
        auto actual = stream.str();
        REQUIRE(actual == expected.at(i++));
        if (i == numStmts)
            break;
    }
}

TEST_CASE("SIPASTPrinterTest: conditional expression printers", "[SIPASTNodePrint]") {
    std::stringstream stream;
    stream << R"(
      fun() {
        var x, y, z;
        if (x >= y) x = 0;
        if (x <= y) x = 0;
        if (x > y) x = 0;
        if (x < y) x = 0;
        return 0;
      }
    )";

    std::vector<std::string> expected{"(x>=y)", "(x<=y)", "(x>y)", "(x<y)"};

    auto ast = ASTHelper::build_ast(stream);

    auto f = ast->findFunctionByName("fun");

    int i = 0;
    int numStmts = f->getStmts().size() - 1; // skip the return
    for (auto s : f->getStmts()) {
        auto ifstmt = dynamic_cast<ASTIfStmt *>(s);
        stream = std::stringstream();
        stream << *ifstmt->getCondition();
        auto actual = stream.str();
        REQUIRE(actual == expected.at(i++));
        if (i == numStmts)
            break;
    }
}