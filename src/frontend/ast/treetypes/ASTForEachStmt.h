#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for range based for loop.
 *  for (E1 : E2) S
 */

class ASTForEachStmt : public ASTStmt {
    std::shared_ptr<ASTExpr> ITEM, LIST;
    std::shared_ptr<ASTStmt> BODY;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTForEachStmt(std::shared_ptr<ASTExpr> ITEM, std::shared_ptr<ASTExpr> LIST,
                   std::shared_ptr<ASTStmt> BODY)
            : ITEM(ITEM), LIST(LIST), BODY(BODY) {}
    ASTExpr *getItem() const { return ITEM.get(); }
    ASTExpr *getList() const { return LIST.get(); }
    ASTStmt *getBody() const { return BODY.get(); }

    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
