#include "ASTForEachStmt.h"
#include "ASTVisitor.h"

void ASTForEachStmt::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getItem()->accept(visitor);
        getList()->accept(visitor);
        getBody()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTForEachStmt::print(std::ostream &out) const {
    out << "for (" << *getItem() << " : " << *getList() << ") " << *getBody();
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForEachStmt::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(ITEM);
    children.push_back(LIST);
    children.push_back(BODY);

    return children;
}
