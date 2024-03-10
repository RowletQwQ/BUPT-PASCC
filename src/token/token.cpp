#include "token.hpp"
#include <string>
/*
*   @brief Token类，用于表示词法分析的结果
*/
Token::Token(){};
/*
    *   @brief 装载Token
    *   @param token_type token的类型
    *   @param token_value token的值
    *   @param lineno token所在行号
    *   @param colno token所在列号
    */
    void Token::fill(int token_type, std::string token_value, int lineno, int colno){
        this->token_type = token_type;
        this->token_value = token_value;
        this->lineno = lineno;
        this->colno = colno;
    };
    /*
    *   @brief 析构函数
    */
    Token::~Token(){};
    /*
    *   @brief 获取token的类型
    *   @return token的类型
    */
    int Token:: get_token_type(){
        return this->token_type;
    };
    /*
    *   @brief 获取token所在行号
    *   @return token所在行号
    */
    int Token::get_lineno(){
        return this->lineno;
    };
    /*
    *   @brief 获取token所在列号
    *   @return token所在列号
    */
    int Token::get_colno(){
        return this->colno;
    };
    /*
    *   @brief 获取token的string类型值
    *   @return token的string类型值
    */
    std::string Token::get_string(){
        return this->token_value;
    };
    /*
    *   @brief 获取token的int类型值
    *   @return token的int类型值
    */
    long long Token::get_int(){
        return std::stoll(this->token_value);
    };
    /*
    *   @brief 获取token的double类型值
    *   @return token的double类型值
    */
    double Token::get_real(){
        return std::stod(this->token_value);
    };
    /*
    *   @brief 获取token的bool类型值
    *   @return token的bool类型值
    */
    bool Token::get_bool(){
        return this->token_value == "true";
    };
    /*
    *   @brief 获取token的char类型值
    *   @return token的char类型值
    */
    char Token::get_char(){
        return this->token_value[1];
    };

    /*
    *   @brief 获取token的类型
    *   @param token_type token的类型
    *  @return token的类型
    */
    std::string Token::get_type(){
    switch (token_type){
        case ERROR:
            return "ERROR";
            break;
        case TOKENEOF:
            return "TOKENEOF";
            break;
        case ID:
            return "ID";
            break;
        case KW:
            return "KW";
            break;
        case INT:
            return "INT";
            break;
        case REAL:
            return "REAL";
            break;
        case CHAR:
            return "CHAR";
            break;
        case STRING:
            return "STRING";
            break;
        case BOOL:
            return "BOOL";
            break;
        case OPERATOR:
            return "OPERATOR";
            break;
        case SEPARATOR:
            return "SEPARATOR";
            break;
        case ANNO:
            return "ANNO";
        default:
            return "ERROR";
            break;
    }
};
    /*
    *   @brief 字符串
    *   @return 字符串
    */
    std::string Token::to_string(){
        switch (token_type)
        {
        case BOOL:
            return "[Token] " + get_type() + " " + (get_bool() ? "true" : "false") + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case CHAR:
            return "[Token] " + get_type() + " " + get_char() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case STRING:
            // 假设字符串总是由两端的引号包围
            if (this->token_value.length() >= 2) {
                // 使用substr去除两端的引号，开始于第1个字符并结束于倒数第2个字符
                std::string unquoted_string = this->token_value.substr(1, this->token_value.length() - 2);
                return "[Token] " + get_type() + " " + unquoted_string + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]";
            } else {
                // 如果字符串长度不足以包含两个引号，则直接返回原始值
                return "[Token] " + get_type() + " " + this->token_value + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]";
            }
        case INT:
            return "[Token] " + get_type() + " " + std::to_string(get_int()) + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case REAL:
            return "[Token] " + get_type() + " " + std::to_string(get_real()) + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case ID:
            return "[Token] " + get_type() + " " + get_string() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case KW:
            return "[Token] " + get_type() + " " + get_string() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case OPERATOR:
            return "[Token] " + get_type() + " " + get_string() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case SEPARATOR:
            return "[Token] " + get_type() + " " + get_string() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case TOKENEOF:
            return "[Token] " + get_type() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case ERROR:
            return "[Token] " + get_type() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
            break;
        case ANNO:
            return "[Token] " + get_type() + " " + get_string() + " " + "[" + std::to_string(lineno) + "," + std::to_string(colno) + "]" ;
        default:
            return "[Token] DEFAULT TOKENTYPE line : >>> "+ std::to_string(lineno) + " " + "col : >>> " +std::to_string(colno);
            break;
        }
    };