///PhraseInfo.h head file
#ifndef _PHRASEINFO_H_
#define _PHRASEINFO_H_

#include "WordInfo.h"
#include "MapInfo.h"

using WORDINFO::WordList;
using WORDINFO::Word;
using MAPINFO::WordMap;
using MAPINFO::FunctionMap;

namespace PHRASEINFO
{
	//词法分析器
	class Lexer:public WordList
	{
	public:
		Lexer():_FuncMapClass(true){}
		void InputString(const string& str){
			if( str.size() )
				InputExpression(str);
		}
		
		//调用基类的虚函数
		virtual void AddWord(const Word& word){
			WordList::AddWord(word);
		}
		virtual void DelWrod(Word& word){
			WordList::DelWrod(word);
		}
		virtual list<Word>* OnCreteObject(){
			return WordList::OnCreteObject();
		}
	protected:
		//词法分析
		void InputExpression(const string& str);
		//单词分析
		void WordAnalyse(const string& str,Word& word);
		//使 ‘-’ 成为负号的字符，在‘-’前面
		bool MinusChr(char ch);

		//添加常数单词
		void AddConstNumWord(Word& word,string& temp,bool IsErase=true);
		//添加函数单词
		void AddFunctionWord(Word& word,string& temp,bool IsErase=true);
		//添加符号（'('\')'\','）单词
		void AddSymbWord(Word& word,string& temp,bool IsErase=true);
		//添加操作符单词
		void AddOperatorWord(Word& word,string& temp,bool IsErase=true);
	private:
		FunctionMap _FuncMapClass;
	};

	//语法分析器类
	typedef list<Word>::iterator AUTO;
	class Phrase
	{
	public:
		//接收词法分析后的单词链表
		Phrase(WordList* WL):_StkStr(10){
			_SuccessFlags=true;
			_WordList=WL;
			_WordMap=new WordMap(7);
		}
		~Phrase(){
			delete _WordMap;
		}
	public:
		void Analyse();
		bool operator ! () const{
			return _SuccessFlags;
		}
		//获取错误信息
		void GetErrorInfo(string& str){
			str=_ErrInfo;
		}
		bool GetSuccess() const{
			return _SuccessFlags;
		}
	protected:
		//检查小数点的数量是否合法
		bool point_numAndch(const string &str);
		//检查中缀表达式是否合法
		bool AnalyseWord(const AUTO& begin,const AUTO& end);
		//检查函数是否合法
		bool AnalyseFunc(AUTO& begin,const AUTO& end);
		void SetErrorInfo(const string& str,const string& word){
			_ErrInfo=str+" \"";
			_ErrInfo+=word;
			_ErrInfo+="\"";
			_SuccessFlags=false;
		}
	private:
		//压入函数参数的中缀表达式
		my_stack<pair<AUTO,AUTO> > _StkStr;
		WordList *_WordList;
		WordMap *_WordMap;
		bool _SuccessFlags;
		string _ErrInfo;
	};
}

#endif