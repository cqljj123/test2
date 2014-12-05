//def.cpp source file
#include "def.h"
using namespace WORDCODE;

unsigned int OperatorChr(char ch_)
{
	switch(ch_)
	{
	case '+':
		return WordCode::add;
	case '-':
		return WordCode::minus;
	case '*':
		return WordCode::mult;
	case '/':
		return WordCode::div;
	case '^':
		return WordCode::spow;
	case '%':
		return WordCode::smod;
	case '>':
		return WordCode::max;
	case '<':
		return WordCode::min;
	case '=':
		return WORDCODE::assign;
	}
	return 0;
}

unsigned int SymbChr(char ch_)
{
	switch(ch_)
	{
	case ',':
		return WordCode::comma;
	case '=':
		return WordCode::equal;
	case '(':
		return WordCode::left;
	case ')':
		return WordCode::right;
	}
	return 0;
}

unsigned int SymbOperatorChr(char ch_)
{
	unsigned int flags=SymbChr(ch_);
	if( flags )
		return flags;
	return OperatorChr(ch_);
}//判断该编码是否为函数编码，在语法分析阶段所用




