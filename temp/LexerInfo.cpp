///PhraseInfo.cpp source file
#include "PhraseInfo.h"
#include "Error.h"

using namespace MYERROR;
using namespace WORDCLASS;
using namespace WORDCODE;

//类Lexer函数的定义
using namespace PHRASEINFO;

void Lexer::InputExpression(const string& str)
{
	string temp;
	auto it=str.begin();

	//记录上一次读取的是常量字符，或者上一次读取的是函数字符
	bool IsNum=false,IsFunc=false;
	/*开头的'-'解析为负号,这里使用 at 函数的目的是
	*如果表达式只有一个 - 号则at函数将会抛出异常。*/
	if( str.at(0) == '-' && NUMCHR( str.at(1) ) ){
		temp+=*it;
		++it;
		IsNum=true;
	}

	Word word;
	char OldOperator=' ';
	for( ; it != str.end(); it++ )
	{
		if( *it == ' ' ) continue; //空格跳过
		if( LUCHR(*it) ){//组成函数的字符
			if( IsNum )
			{//上一次读取完常量字符串后，将单词加入链表中
				AddConstNumWord(word,temp);//有问题需改进
				IsNum=false;
				//temp.erase();
			}
			temp+=*it;
			IsFunc=true;
		}
		else if( PNUMCHR(*it) )
		{//组成常数的字符
			if( IsFunc ){//上一次读取完函数字符串后，将单词加入链表中去
				AddFunctionWord(word,temp);
				IsFunc=false;
				//temp.erase();
			}
			temp+=*it;
			IsNum=true;
		}
		else //特殊符号和操作符
		{
			if( IsFunc ) //上一次读取完函数后
				AddFunctionWord(word,temp,false);
			else if( IsNum ) //上一次读取完常数后
				AddConstNumWord(word,temp,false);
			temp.erase();
			IsNum=IsFunc=false;

			if( SymbChr(*it) ) //符号'(' ')' ','
			{
				temp=*it;
				AddSymbWord(word,temp);
			}
			else//其他情况下均为操作符
			{
				temp=*it;
				if( *it == '-' ){
					if( MinusChr(OldOperator) ){//操作符被解析成负号的情况下
						IsNum=true;
						continue;
					}// end if
				}//end if
				AddOperatorWord(word,temp);
			}//end if
		}//end if
		OldOperator=*it;
	}//end for
	if( temp.size() )
	{
		if( IsNum )
			AddConstNumWord(word,temp);
		else
			AddFunctionWord(word,temp);
	}
}

inline void Lexer::AddConstNumWord(Word& word,string& temp,bool IsErase)
{
	word.SetMemInfo(WordClass::num,WordCode::constnum,temp);
	AddWord(word);
	if( IsErase )
		temp.erase();
}

inline void Lexer::AddFunctionWord(Word& word,string& temp,bool IsErase)
{
	WordAnalyse(temp,word);
	if( IsErase )
		temp.erase();
}

inline void Lexer::AddSymbWord(Word& word,string& temp,bool IsErase)
{
	if( temp[0] == '(' )
		word.SetMemInfo(WordClass::symb,WordCode::left,temp);
	else if( temp[0] == ')' )
		word.SetMemInfo(WordClass::symb,WordCode::right,temp);
	else
		word.SetMemInfo(WordClass::symb,WordCode::comma,temp);
	if( IsErase )
		temp.erase();
	AddWord(word);
}

inline void Lexer::AddOperatorWord(Word& word,string& temp,bool IsErase)
{
	int code=OperatorChr(temp[0]);
	word.SetMemInfo(WordClass::opera,code,temp);
	AddWord(word);
	if( IsErase )
		temp.erase();
}

bool Lexer::MinusChr(char ch)
{
	//在 ‘-' 前面出现以下符号时将会解析为负号
	switch(ch)
	{
	case '-':
	case '>':
	case '<':
	case '+':
	case '(':
	case ',':
		return true;
	default:
		break;
	}
	return false;
}

inline void Lexer::WordAnalyse(const string& str,Word& word)
{
	int code=this->_FuncMapClass.GetMeans(str);
	word.SetMemInfo(WordClass::func,code,str);
	AddWord(word);
}
