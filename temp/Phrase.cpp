#include "PhraseInfo.h"

using PHRASEINFO::Phrase;
using PHRASEINFO::AUTO;
using WORDCODE::WordCode;
using WORDCLASS::WordClass;

bool Phrase::AnalyseWord(const AUTO& begin,const AUTO& end)
{
	//利用堆栈检查中缀表达式的正确性
	int n_num=-1;  //检查运算符与运算数是否匹配
	int c_num=0;  //检查括号是否匹配
	for( AUTO it=begin; it != end; it++ )
	{
		if( it->GetClass() == WORDCLASS::WordClass::func){
			if( !AnalyseFunc(it,end) ) return false;
			else
				n_num++;
		}
		else if( it->GetEncode() == WORDCODE::WordCode::right ) //右括号
			--c_num;
		else if( it->GetEncode() == WORDCODE::WordCode::left ) //左括号
			++c_num;
		else if( it->GetClass() == WORDCLASS::WordClass::num ) //常数
		{
			if( !point_numAndch(it->GetWordName()) ){ //如果常量的小数点不合法
				SetErrorInfo("常数不合法:",it->GetWordName());
				return false;
			}
			++n_num;
		}
		else n_num--; //end if
		//为防止右括号和运算符连续出现两次的情况下，需要提前检测一下
		if( n_num < -1 || c_num < 0 ){
			SetErrorInfo("表达式不正确","运算符与操作数不正确");
			return false;
		}
	}

	if( n_num!=0 || c_num != 0 ){ 
		SetErrorInfo("表达式不正确","运算符与操作数不匹配");
		return false;
	}
	return true;
}

bool Phrase::point_numAndch(const string& str)
{
	//开头出现 '.' 则常量表达式错误
	if( str[0] == '.' ) return false;
	int i=0,point=0;
	while( str[i] != '\0' )
		if( str[i++] == '.' ) ++point;

	if( point > 1 ) return false;
	return true;
}

bool Phrase::AnalyseFunc(AUTO& begin,const AUTO& end)
{
	//首先检查函数是否被定义
	if( !_WordMap->GetFuncMeans(begin->GetWordName()) ){
		SetErrorInfo("未定义的函数出现",begin->GetWordName());
		return false;
	}

	//函数后面应该紧跟着左括号 '('
	AUTO it=begin;
	if( ++it == end ){
		SetErrorInfo("函数缺少左括号",begin->GetWordName());
		return false;
	}

	if( it->GetEncode() == WordCode::left )
	{
		//函数的参数个数
		int par=TowFunctionStr(begin->GetEncode());
		++it;
		AUTO stk=it;
		//读取函数的参数压入堆栈中去
		int Empty=0; //左括号与右括号的平衡
		int LastTowFunc=0;
		while( it != end )
		{
			if( (par>1) && TowFunctionStr(it->GetEncode()) > 1  )
				LastTowFunc+=TowFunctionStr(it->GetEncode())-1;
			else if( (par>1) && (it->GetEncode() == WordCode::comma) )
			{
				if( !LastTowFunc ){
					Empty=0;
					_StkStr.push(pair<AUTO,AUTO>(stk,it));
					stk=it;++stk;--par;
				}//end if
				LastTowFunc--;
				if( stk == end ){
						SetErrorInfo("函数缺少参数列表",begin->GetWordName());
						break;
				}//end if
			}
			else if( it->GetEncode() == WordCode::left ) Empty++;
			else if( it->GetEncode() == WordCode::right )
			{
				if( !Empty ){
					_StkStr.push(pair<AUTO,AUTO>(stk,it));
					--par;
					break;
				}
				Empty--;
			}//end if 
			++it;
		}//end while
		if( par ){
			SetErrorInfo("函数参数不完整",begin->GetWordName());
			return false;
		}
		else
			begin=it;
	}
	else
	{
		SetErrorInfo("函数缺少左括号",begin->GetWordName());
		return false;
	}//end if
	return true;
}

void Phrase::Analyse()
{
	list<Word> *li=_WordList->OnCreteObject();
	if( AnalyseWord(li->begin(),li->end()) )
	{
		pair<AUTO,AUTO> obj;
		bool und;
		while( !_StkStr.empty() ){
			obj=_StkStr.pop(und);
			assert(und);
			if( !AnalyseWord(obj.first,obj.second) )
				break;
		}
	}
}