#include "ASTArrExpr.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

ASTArrExpr::ASTArrExpr(
        std::vector<std::shared_ptr<ASTExpr>> ELEMENTS) {
    for (auto &element : ELEMENTS) {
        std::shared_ptr<ASTExpr> e = element;
        this->ELEMENTS.push_back(e);
    }
} // LCOV_EXCL_LINE

std::vector<ASTExpr *> ASTArrExpr::getElements() const {
    return rawRefs(ELEMENTS);
} // LCOV_EXCL_LINE

void ASTArrExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        for (auto e : getElements()) {
            e->accept(visitor);
        }
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTArrExpr::print(std::ostream &out) const {
    out << "[";
    bool skip = true;
    for (auto &e : getElements()) {
        if (skip) {
            skip = false;
            out << *e;
            continue;
        }
        out << "," << *e;
    }
    out << "]";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTArrExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    for (auto &element : ELEMENTS) {
        children.push_back(element);
    }
    return children;
} // LCOV_EXCL_LINE
