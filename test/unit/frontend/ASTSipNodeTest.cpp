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
    // TIP
    void endVisit(ASTVariableExpr *element) override { captureResults(element); }
    void endVisit(ASTBinaryExpr *element) override { captureResults(element); }
    void endVisit(ASTNumberExpr *element) override { captureResults(element); }
    void endVisit(ASTOutputStmt *element) override { captureResults(element); }
    // SIP
    void endVisit(ASTBoolExpr *element) override { captureResults(element); }
    void endVisit(ASTTernaryExpr *element) override { captureResults(element); }
    void endVisit(ASTForRangeStmt *element) override { captureResults(element); }
    void endVisit(ASTForEachStmt *element) override { captureResults(element); }
    void endVisit(ASTArrExpr *element) override { captureResults(element); }
    void endVisit(ASTArrOfExpr *element) override { captureResults(element); }
    void endVisit(ASTArrElemRefExpr *element) override { captureResults(element); }
    void endVisit(ASTUnaryExpr *element) override { captureResults(element); }
    void endVisit(ASTIncDecStmt *element) override { captureResults(element); }
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
    REQUIRE(trueVisitor.resultStrings.at(0) == "true");

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
    REQUIRE(falseVisitor.resultStrings.at(0) == "false");

    std::stringstream printFalseNode;
    printFalseNode << *FalseNode;
    REQUIRE(printFalseNode.str() == "false");
}

