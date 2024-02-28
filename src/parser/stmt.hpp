

#include <memory>
#include <string>
#include <vector>
class StmtVisitor;

/**
 * @brief stmt的基类, stmt即为AST的节点
 */
class BaseStmt {
public:
    /**
     * @brief 用于接受visitor的访问，继承visitor类即可实现对stmt的访问
     * @param visitor 
     */
    virtual void accept(StmtVisitor &visitor) = 0;
    BaseStmt() = default;
    virtual ~BaseStmt() = default;
};

/********************************表达式*******************************************/
// 在Pascal中，运算符被分为五个优先等级，从高到低分别是
// ~, not
// *, /, div, mod, and, &
// |, !, +, -, or
// =, <>, <, <=, >, >=, in
// or else, and then

class FuncCallStmt; // 函数调用
class LValStmt; // 左值
class StrStmt; // 字符串
class NumberStmt; // 数字
class ValueStmt; // 值的stmt
class PrimaryExprStmt; // 优先级最高的表达式，即括号内的表达式
class UnaryExprStmt; // 一元表达式
class MulExprStmt; // 乘法以及与乘法同级别的运算
class AddExprStmt; // 加法以及与加法同级别的运算
class RelExprStmt; // 关系运算

/**
 * @brief 表示一个表达式
 */
class ExprStmt : public BaseStmt {
public:
    std::unique_ptr<RelExprStmt> rel_expr;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 关系表达式
 */
class RelExprStmt : public BaseStmt {
public:
    enum class RelExprType {
        NULL_TYPE,
        Equal, // =
        NotEqual, // <>
        Less, // <
        LessEqual, // <=
        Greater, // >
        GreaterEqual, // >=
        In, // in
    };
    RelExprType type;
    std::unique_ptr<AddExprStmt> add_expr;
    std::unique_ptr<RelExprStmt> rel_expr;
    void accept(StmtVisitor &visitor) override;
};

class AddExprStmt : public BaseStmt {
public:
    enum class AddExprType {
        NULL_TYPE, 
        Plus, // +
        Minus, // -
        Or, // or
    };
    AddExprType type;
    std::unique_ptr<MulExprStmt> mul_expr;
    std::unique_ptr<AddExprStmt> add_expr;
    void accept(StmtVisitor &visitor) override;
};


class MulExprStmt : public BaseStmt {
public:
    enum class MulExprType {
        NULL_TYPE,
        Mul, // *
        Div, // /
        Mod, // mod
        And, // and
        AndThen, // and then
    }; 
    MulExprType type;
    std::unique_ptr<UnaryExprStmt> unary_expr;
    std::unique_ptr<MulExprStmt> mul_expr;
    void accept(StmtVisitor &visitor) override;
};

class UnaryExprStmt : public BaseStmt {
public:
    enum class UnaryExprType {
        NULL_TYPE, 
        Not, // not
    };
    UnaryExprType type;
    std::unique_ptr<PrimaryExprStmt> primary_expr;
    void accept(StmtVisitor &visitor) override;
};

class PrimaryExprStmt : public BaseStmt {
public:
    enum class PrimaryExprType {
        NULL_TYPE,
        Value, // 值
        Parentheses, // 括号内的表达式
    };
    PrimaryExprType type;
    std::unique_ptr<ValueStmt> value;
    std::unique_ptr<ExprStmt> expr;
    void accept(StmtVisitor &visitor) override;
};

class ValueStmt : public BaseStmt {
public:
    enum class ValueType {
        NULL_TYPE,
        Number, // 立即数
        Str, // 字符串
        LVal, // 左值
        FuncCall, // 函数调用
    };
    ValueType type;
    std::unique_ptr<NumberStmt> number;
    std::unique_ptr<StrStmt> str;
    std::unique_ptr<LValStmt> lval;
    std::unique_ptr<FuncCallStmt> func_call;
    void accept(StmtVisitor &visitor) override;
};

class NumberStmt : public BaseStmt {
public:
    bool is_real;
    bool is_signed;
    union {
        long long int_val;
        double real_val;
        unsigned long long uint_val;
    };
    void accept(StmtVisitor &visitor) override;
};

class StrStmt : public BaseStmt {
public:
    std::string val;
    void accept(StmtVisitor &visitor) override;
};

class LValStmt : public BaseStmt {
public:
    std::string id;
    std::vector<std::unique_ptr<ExprStmt>> array_index; // 多维数组的下标  
    void accept(StmtVisitor &visitor) override;
};

class FuncCallStmt : public BaseStmt {
public:
    std::string id;
    std::vector<std::unique_ptr<ExprStmt>> args; // 函数的参数
    void accept(StmtVisitor &visitor) override;
};

/********************************表达式*******************************************/