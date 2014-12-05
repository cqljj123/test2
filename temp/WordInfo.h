//Token.h head file

#ifndef _WORDINFO_H_
#define _WORDINFO_H_
#include "stdafx.h"

//标记类
namespace WORDINFO
{
	//单词类,记录单词名称，类别与词义
	class Word
	{
	public:
		Word(){}
		template<typename type>
		Word(int Class,int Encode,const type& Value){
			SetValueName(Value);
		}
	public:
		//返回单词类别
		int GetClass() const{
			return _class;
		}
		//返回单词编码
		int GetEncode() const{
			return _encode;
		}
		//返回单词名称
		string& GetWordName(){
			return _WordName;
		}
		string GetWordName() const{
			return _WordName;
		}
		//设置成员变量的类别、编码、与单词信息
		void SetMemInfo(int cla,int encode,const string& str){
			_class=cla;
			_encode=encode;
			_WordName=str;
		}
	private:
		string _WordName;//单词名称
		int _class;	   //单词类别
		int _encode;   //单词编码
	private:
		//给_WordName赋值,供构造函数调用
		template<typename type>
		void SetValueName(const type& value);
	};

	//单词链表类
	class WordList
	{
	public:
		//增加链表长度
		virtual void AddWord(const Word& word);
		//减去链表长度
		virtual void DelWrod(Word& word);
		//返回字符串列表对象指针
		virtual list<Word>* OnCreteObject(){
			return &_WordList;
		}
		int GetSize() const;
	protected:
		list<Word> _WordList;
	};
}
#endif