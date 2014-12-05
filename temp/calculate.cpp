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
		error="��������ʽ";
		return num;
	}
	//ʹ��ǰ�����������
	_lexer.OnCreteObject()->erase(_lexer.OnCreteObject()->begin(),_lexer.OnCreteObject()->end());

	try
	{
		//��ʼ�ʷ�����
		_lexer.InputString(_str);
		//��ʼ�﷨����
		Phrase _phrase(&_lexer);
		_phrase.Analyse();
		Success=_phrase.GetSuccess();
		if( !Success )
		{
			_phrase.GetErrorInfo(error);
			return num;
		}
		//��ʼ���㣬���ȳ�ʼ��������
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
		error="����δ֪�Ĵ���";
		Success=false;
	}

	return num;
}