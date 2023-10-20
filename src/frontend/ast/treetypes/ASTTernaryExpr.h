#pragma once

#include "ASTExpr.h"

/*! \brief Class for a ternary operator.
 */
class ASTTernaryExpr : public ASTExpr {
		std::shared_ptr<ASTExpr> COND, TRUE, FALSE;

public:
		std::vector<std::shared_ptr<ASTNode>> getChildren() override;
		ASTTernaryExpr(std::shared_ptr<ASTExpr> COND,
									std::shared_ptr<ASTExpr> TRUE, std::shared_ptr<ASTExpr> FALSE)
						: COND(COND), TRUE(TRUE), FALSE(FALSE) {}
		ASTExpr *getCond() const { return COND.get(); }
		ASTExpr *getTrue() const { return TRUE.get(); }
		ASTExpr *getFalse() const { return FALSE.get(); }
		void accept(ASTVisitor *visitor) override;
		llvm::Value *codegen() override;

protected:
		std::ostream &print(std::ostream &out) const override;
};