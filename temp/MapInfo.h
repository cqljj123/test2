//lexaInfo.h head file
#ifndef _MAPINFO_H_
#define _MAPINFO_H_

#include "stdafx.h"

//单词映射表类,将单词与词义相关联
namespace MAPINFO
{
	/* 详细的成员函数用法与解释见三个基类的派生类 */

	//函数映射，将函数的名称与词义相关联
	class FunctionMap
	{
	public:
		//构造函数并且给予默认的一个参数指出是否需要将成员初始化
		FunctionMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	protected:
		map<string,int> _FuncMap;
	};

	//操作符映射表类，将操作符与词义想关联
	class OperatorMap
	{
	public:
		OperatorMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	private:
		map<string,int> _OperatorMap;
	};

	//符号映射表类,将符号与词义相关联
	class SymbMap
	{
	public:
		//构造函数并且给予默认的一个参数指出是否需要将成员初始化
		SymbMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	private:
		map<string,int> _SympMap;
	};

	//三种映射表的派生类，用于管理映射表
	class WordMap:public FunctionMap,public OperatorMap,public SymbMap
	{
	public:
		//style指出创建哪种类型的映射表对象（总共就是申明的3种基类对象,类的顺序按照继承的顺序）
		static WordMap* Create(int style);
		/*
		**  构造函数并且给予默认的一个参数指出是否需要将成员初始化
		**	使用000表示要初始化的位，第一个位代表第一个类
		**	依次类推，比如 100表示初始化FuctionMap,110表示初始化FunctionMap和OperatorMap
		**  111表示全部初始化
		**	类的顺序按照继承的顺序
		*/
		WordMap(int flags=0);
		/*接收一个string类型检查该单词是否定义了，如果定义则返回相应的编码，
		 *否则将返回-1值*/
		virtual int GetMeans(const string& word);
		/*接收一个int类型检查该编码是否有对应的单词，如果有对应的单词则返回相应的函数字符串
		 *否则将返回""值*/
		virtual string GetWordName(int means);
		//返回操作符单词编码,未定义则返回0值
		int GetOperatorMeans(const string& word){
			return OperatorMap::GetMeans(word);
		}
		//返回符号单词的编码,未定义则返回0值
		int GetSymbMeans(const string& word){
			return SymbMap::GetMeans(word);
		}
		//返回函数单词的编码,未定义则返回0值
		int GetFuncMeans(const string& word){
			return FunctionMap::GetMeans(word);
		}
	protected:
		//保护成员函数初始化成员，将成员对应的函数与编码想关联，供构造函数调用
		virtual void InitInstance();
	};
}

#endif