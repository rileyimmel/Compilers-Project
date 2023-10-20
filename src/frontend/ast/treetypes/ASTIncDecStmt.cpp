#include "ASTIncDecStmt.h"
#include "ASTVisitor.h"

void ASTIncDecStmt::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getLeft()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTIncDecStmt::print(std::ostream &out) const {
    out << *getLeft() << getOp() << ";";
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTIncDecStmt::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(LEFT);
    return children;
}
