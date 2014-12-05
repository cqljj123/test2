//LexaInfo.cpp source file
#include "MapInfo.h"

using namespace MAPINFO;
using WORDCODE::WordCode;

//FunctionMap类函数的定义
FunctionMap::FunctionMap(bool flags)
{
	if( flags )
		InitInstance();
}

int FunctionMap::GetMeans(const string& str)
{
	map<string,int>::const_iterator it=_FuncMap.find(str);
	if( it == _FuncMap.end() )
		return 0;
	return it->second;
}

string FunctionMap::GetWordName(int means)
{
	auto it=_FuncMap.begin();
	while( it != _FuncMap.end() )
	{
		if( it->second == means )
			return it->first;
		++it;
	}
	return string("NULL");
}

void FunctionMap::InitInstance()
{
	typedef pair<string,int> makeStrInt;
	_FuncMap.insert(makeStrInt("sqrt",WordCode::sqrt));
	_FuncMap.insert(makeStrInt("abs",WordCode::abs));
	_FuncMap.insert(makeStrInt("acos",WordCode::acos));
	_FuncMap.insert(makeStrInt("atan",WordCode::atan));
	_FuncMap.insert(makeStrInt("cos",WordCode::cos));
	_FuncMap.insert(makeStrInt("tan",WordCode::tan));
	_FuncMap.insert(makeStrInt("cosh",WordCode::cosh));
	_FuncMap.insert(makeStrInt("exp",WordCode::exp));
	_FuncMap.insert(makeStrInt("fact",WordCode::fact));
	_FuncMap.insert(makeStrInt("floor",WordCode::floor));
	_FuncMap.insert(makeStrInt("log",WordCode::log));
	_FuncMap.insert(makeStrInt("lg",WordCode::lg));
	_FuncMap.insert(makeStrInt("ln",WordCode::ln));
	_FuncMap.insert(makeStrInt("mod",WordCode::mod));
	_FuncMap.insert(makeStrInt("sum",WordCode::sum));
	_FuncMap.insert(makeStrInt("tanh",WordCode::tanh));
	_FuncMap.insert(makeStrInt("sinh",WordCode::sinh));
	_FuncMap.insert(makeStrInt("sin",WordCode::sin));
	_FuncMap.insert(makeStrInt("pow",WordCode::pow));
}//end InitInstance function define
/****结束类FunctionMap函数的定义****/


/*开始类OperatorMap类函数的定义*/
OperatorMap::OperatorMap(bool flags)
{
	if( flags )
		InitInstance();
}

int OperatorMap::GetMeans(const string& str)
{
	auto it=_OperatorMap.end();
	it=_OperatorMap.find(str);
	if( it == _OperatorMap.end() )
		return 0;
	return it->second;
}

string OperatorMap::GetWordName(int means)
{
	auto it=_OperatorMap.begin();
	while( it != _OperatorMap.end() )
	{
		if( it->second == means )
			return it->first;
		++it;
	}
	return string("NULL");
}

void OperatorMap::InitInstance()
{
	typedef pair<string,int> StrInt;
	_OperatorMap.insert(StrInt("+",WordCode::add));
	_OperatorMap.insert(StrInt("/",WordCode::div));
	_OperatorMap.insert(StrInt("-",WordCode::minus));
	_OperatorMap.insert(StrInt("*",WordCode::mult));
	_OperatorMap.insert(StrInt("^",WordCode::spow));
	_OperatorMap.insert(StrInt("%",WordCode::smod));
	_OperatorMap.insert(StrInt(">",WordCode::max));
	_OperatorMap.insert(StrInt("<",WordCode::min));
}
/****结束OperatoMap类函数的定义****/


//开始类SymbMap函数的定义
SymbMap::SymbMap(bool flags)
{
	if( flags )
		InitInstance();
}

int SymbMap::GetMeans(const string& str)
{
	auto it=_SympMap.end();
	it=_SympMap.find(str);
	if( it == _SympMap.end() )
		return 0;
	return it->second;
}

string SymbMap::GetWordName(int means)
{
	auto it=_SympMap.begin();
	while( it != _SympMap.end() )
	{
		if( it->second == means )
			it->first;
		++it;
	}
	return string("NULL");
}

void SymbMap::InitInstance()
{
	typedef pair<string,int> StrInt;
	_SympMap.insert(StrInt("(",WordCode::left));
	_SympMap.insert(StrInt(")",WordCode::right));
	_SympMap.insert(StrInt(",",WordCode::comma));
	_SympMap.insert(StrInt("=",WordCode::equal));
}//end InitInstance
/****结束类SymbMap类函数的定义****/


/*开始WordMap类函数的定义*/
WordMap::WordMap(int flags )
{
	if( flags & 1<<2 )
		FunctionMap::InitInstance();
	if( flags & 1<<1 )
		OperatorMap::InitInstance();
	if( flags & 1 )
		SymbMap::InitInstance();
}

int WordMap::GetMeans(const string& word)
{
	int flags=FunctionMap::GetMeans(word);
	if( flags )
		return flags;
	flags=OperatorMap::GetMeans(word);
	if( flags )
		return flags;
	return SymbMap::GetMeans(word);
}

string WordMap::GetWordName(int means)
{
	string temp;
	temp=FunctionMap::GetWordName(means);
	if( temp != "NULL" )
		return temp;

	temp=OperatorMap::GetWordName(means);
	if( temp != "NULL" )
		return temp;
	
	temp=SymbMap::GetWordName(means);

	return temp;
}

WordMap* WordMap::Create(int style)
{
	WordMap *Wmap;
	switch (style)
	{
	case 1:
		Wmap=dynamic_cast<WordMap*>(new FunctionMap(true));
		break;
	case 2:
		Wmap=dynamic_cast<WordMap*>(new OperatorMap(true));
		break;
	case 3:
		Wmap=dynamic_cast<WordMap*>(new SymbMap(true));
		break;
	default:
		break;
	}
	
	return Wmap;
}

void WordMap::InitInstance()
{
	FunctionMap::InitInstance();
	OperatorMap::InitInstance();
	SymbMap::InitInstance();
}
/****结束类WordMap函数的定义****/



