#include "ASTUnaryExpr.h"
#include "ASTVisitor.h"

void ASTUnaryExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getRight()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTUnaryExpr::print(std::ostream &out) const {
    if (this->getOp() != "not") {
        out << getOp() << *getRight();
    } else {
        out << getOp() << " " << *getRight();
    }
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTUnaryExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(RIGHT);
    return children;
} // LCOV_EXCL_LINE
