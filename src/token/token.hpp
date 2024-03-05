#pragma once

#include<iostream>
#include<string>

/*
*   @brief Token类，用于表示词法分析的结果
*
*/
class Token{
private:
    int token_type;
    std::string token_value;
    int lineno;
    int colno;
public:
    /*特殊符号*/
    const static int ERROR = -1;
    const static int TOKENEOF = 0;
    /*标识符*/
    const static int ID = 1;
    /*关键字*/
    const static int KW = 2;
    /*常量类型 可以通过这个来类型转化*/
    const static int INT = 3;
    const static int REAL = 4;
    const static int CHAR = 5;
    const static int STRING = 6;
    const static int BOOL = 7;
    /*运算符*/
    const static int OPERATOR = 8;
    /*分隔符*/
    const static int SEPARATOR = 9;
    /*注释*/
    const static int ANNO = 10;


    /*
    *   @brief 构造函数 
    */
    Token();
    /*
    *   @brief 析构函数
    */
    ~Token();
    /*
    *   @brief 装载Token
    *   @param token_type token的类型
    *  @param token_value token的值
    *  @param lineno token所在行号
    * @param colno token所在列号
    * @return void
    */
    void fill(int token_type, std::string token_value, int lineno, int colno);
    /*
    *   @brief 获取token的类型
    *   @return token的类型
    */
    int get_token_type();
    /*
    *   @brief 获取token所在行号
    *   @return token所在行号
    */
    int get_lineno();
    /*
    *   @brief 获取token所在列号
    *   @return token所在列号
    */
    int get_colno();
    /*
    *   @brief 获取token的string类型值
    *   @return token的string类型值
    */
    std::string get_string();
    /*
    *   @brief 获取token的int类型值
    *   @return token的int类型值
    */
    long long get_int();
    /*
    *   @brief 获取token的double类型值
    *   @return token的double类型值
    */
    double get_real();
    /*
    *   @brief 获取token的bool类型值
    *   @return token的bool类型值
    */
    bool get_bool();
    /*
    *   @brief 获取token的char类型值
    *   @return token的char类型值
    */
    char get_char();
    /*
    *   @brief 获取token的类型
    *   @param token_type token的类型
    *  @return token的类型
    */
    std::string get_type();
    /*
    *   @brief 字符串
    *   @return 字符串
    */
    std::string to_string();
};
