#include "ASTArrElemRefExpr.h"
#include "ASTVisitor.h"

void ASTArrElemRefExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getPtr()->accept(visitor);
        getIndex()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTArrElemRefExpr::print(std::ostream &out) const {
    out << *getPtr() << "[" << *getIndex() << "]";
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTArrElemRefExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(PTR);
    children.push_back(INDEX);
    return children;
}
