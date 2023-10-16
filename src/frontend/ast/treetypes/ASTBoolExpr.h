#pragma once

#include "ASTExpr.h"

/*! \brief Class for a boolean
 */
class ASTBoolExpr : public ASTExpr {
		std::string VALUE;

public:
		ASTBoolExpr(std::string VALUE) : VALUE(VALUE) {}
		std::string getValue() const { return VALUE; }
		void accept(ASTVisitor *visitor) override;
		llvm::Value *codegen() override;

protected:
		std::ostream &print(std::ostream &out) const override;
};