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
	//�ʷ�������
	class Lexer:public WordList
	{
	public:
		Lexer():_FuncMapClass(true){}
		void InputString(const string& str){
			if( str.size() )
				InputExpression(str);
		}
		
		//���û�����麯��
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
		//�ʷ�����
		void InputExpression(const string& str);
		//���ʷ���
		void WordAnalyse(const string& str,Word& word);
		//ʹ ��-�� ��Ϊ���ŵ��ַ����ڡ�-��ǰ��
		bool MinusChr(char ch);

		//��ӳ�������
		void AddConstNumWord(Word& word,string& temp,bool IsErase=true);
		//��Ӻ�������
		void AddFunctionWord(Word& word,string& temp,bool IsErase=true);
		//��ӷ��ţ�'('\')'\','������
		void AddSymbWord(Word& word,string& temp,bool IsErase=true);
		//��Ӳ���������
		void AddOperatorWord(Word& word,string& temp,bool IsErase=true);
	private:
		FunctionMap _FuncMapClass;
	};

	//�﷨��������
	typedef list<Word>::iterator AUTO;
	class Phrase
	{
	public:
		//���մʷ�������ĵ�������
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
		//��ȡ������Ϣ
		void GetErrorInfo(string& str){
			str=_ErrInfo;
		}
		bool GetSuccess() const{
			return _SuccessFlags;
		}
	protected:
		//���С����������Ƿ�Ϸ�
		bool point_numAndch(const string &str);
		//�����׺���ʽ�Ƿ�Ϸ�
		bool AnalyseWord(const AUTO& begin,const AUTO& end);
		//��麯���Ƿ�Ϸ�
		bool AnalyseFunc(AUTO& begin,const AUTO& end);
		void SetErrorInfo(const string& str,const string& word){
			_ErrInfo=str+" \"";
			_ErrInfo+=word;
			_ErrInfo+="\"";
			_SuccessFlags=false;
		}
	private:
		//ѹ�뺯����������׺���ʽ
		my_stack<pair<AUTO,AUTO> > _StkStr;
		WordList *_WordList;
		WordMap *_WordMap;
		bool _SuccessFlags;
		string _ErrInfo;
	};
}

#endif