#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
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
 * @brief 关系表达式, 即relop
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
    struct Term {
        RelExprType type;
        std::unique_ptr<AddExprStmt> add_expr;
    };
    std::vector<Term> terms;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 加法类表达式，等同于文法产生式中的addop
 */
class AddExprStmt : public BaseStmt {
public:
    enum class AddExprType {
        NULL_TYPE, 
        Plus, // +
        Minus, // -
        Or, // or
    };
    struct Term {
        AddExprType type;
        std::unique_ptr<MulExprStmt> mul_expr;
    };
    std::vector<Term> terms;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 乘积类表达式，等同于文法产生式中的mulop
 */
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
    struct Term {
        MulExprType type;
        std::unique_ptr<UnaryExprStmt> unary_expr;
    };
    std::vector<Term> terms;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 一元表达式
 */
class UnaryExprStmt : public BaseStmt {
public:
    enum class UnaryExprType {
        NULL_TYPE, 
        Not, // not
        Minus, // -
    };
    std::vector<UnaryExprType> types;
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

/**
 * @brief 保存数值类型的值，如char,int,float等
 */
class NumberStmt : public BaseStmt {
public:
    bool is_real; // 是否为实数(浮点型)
    bool is_signed; // 是否为有符号数
    bool is_char; // 是否为字符
    bool is_unsigned; // 是否为无符号数
    union {
        long long int_val;
        double real_val;
        unsigned long long uint_val;
        char char_val;
    };
    std::string literal; // 字面量
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 保存字符串类型的值
 */
class StrStmt : public BaseStmt {
public:
    std::string val;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 左值，即可以出现在赋值语句的一边的表达式
 */
class LValStmt : public BaseStmt {
public:
    std::string id; 
    std::vector<std::unique_ptr<ExprStmt>> array_index; // 多维数组的下标  
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 函数调用
 */
class FuncCallStmt : public BaseStmt {
public:
    std::string id;
    std::vector<std::unique_ptr<ExprStmt>> args; // 函数的参数
    void accept(StmtVisitor &visitor) override;
};

/********************************表达式*******************************************/

/*******************************声明语句******************************************/

/**
 * @brief Pascal中的基本类型
 * 
 */
enum class BasicType {
    VOID,
    INT,
    REAL,
    CHAR,
    BOOLEAN,
};

enum class DataType {
    NULL_TYPE,
    BasicType,
    ArrayType,
};

/**
 * @brief 范围表达式
 */
class PeriodStmt : public BaseStmt {
public:
    int begin;
    int end;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 常量声明语句
 */
class ConstDeclStmt : public BaseStmt {
public:
    typedef std::pair<std::string, std::unique_ptr<ValueStmt>> KvPair;
    std::vector<KvPair> pairs;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 变量声明语句
 */

class VarDeclStmt : public BaseStmt {
public:
    std::vector<std::string> id; // 可能同时声明多个变量
    DataType data_type; // 变量的类型,基本类型或者数组类型
    BasicType basic_type; // 对应的基本类型
    int type_size; // 如果是基本类型，需要指定类型大小
    bool is_var; // 是否为引用传递（在函数头中使用）
    std::vector<std::unique_ptr<PeriodStmt>> array_range; // 各维度数组定义取值
    void accept(StmtVisitor &visitor) override;
 };

/**
 * @brief 函数（function）和过程（procedure）头部声明
 * 他们俩的区别仅为有无返回值
 * 
 */
class FuncHeadDeclStmt : public BaseStmt {
public:
    std::string func_name; // 函数名
    BasicType ret_type; //返回值的类型
    std::vector<std::unique_ptr<VarDeclStmt>> args; // 函数的参数
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 函数体声明（function/procedure），对应产生式的subprogram_body
 * 
 */
class FuncBodyDeclStmt : public BaseStmt {
public:
    std::unique_ptr<ConstDeclStmt> const_decl;          // 常量声明块
    std::vector<std::unique_ptr<VarDeclStmt>> var_decl; // 变量声明块
    std::vector<std::unique_ptr<BaseStmt>> comp_stmt;   // 复合声明块，即代码段
    void accept(StmtVisitor &visitor) override;
};

class FuncDeclStmt : public BaseStmt {
public:
    std::unique_ptr<FuncHeadDeclStmt> header; // 函数的头部
    std::unique_ptr<FuncBodyDeclStmt> body;   // 函数块
    void accept(StmtVisitor &visitor) override;
};

/*******************************声明语句******************************************/

/*******************************功能语句******************************************/

/**
 * @brief 赋值语句
 */
class AssignStmt : public BaseStmt {
public:
    bool is_lval_func; //左值是不是函数
    std::unique_ptr<LValStmt> lval; //左值
    std::unique_ptr<ExprStmt> expr; //右值/表达式
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 分支语句(If)
 * 
 */
class IfStmt : public BaseStmt {
public:
    std::unique_ptr<ExprStmt> expr; // if条件表达式
    std::vector<std::unique_ptr<BaseStmt>> true_stmt; // if语句块
    std::vector<std::unique_ptr<BaseStmt>> false_stmt; // else语句块
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 循环语句
 */
class ForStmt : public BaseStmt {
public:
    std::string id; // 循环变量,只能自增
    std::unique_ptr<ExprStmt> begin; // 循环开始
    std::unique_ptr<ExprStmt> end; // 循环结束
    std::vector<std::unique_ptr<BaseStmt>> stmt; // 循环体
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief while循环语句
*/
class WhileStmt : public BaseStmt {
public:
    std::unique_ptr<ExprStmt> expr; // while条件表达式
    std::vector<std::unique_ptr<BaseStmt>> stmt; // while语句块
    void accept(StmtVisitor &visitor) override;
};


/**
 * @brief 输入函数
 */
class ReadFuncStmt : public BaseStmt {
public:
    std::vector<std::unique_ptr<LValStmt>> lval; // 输入的左值
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 输出函数
 */
class WriteFuncStmt : public BaseStmt {
public:
    std::vector<std::unique_ptr<ExprStmt>> expr; // 输出的表达式
    void accept(StmtVisitor &visitor) override;
};


class BreakStmt : public BaseStmt {
public:
    void accept(StmtVisitor &visitor) override;
};

class ContinueStmt : public BaseStmt {
public:
    void accept(StmtVisitor &visitor) override;
};


/*******************************功能语句******************************************/

/*******************************主函数******************************************/


/**
 * @brief 主函数头部，对应文法的program_head
 * 
 */
class ProgramHeadStmt : public BaseStmt {
public:
    std::vector<std::string> id_list;
    void accept(StmtVisitor &visitor) override;
};

/**
 * @brief 主函数体，对应文法的program_body
 * 
 */
class ProgramBodyStmt : public BaseStmt {
public:
    std::unique_ptr<ConstDeclStmt> const_decl;
    std::vector<std::unique_ptr<VarDeclStmt>> var_decl;
    std::vector<std::unique_ptr<FuncDeclStmt>> func_decl;
    std::vector<std::unique_ptr<BaseStmt>> comp_stmt;
    void accept(StmtVisitor &visitor) override;
};


/**
 * @brief 主函数
 */
class ProgramStmt : public BaseStmt {
public:
    std::unique_ptr<ProgramHeadStmt> head;
    std::unique_ptr<ProgramBodyStmt> body;
    void accept(StmtVisitor &visitor) override;
};

