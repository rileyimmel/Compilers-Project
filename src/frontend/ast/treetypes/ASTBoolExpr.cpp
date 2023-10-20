#include "ASTBoolExpr.h"
#include "ASTVisitor.h"

#include <iostream>

void ASTBoolExpr::accept(ASTVisitor * visitor) {
		visitor->visit(this);
		visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTBoolExpr::print(std::ostream &out) const {
		out << getValue();
		return out;
} // LCOV_EXCL_LINE