#include "AST.h"
#include "ASTVisitor.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <vector>
#include <string>


class EndVisitResults : public ASTVisitor {
public:
    std::vector<std::string> resultStrings;
    void captureResults(ASTNode *element) {
        std::stringstream ss; ss << *element; resultStrings.push_back(ss.str());
    }
};

TEST_CASE("ASTSipNodeTest: boolean nodes", "[ASTSipNode]") {
    // true node
    // make an ASTBoolExpr node
    auto TrueNode = std::make_shared<ASTBoolExpr>("true");

    // test the getValue function
    REQUIRE(TrueNode->getValue() == "true");

    // make sure it has no children
    REQUIRE(TrueNode->getChildren().empty());

    // test the accept method
    EndVisitResults trueVisitor;
    TrueNode->accept(&trueVisitor);
    REQUIRE(trueVisitor.resultStrings.empty());

    // test the print method
    std::stringstream printTrueNode;
    printTrueNode << *TrueNode;
    REQUIRE(printTrueNode.str() == "true");

    // false node
    auto FalseNode = std::make_shared<ASTBoolExpr>("false");

    REQUIRE(FalseNode->getValue() == "false");

    REQUIRE(FalseNode->getChildren().empty());

    EndVisitResults falseVisitor;
    FalseNode->accept(&falseVisitor);
    REQUIRE(falseVisitor.resultStrings.empty());

    std::stringstream printFalseNode;
    printFalseNode << *FalseNode;
    REQUIRE(printFalseNode.str() == "false");
}