/*
 *
 * copies the style of "TEST_CASE("Unifier: Collect and then unify constraints", "[Unifier, Collect]")" in UnifierTest.cpp
 *
 */
#include "Unifier.h"
#include "ASTHelper.h"
#include "ASTVariableExpr.h"
#include "TipAlpha.h"
#include "TipFunction.h"
#include "TipInt.h"
#include "TipMu.h"
#include "TipRef.h"
#include "TipBool.h"
#include "TipArray.h"
#include "TypeConstraintCollectVisitor.h"
#include "TypeConstraintUnifyVisitor.h"
#include "TypeConstraintVisitor.h"
#include "UnificationError.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("SIP Semantic: Collect and then unify constraints", "[Unifier, Collect]") {

    SECTION("Test SIP type-safe program 1") {
    std::stringstream program;
    program << R"(
                // x is bool, y is [] int, z is int, short is () -> int
                short() {
                  var x, y, z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v;
                  x = true;                          // bool
                  y = [1,2,3];                       // [] int
                  z = y[1];                          // int
                  a = #y;                            // int
                  b = not x;                         // bool
                  c = 1;                             // int
                  d = -c;                            // int
                  e = 1;                             // int
                  e++;                               // int
                  f = 1;                             // int
                  f--;                               // int
                  l = 5;                             // int
                  m = 6;                             // int
                  g = l > m ? 5 : -5;                // int
                  for (h:y) { h--; }
                  for (1 : 2 .. 5 by 2) { i = 1; }
                  j = true;                          // bool
                  k = [5 of j];                      // [] bool
                  n = [];                            // [] \alpha
                  o = #n;                            // int
                  p = true;                          // bool
                  q = true;                          // bool
                  r = false;                         // bool
                  s = p and q;                       // bool
                  t = q and r;                       // bool
                  u = p or q;                        // bool
                  v = r or false;                    // bool
                  return z;                          // () -> int
                }
             )";

    auto ast = ASTHelper::build_ast(program);
    auto symbols = SymbolTable::build(ast.get());

    TypeConstraintCollectVisitor visitor(symbols.get());
    ast->accept(&visitor);

    Unifier unifier(visitor.getCollectedConstraints());
    REQUIRE_NOTHROW(unifier.solve());

    // Expected types
    std::vector<std::shared_ptr<TipType>> emptyParams;
    auto intType = std::make_shared<TipInt>();
    auto funRetInt = std::make_shared<TipFunction>(emptyParams, intType);
    auto boolType = std::make_shared<TipBool>();
    auto arrayIntType = std::make_shared<TipArray>(std::make_shared<TipInt>());
    auto arrayBoolType = std::make_shared<TipArray>(std::make_shared<TipBool>());

    auto fDecl = symbols->getFunction("short");
    auto fType = std::make_shared<TipVar>(fDecl);

    REQUIRE(*unifier.inferred(fType) == *funRetInt);

    auto xType = std::make_shared<TipVar>(symbols->getLocal("x", fDecl));
    REQUIRE(*unifier.inferred(xType) == *boolType);

    auto yType = std::make_shared<TipVar>(symbols->getLocal("y", fDecl));
    REQUIRE(*unifier.inferred(yType) == *arrayIntType);

    auto zType = std::make_shared<TipVar>(symbols->getLocal("z", fDecl));
    REQUIRE(*unifier.inferred(zType) == *intType);

    auto aType = std::make_shared<TipVar>(symbols->getLocal("a", fDecl));
    REQUIRE(*unifier.inferred(aType) == *intType);

    auto bType = std::make_shared<TipVar>(symbols->getLocal("b", fDecl));
    REQUIRE(*unifier.inferred(bType) == *boolType);

    auto cType = std::make_shared<TipVar>(symbols->getLocal("c", fDecl));
    REQUIRE(*unifier.inferred(cType) == *intType);

    auto dType = std::make_shared<TipVar>(symbols->getLocal("d", fDecl));
    REQUIRE(*unifier.inferred(dType) == *intType);

    auto eType = std::make_shared<TipVar>(symbols->getLocal("e", fDecl));
    REQUIRE(*unifier.inferred(eType) == *intType);

    auto ffType = std::make_shared<TipVar>(symbols->getLocal("f", fDecl));
    REQUIRE(*unifier.inferred(ffType) == *intType);

    auto gType = std::make_shared<TipVar>(symbols->getLocal("g", fDecl));
    REQUIRE(*unifier.inferred(gType) == *intType);

    auto hType = std::make_shared<TipVar>(symbols->getLocal("h", fDecl));
    REQUIRE(*unifier.inferred(hType) == *intType);

    auto iType = std::make_shared<TipVar>(symbols->getLocal("i", fDecl));
    REQUIRE(*unifier.inferred(iType) == *intType);

    auto jType = std::make_shared<TipVar>(symbols->getLocal("j", fDecl));
    REQUIRE(*unifier.inferred(jType) == *boolType);

    auto kType = std::make_shared<TipVar>(symbols->getLocal("k", fDecl));
    REQUIRE(*unifier.inferred(kType) == *arrayBoolType);

    auto oType = std::make_shared<TipVar>(symbols->getLocal("o", fDecl));
    REQUIRE(*unifier.inferred(oType) == *intType);

    auto pType = std::make_shared<TipVar>(symbols->getLocal("p", fDecl));
    REQUIRE(*unifier.inferred(pType) == *boolType);

    auto qType = std::make_shared<TipVar>(symbols->getLocal("q", fDecl));
    REQUIRE(*unifier.inferred(qType) == *boolType);

    auto rType = std::make_shared<TipVar>(symbols->getLocal("r", fDecl));
    REQUIRE(*unifier.inferred(rType) == *boolType);

    auto sType = std::make_shared<TipVar>(symbols->getLocal("s", fDecl));
    REQUIRE(*unifier.inferred(sType) == *boolType);

    auto tType = std::make_shared<TipVar>(symbols->getLocal("t", fDecl));
    REQUIRE(*unifier.inferred(tType) == *boolType);

    auto uType = std::make_shared<TipVar>(symbols->getLocal("u", fDecl));
    REQUIRE(*unifier.inferred(uType) == *boolType);

    auto vType = std::make_shared<TipVar>(symbols->getLocal("v", fDecl));
    REQUIRE(*unifier.inferred(vType) == *boolType);

    auto nType = std::make_shared<TipVar>(symbols->getLocal("n", fDecl));
    auto alphaN = std::make_shared<TipArray>(std::make_shared<TipAlpha>(symbols->getLocal("n", fDecl)));
