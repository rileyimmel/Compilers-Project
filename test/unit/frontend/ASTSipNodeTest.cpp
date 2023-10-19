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

    void endVisit(ASTVariableExpr * element) override { captureResults(element); }
    void endVisit(ASTBinaryExpr * element) override { captureResults(element); }
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

TEST_CASE("ASTSipNodeTest: ternary node", "[ASTSipNode]") {
    // make an ASTTernaryNode
    auto x = std::make_shared<ASTVariableExpr>("x");
    auto y = std::make_shared<ASTVariableExpr>("y");
    std::string op = ">";
    auto cond = std::make_shared<ASTBinaryExpr>(op, x, y);
    auto left = std::make_shared<ASTNumberExpr>(1);
    auto right = std::make_shared<ASTNumberExpr>(0);
    auto ternNode = std::make_shared<ASTTernaryExpr>(cond, left, right);

    // test the getters
    auto condVal = cond.get();
    REQUIRE(ternNode->getCond() == condVal);

    auto leftVal = left.get();
    REQUIRE(ternNode->getTrue() == leftVal);

    auto rightVal = right.get();
    REQUIRE(ternNode->getFalse() == rightVal);

    // make sure it has 3 children
    REQUIRE(ternNode->getChildren().size() == 3);
    bool condFound, leftFound, rightFound;
    for(auto &child : ternNode->getChildren()){
        auto childVal = child.get();
        if(childVal == condVal){
            condFound = true;
        } else if(childVal == leftVal){
            leftFound = true;
        } else if(childVal == rightVal){
            rightFound = true;
        }
    }
    REQUIRE((condFound && leftFound && rightFound));

    // test the accept method
    EndVisitResults ternVisitor;
    ternNode->accept(&ternVisitor);
    std::string expected[] = {"x","y","(x>y)"};
    for (int i=0; i < 3; i++) {
        REQUIRE(ternVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printTernNode;
    printTernNode << *ternNode;
    REQUIRE(printTernNode.str() == "(x>y) ? 1 : 0");
}