TEST_CASE("ASTSipNodeTest: ternary node", "[ASTSipNode]") {
    // make an ASTTernaryExpr node
    auto x = std::make_shared<ASTVariableExpr>("x");
    auto y = std::make_shared<ASTVariableExpr>("y");
    std::string op = ">";
    auto cond = std::make_shared<ASTBinaryExpr>(op, x, y);
    auto left = std::make_shared<ASTNumberExpr>(1);
    auto right = std::make_shared<ASTNumberExpr>(0);
    auto ternNode = std::make_shared<ASTTernaryExpr>(cond, left, right);

    // test the getters
    REQUIRE(ternNode->getCond() == cond.get());
    REQUIRE(ternNode->getTrue() == left.get());
    REQUIRE(ternNode->getFalse() == right.get());

    // make sure it has 3 children
    REQUIRE(ternNode->getChildren().size() == 3);
    bool condFound, leftFound, rightFound;
    for(auto &child : ternNode->getChildren()){
        if(child.get() == cond.get()){
            condFound = true;
        } else if(child.get() == left.get()){
            leftFound = true;
        } else if(child.get() == right.get()){
            rightFound = true;
        }
    }
    REQUIRE((condFound && leftFound && rightFound));

    // test the accept method
    EndVisitResults ternVisitor;
    ternNode->accept(&ternVisitor);
    std::string expected[] = {"x","y","(x>y)","1","0","(x>y) ? 1 : 0"};
    for (int i=0; i < 6; i++) {
        REQUIRE(ternVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printTernNode;
    printTernNode << *ternNode;
    REQUIRE(printTernNode.str() == "(x>y) ? 1 : 0");
}

TEST_CASE("ASTSipNodeTest: for range with step node", "[ASTSipNode]") {
    // make an ASTForRangeStmt node
    auto iter = std::make_shared<ASTVariableExpr>("i");
    auto start = std::make_shared<ASTNumberExpr>(0);
    auto end = std::make_shared<ASTNumberExpr>(10);
    auto step = std::make_shared<ASTNumberExpr>(2);
    auto body = std::make_shared<ASTOutputStmt>(std::make_shared<ASTVariableExpr>("bodyContents"));
    auto forRangeNode = std::make_shared<ASTForRangeStmt>(iter, start, end, step, body);

    // test the getters
    REQUIRE(forRangeNode->getIter() == iter.get());
    REQUIRE(forRangeNode->getRStart() == start.get());
    REQUIRE(forRangeNode->getREnd() == end.get());
    REQUIRE(forRangeNode->getStep() == step.get());
    REQUIRE(forRangeNode->getBody() == body.get());

    // make sure it has 5 children
    REQUIRE(forRangeNode->getChildren().size() == 5);
    bool iterFound, startFound, endFound, stepFound, bodyFound;
    for(auto &child : forRangeNode->getChildren()){
        if(child.get() == iter.get()){
            iterFound = true;
        } else if(child.get() == start.get()){
            startFound = true;
        } else if(child.get() == end.get()){
            endFound = true;
        } else if(child.get() == step.get()){
            stepFound = true;
        } else if(child.get() == body.get()){
            bodyFound = true;
        }
    }
    REQUIRE((iterFound && startFound && endFound && stepFound && bodyFound));

    // test the accept method
    EndVisitResults forRangeVisitor;
    forRangeNode->accept(&forRangeVisitor);
    std::string expected[] = {"i","0","10","2","bodyContents","output bodyContents;","for (i : 0 .. 10 by 2) output bodyContents;"};
    for (int i=0; i < 7; i++) {
        REQUIRE(forRangeVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printForRangeNode;
    printForRangeNode << *forRangeNode;
    REQUIRE(printForRangeNode.str() == "for (i : 0 .. 10 by 2) output bodyContents;");
}

TEST_CASE("ASTSipNodeTest: for range without step node", "[ASTSipNode]") {
    // make an ASTForRangeStmt node
    auto iter = std::make_shared<ASTVariableExpr>("i");
    auto start = std::make_shared<ASTNumberExpr>(0);
    auto end = std::make_shared<ASTNumberExpr>(10);
    auto step = nullptr;
    auto body = std::make_shared<ASTOutputStmt>(std::make_shared<ASTVariableExpr>("bodyContents"));
    auto forRangeNode = std::make_shared<ASTForRangeStmt>(iter, start, end, step, body);

    // test the getters
    REQUIRE(forRangeNode->getIter() == iter.get());
    REQUIRE(forRangeNode->getRStart() == start.get());
    REQUIRE(forRangeNode->getREnd() == end.get());
    REQUIRE(forRangeNode->getStep() == nullptr);
    REQUIRE(forRangeNode->getBody() == body.get());

    // make sure it has 4 children
    REQUIRE(forRangeNode->getChildren().size() == 4);
    bool iterFound, startFound, endFound, bodyFound;
    for(auto &child : forRangeNode->getChildren()){
        if(child.get() == iter.get()){
            iterFound = true;
        } else if(child.get() == start.get()){
            startFound = true;
        } else if(child.get() == end.get()){
            endFound = true;
        } else if(child.get() == body.get()){
            bodyFound = true;
        }
    }
    REQUIRE((iterFound && startFound && endFound && bodyFound));

    // test the accept method
    EndVisitResults forRangeVisitor;
    forRangeNode->accept(&forRangeVisitor);
    std::string expected[] = {"i","0","10","bodyContents","output bodyContents;","for (i : 0 .. 10) output bodyContents;"};
    for (int i=0; i < 6; i++) {
        REQUIRE(forRangeVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printForRangeNode;
    printForRangeNode << *forRangeNode;
    REQUIRE(printForRangeNode.str() == "for (i : 0 .. 10) output bodyContents;");
}

TEST_CASE("ASTSipNodeTest: for each node", "[ASTSipNode]") {
    // make an ASTForRangeStmt node
    auto item = std::make_shared<ASTVariableExpr>("x");
    auto list = std::make_shared<ASTVariableExpr>("y");
    auto body = std::make_shared<ASTOutputStmt>(std::make_shared<ASTVariableExpr>("bodyContents"));
    auto forEachNode = std::make_shared<ASTForEachStmt>(item, list, body);

    // test the getters
    REQUIRE(forEachNode->getItem() == item.get());
    REQUIRE(forEachNode->getList() == list.get());
    REQUIRE(forEachNode->getBody() == body.get());

    // make sure it has 3 children
    REQUIRE(forEachNode->getChildren().size() == 3);
    bool itemFound, listFound, bodyFound;
    for(auto &child : forEachNode->getChildren()){
        if(child.get() == item.get()){
            itemFound = true;
        } else if(child.get() == list.get()){
            listFound = true;
        } else if(child.get() == body.get()){
            bodyFound = true;
        }
    }
    REQUIRE((itemFound && listFound && bodyFound));

    // test the accept method
    EndVisitResults forEachVisitor;
    forEachNode->accept(&forEachVisitor);
    std::string expected[] = {"x","y","bodyContents","output bodyContents;","for (x : y) output bodyContents;"};
    for (int i=0; i < 5; i++) {
        REQUIRE(forEachVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printForEachNode;
    printForEachNode << *forEachNode;
    REQUIRE(printForEachNode.str() == "for (x : y) output bodyContents;");
}

TEST_CASE("ASTSipNodeTest: array node", "[ASTSipNode]") {
    // make an ASTArrExpr node
    auto zero = std::make_shared<ASTVariableExpr>("x");
    auto one = std::make_shared<ASTVariableExpr>("y");
    auto two = std::make_shared<ASTVariableExpr>("z");
    std::vector<std::shared_ptr<ASTExpr>> items{zero, one, two};
    std::vector<ASTExpr*> vals{zero.get(), one.get(), two.get()};
    auto arrNode = std::make_shared<ASTArrExpr>(items);

    // test the getter
    auto elements = arrNode->getElements();
    std::vector<std::shared_ptr<ASTExpr>> compare;
    REQUIRE(elements == vals);
    for(int i = 0; i < elements.size(); i++){
        REQUIRE(elements[i] == vals[i]);
    }

    // make sure it has 3 children
    REQUIRE(arrNode->getChildren().size() == 3);
    bool zeroFound, oneFound, twoFound;
    for(auto &child : arrNode->getChildren()){
        if(child.get() == vals[0]){
            zeroFound = true;
        } else if(child.get() == vals[1]){
            oneFound = true;
        } else if(child.get() == vals[2]){
            twoFound = true;
        }
    }
    REQUIRE((zeroFound && oneFound && twoFound));

    // test the accept method
    EndVisitResults arrVisitor;
    arrNode->accept(&arrVisitor);
    std::string expected[] = {"x","y","z","[x,y,z]"};
    for (int i=0; i < 3; i++) {
        REQUIRE(arrVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printArrNode;
    printArrNode << *arrNode;
    REQUIRE(printArrNode.str() == "[x,y,z]");
}

TEST_CASE("ASTSipNodeTest: array of node", "[ASTSipNode]") {
    // make an ASTArrOfExpr node
    auto left = std::make_shared<ASTVariableExpr>("x");
    auto right = std::make_shared<ASTVariableExpr>("y");
    auto arrOfNode = std::make_shared<ASTArrOfExpr>(left, right);

    // test the getter
    REQUIRE(arrOfNode->getLeft() == left.get());
    REQUIRE(arrOfNode->getRight() == right.get());

    // make sure it has 2 children
    REQUIRE(arrOfNode->getChildren().size() == 2);
    bool leftFound, rightFound;
    for(auto &child : arrOfNode->getChildren()){
        if(child.get() == left.get()){
            leftFound = true;
        } else if(child.get() == right.get()){
            rightFound = true;
        }
    }
    REQUIRE((leftFound && rightFound));

    // test the accept method
    EndVisitResults arrOfVisitor;
    arrOfNode->accept(&arrOfVisitor);
    std::string expected[] = {"x","y","[x of y]"};
    for (int i=0; i < 3; i++) {
        REQUIRE(arrOfVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printArrOfNode;
    printArrOfNode << *arrOfNode;
    REQUIRE(printArrOfNode.str() == "[x of y]");
}

TEST_CASE("ASTSipNodeTest: array elem ref node", "[ASTSipNode]") {
    // make an ASTArrElemRefExpr node
    auto ptr = std::make_shared<ASTVariableExpr>("x");
    auto index = std::make_shared<ASTNumberExpr>(0);
    auto arrElemRefNode = std::make_shared<ASTArrElemRefExpr>(ptr, index);

    // test the getter
    REQUIRE(arrElemRefNode->getPtr() == ptr.get());
    REQUIRE(arrElemRefNode->getIndex() == index.get());

    // make sure it has 2 children
    REQUIRE(arrElemRefNode->getChildren().size() == 2);
    bool ptrFound, indexFound;
    for(auto &child : arrElemRefNode->getChildren()){
        if(child.get() == ptr.get()){
            ptrFound = true;
        } else if(child.get() == index.get()){
            indexFound = true;
        }
    }
    REQUIRE((ptrFound && indexFound));

    // test the accept method
    EndVisitResults arrElemRefVisitor;
    arrElemRefNode->accept(&arrElemRefVisitor);
    std::string expected[] = {"x","0","x[0]"};
    for (int i=0; i < 3; i++) {
        REQUIRE(arrElemRefVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printArrElemRefNode;
    printArrElemRefNode << *arrElemRefNode;
    REQUIRE(printArrElemRefNode.str() == "x[0]");
}

TEST_CASE("ASTSipNodeTest: unary len op node", "[ASTSipNode]") {
    // make an ASTUnaryExpr node for '#'
    std::string op = "#";
    auto right = std::make_shared<ASTVariableExpr>("x");
    auto lenNode = std::make_shared<ASTUnaryExpr>(op, right);

    // test the getter
    REQUIRE(lenNode->getOp() == op);
    REQUIRE(lenNode->getRight() == right.get());


    // make sure it has 1 child
    REQUIRE(lenNode->getChildren().size() == 1);
    REQUIRE(lenNode->getChildren().back().get() == right.get());


    // test the accept method
    EndVisitResults lenVisitor;
    lenNode->accept(&lenVisitor);
    std::string expected[] = {"x","#x"};
    for (int i=0; i < 2; i++) {
        REQUIRE(lenVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printLenNode;
    printLenNode << *lenNode;
    REQUIRE(printLenNode.str() == "#x");
}

TEST_CASE("ASTSipNodeTest: unary not op node", "[ASTSipNode]") {
    // make an ASTUnaryExpr node for "not"
    std::string op = "not";
    auto right = std::make_shared<ASTVariableExpr>("x");
    auto notNode = std::make_shared<ASTUnaryExpr>(op, right);

    // test the getter
    REQUIRE(notNode->getOp() == op);
    REQUIRE(notNode->getRight() == right.get());


    // make sure it has 1 child
    REQUIRE(notNode->getChildren().size() == 1);
    REQUIRE(notNode->getChildren().back().get() == right.get());


    // test the accept method
    EndVisitResults notVisitor;
    notNode->accept(&notVisitor);
    std::string expected[] = {"x","not x"};
    for (int i=0; i < 2; i++) {
        REQUIRE(notVisitor.resultStrings.at(i) == expected[i]);
    }

    // test the print method
    std::stringstream printNotNode;
    printNotNode << *notNode;
    REQUIRE(printNotNode.str() == "not x");
}

TEST_CASE("ASTSipNodeTest: inc dec stmt node", "[ASTSipNode]") {
    // make an inc and a dec node
    std::string opInc = "++";
    auto leftInc = std::make_shared<ASTVariableExpr>("x");
    auto incNode = std::make_shared<ASTIncDecStmt>(leftInc, opInc);

    // test the getter
    REQUIRE(incNode->getLeft() == leftInc.get());
    REQUIRE(incNode->getOp() == opInc);

    // make sure it has 1 child
    REQUIRE(incNode->getChildren().size() == 1);
    REQUIRE(incNode->getChildren().back().get() == leftInc.get());

    // test the accept method
    EndVisitResults incVisitor;
    incNode->accept(&incVisitor);
    std::string expectedInc[] = {"x","x++;"};
    for (int i=0; i < 2; i++) {
        REQUIRE(incVisitor.resultStrings.at(i) == expectedInc[i]);
    }

    // test the print method
    std::stringstream printIncNode;
    printIncNode << *incNode;
    REQUIRE(printIncNode.str() == "x++;");

    std::string opDec = "--";
    auto leftDec = std::make_shared<ASTVariableExpr>("y");
    auto decNode = std::make_shared<ASTIncDecStmt>(leftDec, opDec);

    REQUIRE(decNode->getLeft() == leftDec.get());
    REQUIRE(decNode->getOp() == opDec);

    REQUIRE(decNode->getChildren().size() == 1);
    REQUIRE(decNode->getChildren().back().get() == leftDec.get());

    EndVisitResults decVisitor;
    decNode->accept(&decVisitor);
    std::string expectedDec[] = {"y","y--;"};
    for (int i=0; i < 2; i++) {
        REQUIRE(decVisitor.resultStrings.at(i) == expectedDec[i]);
    }

    std::stringstream printDecNode;
    printDecNode << *decNode;
    REQUIRE(printDecNode.str() == "y--;");
}