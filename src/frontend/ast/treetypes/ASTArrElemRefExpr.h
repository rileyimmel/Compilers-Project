#pragma once

#include "ASTExpr.h"

/*! \brief Class for referencing an element of an array
 * E1[E2]
 * */
class ASTArrElemRefExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> PTR, INDEX;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTArrElemRefExpr(std::shared_ptr<ASTExpr> PTR, std::shared_ptr<ASTExpr> INDEX) : PTR(PTR), INDEX(INDEX) {}
    ASTExpr *getPtr() const { return PTR.get(); }
    ASTExpr *getIndex() const { return INDEX.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};