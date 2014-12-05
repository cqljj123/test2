//calculate.cpp source file
#include "calculate.h"
#include "Error.h"
#include <string.h>

using PHRASEINFO::Phrase;
using MYERROR::any_error;

double calculate::eval(bool& Success,string& error)
{
	double num=0;

	if( !strlen(_str) )
	{
		Success=false;
		error="请输入表达式";
		return num;
	}
	//使用前先来个清除吧
	_lexer.OnCreteObject()->erase(_lexer.OnCreteObject()->begin(),_lexer.OnCreteObject()->end());

	try
	{
		//开始词法解析
		_lexer.InputString(_str);
		//开始语法解析
		Phrase _phrase(&_lexer);
		_phrase.Analyse();
		Success=_phrase.GetSuccess();
		if( !Success )
		{
			_phrase.GetErrorInfo(error);
			return num;
		}
		//开始计算，首先初始化两个类
		_Exp.SetWordListPtr(&_lexer);
		_Func.SetWordListPtr(&_lexer);

		num=_Exp.eval(_lexer.OnCreteObject()->begin(),
			_lexer.OnCreteObject()->end(),_Func);
	}
	catch(out_of_range err)
	{
		error=err.what();
		Success=false;
	}
	catch(any_error err)
	{
		error=err.what();
		Success=false;
	}
	catch(...)
	{
		error="出现未知的错误";
		Success=false;
	}

	return num;
}