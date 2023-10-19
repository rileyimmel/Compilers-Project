#include "ASTArrOfExpr.h"
#include "ASTVisitor.h"


void ASTArrOfExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getLeft()->accept(visitor);
        getRight()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTArrOfExpr::print(std::ostream &out) const {
    out << "[" << *getLeft() << " of " << *getRight() << "]";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTArrOfExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(LEFT);
    children.push_back(RIGHT);
    return children;
}
