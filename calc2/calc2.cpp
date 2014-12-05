// calc2.cpp : Defines the entry point for the console application.
//
/*
桌面计算器:
支持+,-
*,/ ,% ,^指数,~对数运算
根据c++ 程序时间语言修改而来
采用一边解析一边计算的方式;
*/
#include "stdafx.h"
#include "calc.h"
double mycalc::calc(const char * calstr)
{
	curr_tok = START;
	input = new istringstream(calstr);
	table["pi"] = 3.1415926535898;
	table["e"] =  2.718281828459;
	double cr1=0;
	int j=0;
	while(input->good())
	{
		//if(curr_tok ==END) break;
		if(curr_tok == PRINT || curr_tok ==END)
		{
			curr_tok = START;
			continue;
		}
		//double &cr = table["ans"];
		cr1 = expr();
	}	
	delete input;
	return cr1;
}

double mycalc::expr(bool get)
{
	double left = term(get);
	for(;;)
	{
		switch(curr_tok)
		{
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}
double mycalc::term(bool get)
{
	double left = prim(get);
	for(;;)
	{
		switch (curr_tok)
		{

		case MUL:
			left *=prim(true);
			break;
		case DIV:
			if(double d=prim(true))
			{
				left /=d;
				break;
			}
			return error("div by 0");
		case pw1:
			{
				double d=prim(true);
				if(d>0) left = pow(left,d);
				return left;
			}
			return error("pow more zero");
		case ln1:
			{
				double d=prim(true);
				if(d>0 && left>0) return log(left)/log(d);
			}
			return error("ln more zero");
		case mod:
			if(double d=prim(true))
			{
				return fmod(left,d);
			}
			return error("div by 0");
		case SIN:
			{
			double d= prim(true);
			return sin(d);
			return error("div by 0");
			}
		default:
			return left;
		}
	}
}
double mycalc::prim(bool get)
{
	if(get) get_token();
	switch (curr_tok)
	{
	case NUMBER:
		{
			double v= number_value;
			get_token();
			return v;
		}
	case NAME:
		{
			double &v=table[string_value];
			if(get_token()==ASSIGN)
			{v=expr(true);

			}
			return v;
		}
	case PLUS:
		return prim(true);
	case MINUS:
		return -prim(true);
	case LP:
		{
			double e = expr(true);
			if(curr_tok != RP) return error("'(' not matching");
			get_token();
			return e;
			break;
		}
	default:
		return 0.0;
	}
}
mycalc::Token_value mycalc::get_token()
{
	char ch=0;
	do{

		if(! input->good())return curr_tok = END;
		*input>>ch;
		//if(!cin.get(ch))return curr_tok = END;
	}while(ch!='\n'&&isspace(ch));
	switch (ch)
	{
	case '\n':
	case ';':
		return curr_tok = PRINT;
	case 0:
		return curr_tok = END;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
	case '^':
	case '~':
	case '%':
	case '@':
		return curr_tok = Token_value(ch);
	case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
		//cin.putback(ch);
		input->putback(ch);
		//cin>>number_value;
		*input>>number_value;
		return curr_tok = NUMBER;
	default:
		if(isalpha(ch))
		{
			string_value = ch;
			/*while(cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
			cin.putback(ch);
			*/
			while(*input>>ch && isalnum(ch)) string_value.push_back(ch);
			input->putback(ch);
			return curr_tok = NAME;
		}
		error("bad tocken");
		return curr_tok = PRINT;
	}
}