//    std::cout << "alphaNType " << *alphaN << "\n";
//    std::cout << "gType " << *unifier.inferred(gType) << "\n";
//    std::cout << "nType " << *unifier.inferred(nType) << "\n";

//    REQUIRE(std::dynamic_pointer_cast<TipAlpha>(nType));

    }

    SECTION("SIP Test unification error 1") {
    std::stringstream program;
    program << R"(
                bar() {
                    var r;
                    r = [1+1, true, 42];
                    return 42;
                }
            )";

    auto ast = ASTHelper::build_ast(program);
    auto symbols = SymbolTable::build(ast.get());

    TypeConstraintCollectVisitor visitor(symbols.get());
    ast->accept(&visitor);

    Unifier unifier(visitor.getCollectedConstraints());
    REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    }
    //
    //SECTION("Test unification error 2") {
    //std::stringstream program;
    //program << R"(
    //            foo(p) {
    //                return *p;
    //            }
    //
    //            main() {
    //                var x;
    //                x = 5;
    //                x = foo;
    //                return 4;
    //            }
    //        )";
    //
    //auto ast = ASTHelper::build_ast(program);
    //auto symbols = SymbolTable::build(ast.get());
    //
    //TypeConstraintCollectVisitor visitor(symbols.get());
    //ast->accept(&visitor);
    //
    //Unifier unifier(visitor.getCollectedConstraints());
    //REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    //}
    //
    //SECTION("Test unification error 3") {
    //std::stringstream program;
    //program << R"(
    //            main() {
    //                var x, y;
    //                x = 5;
    //                y = 10;
    //                x = &y;
    //                return 4;
    //            }
    //        )";
    //
    //auto ast = ASTHelper::build_ast(program);
    //auto symbols = SymbolTable::build(ast.get());
    //
    //TypeConstraintCollectVisitor visitor(symbols.get());
    //ast->accept(&visitor);
    //
    //Unifier unifier(visitor.getCollectedConstraints());
    //REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    //}
}


