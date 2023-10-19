#include "ASTForRangeStmt.h"
#include "ASTVisitor.h"

void ASTForRangeStmt::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getIter()->accept(visitor);
        getRStart()->accept(visitor);
        getREnd()->accept(visitor);
        if (getStep() != nullptr) {
            getStep()->accept(visitor);
        }
        getBody()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTForRangeStmt::print(std::ostream &out) const {
    out << "for (" << *getIter() << " : " << *getRStart() << " .. " << *getREnd();
    if (getStep() != nullptr){
        out << " by " << *getStep();
    }
    out << ") " << *getBody();
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForRangeStmt::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(ITER);
    children.push_back(RSTART);
    children.push_back(REND);
    if (getStep() != nullptr) {
        children.push_back(STEP);
    }
    children.push_back(BODY);

    return children;
}
