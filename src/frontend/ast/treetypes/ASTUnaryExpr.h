#pragma once

#include "ASTExpr.h"

/*! \brief Class for unary operators
 * */
class ASTUnaryExpr : public ASTExpr {
    std::string OP;
    std::shared_ptr<ASTExpr> RIGHT;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTUnaryExpr(const std::string &OP, std::shared_ptr<ASTExpr> RIGHT) : OP(OP), RIGHT(RIGHT) {}
    std::string getOp() const { return OP; }
    ASTExpr *getRight() const { return RIGHT.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};