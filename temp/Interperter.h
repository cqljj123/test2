//Interperter.h head file

#ifndef _INTERPERTER_H_
#define _INTERPERTER_H_

#include "WordInfo.h"

using namespace WORDINFO;

namespace INTERPERTER
{
	//解释器类
	typedef list<Word>::iterator AUTO;
	class FuncIpt;

	//表达式解释器
	class ExpIpt
	{
	public:
		ExpIpt(WordList* WList=NULL){
			SetWordListPtr(WList);
		}
	public:
		void SetWordListPtr(WordList* WList){
			_WList=WList;
		}
	public:
		//计算函数

		/*计算转换后的表达式
		 *begin[in]：是该类处理的第一个位置
		 *end[in]:该类处理的最后一个位置
		 *FuncCla[in]：上一次递归，传递的函数表达式类的引用,以便使函数递归跳转到函数处理类处理*/
		double eval(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla);
	protected:
		//判断、检查、比较类函数
		bool isnum(const Word& word);			//判断是否为一串数字
		bool isfunc(const Word& word);		    //判断单词是否为函数

		bool isproc(char op1,char op2);			//比较两个运算符的优先级												
	public:
		bool isopen(char ch);					//判断是否为运算符

	protected:
		//转换类函数
		double    atox(const string &str);		//将字符转换为要计算的类型
		//将中缀表达式转换为后缀
		//_WCList为后缀表达式链表
		void convert(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla,WordList& _WCList);

	private:
		//操作类函数
		int open_lev(char op1);				    //运算符等级
		//计算两个操作
		double  count(double op1,double op2,char open);		 
	public:
		//析构函数作必要的清理工作
		~ExpIpt() {}
	public:
		//表示角度或者弧度的变量，0为角度值 1为弧度制
		static int _sys;
	private:
		//管理存储表达式的单词链表类
		WordList *_WList;
		my_stack<double> _NumStck;	//存储操作数的堆栈
	};

	//函数解释器
	class FuncIpt
	{
	public:
		FuncIpt(WordList* WList=NULL){
			SetWordListPtr(WList);
		}
	public:
		void SetWordListPtr(WordList* WList){
			_WList=WList;
		}
	public:
		/*函数接收表达式并分析最后返回结果
		 *begin[in,out]：是该类处理的第一个位置
		 *end[in,out]:仅仅标识最后的结束位置，真真的结束位置应该靠类的分析函数去标识
		 *ExpCla[in]：上一次递归，传递的常规表达式类的引用,以便使函数递归跳转到常规处理函数
		 */
		double eval(AUTO& begin,const AUTO& end,ExpIpt& ExpCla);
	public:
		/*Analyse
		 *函数用于检测表达式的正确性，并产生一个正确表达式序列，
		 *    且使用begin~end 标记
		 *begin[in]  : 开始检查的位置,这个位置不会被改写
		 *end[out]   : 接收分析后的结束位置,这个位置将会被改写
		 *errEnd[out]: 一个错误的结束标记如果提前到达则表达式结束位将是错误的 
		 *symb[in]   : 标识着是否是最后一个参数，1表示是最后一个参数
		 *备注： begin与end的参数传递的时候应该是一致的
		 */
		void Analyse(const AUTO& begin,AUTO& end,const AUTO& errEnd,int symb);
	protected:
		//处理计算后表达式
		void Process(AUTO& begin,AUTO& end,double result);
		//计算函数的结果
		double count(const Word& fw,const array<double,4>& vr); 
	private:
		WordList *_WList;
	};
}

#endif