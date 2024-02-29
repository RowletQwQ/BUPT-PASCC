#include "ast/stmt.hpp"
#include "ast/visitor.hpp"

void ExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void RelExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void AddExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void MulExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void UnaryExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void PrimaryExprStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void ValueStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void NumberStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void StrStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void LValStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void FuncCallStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void PeriodStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void ConstDeclStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void VarDeclStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void FuncHeadDeclStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void FuncBodyDeclStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void FuncDeclStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void AssignStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void IfStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void ForStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void ReadFuncStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}

void WriteFuncStmt::accept(StmtVisitor &visitor)
{
    visitor.visit(*this);
}