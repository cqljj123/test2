//calculate.h head file
#ifndef _CALCULATE_H_
#define _CALCULATE_H_
#include "Interperter.h"
#include "PhraseInfo.h"
#include "mathfunction.h"

using PHRASEINFO::Lexer;
using INTERPERTER::ExpIpt;
using INTERPERTER::FuncIpt;

class calculate
{
public:
	calculate(int ways=0) {
		_str=NULL;
		SetWsys(ways);
	}
	~calculate()
	{
		if(_str == nullptr)
		{
			delete [] _str;
		}
	}
	calculate(const calculate& obj)/*:_Exp(obj._Exp),_Func(obj._Func),_lexer(obj._lexer)*/
	{
		_str=new char[strlen(obj._str)+1];
		strcpy(_str,obj._str);
	}
	void SetWsys(int ways){
		WAYS=ways;
	}
	void InputStr(const string& str){
		_str=new char[str.size()+1];
		strcpy(_str,str.c_str());
	}
	double eval(bool& Success,string& ErrorInfo);
private:
	char* _str;
	ExpIpt _Exp;
	FuncIpt _Func;
	Lexer _lexer;
};

#endif