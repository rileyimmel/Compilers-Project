#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for range based for loop.
 *  for (E1 : E2 .. E3 by E4) S
 */

class ASTForRangeStmt : public ASTStmt {
    std::shared_ptr<ASTExpr> ITER, RSTART, REND, STEP;
    std::shared_ptr<ASTStmt> BODY;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTForRangeStmt(std::shared_ptr<ASTExpr> ITER, std::shared_ptr<ASTExpr> RSTART, std::shared_ptr<ASTExpr> REND,
                    std::shared_ptr<ASTExpr> STEP, std::shared_ptr<ASTStmt> BODY)
            : ITER(ITER), RSTART(RSTART), REND(REND), STEP(STEP), BODY(BODY) {}
    ASTExpr *getIter() const { return ITER.get(); }
    ASTExpr *getRStart() const { return RSTART.get(); }
    ASTExpr *getREnd() const { return REND.get(); }

    /*! \fn step
     * \return step if it is set, 1 by default.
     */

    ASTExpr *getStep() const { return STEP.get(); }

    ASTStmt *getBody() const { return BODY.get(); }

    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
