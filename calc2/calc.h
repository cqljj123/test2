#ifndef __CALC_H_
#define __CALC_H_
/*
���������:
֧��+,-
*,/ ,% ,^ָ��,~��������
����c++ ����ʱ�������޸Ķ���
����һ�߽���һ�߼���ķ�ʽ;
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
	double calc(const char * calstr);/*����ӿ�*/
	double expr(bool get = true);/*�Ӻͼ���*/
	double term(bool);/*�˷��ͳ���*/
	double prim(bool);/*���������*/
	double number_value;/*����*/
	std::string string_value;/*����*/
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