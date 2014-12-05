#ifndef __CALC_H_
#define __CALC_H_
/*
桌面计算器:
支持+,-
*,/ ,% ,^指数,~对数运算
根据c++ 程序时间语言修改而来
采用一边解析一边计算的方式;
*/
#include <iostream>
#include <map>
#include <sstream>
#include <cmath>
#include <memory>
using std::cout;
using std::cerr;
using std::string;
using std::map;
using std::istream;
using std::istringstream;
struct mycalc{
	int no_of_errors;
	double inline error(const string &s)
	{
		no_of_errors++;
		cerr<<"error:"<<s<<'\n';
		return 0.0;
	}
	double calc(const char * calstr);/*对外接口*/
	double expr(bool get = true);/*加和减法*/
	double term(bool);/*乘法和除法*/
	double prim(bool);/*处理初等项*/
	double number_value;/*数字*/
	std::string string_value;/*变量*/
	std::map<std::string,double> table;
	enum Token_value{
		START,NAME,NUMBER,END,
		PLUS = '+' , MINUS = '-',MUL='*',DIV='/',
		PRINT=';',ASSIGN = '=',LP='(',RP=')',pw1='^',ln1='~',mod='%',SIN='@'
	};
	Token_value curr_tok;
	Token_value get_token();
	istream * input;
	//shared_ptr<istream> input;
	
};

#endif