#pragma once

#include "ASTExpr.h"

/*! \brief Class for array expression
 * [x, y, z]
 */
class ASTArrExpr : public ASTExpr {
    std::vector<std::shared_ptr<ASTExpr>> ELEMENTS;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTArrExpr(std::vector<std::shared_ptr<ASTExpr>> ELEMENTS);
    std::vector<ASTExpr*> getElements() const;
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
