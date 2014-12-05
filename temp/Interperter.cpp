//Interperter.cpp source file

#include "Interperter.h"
#include "mathfunction.h"
#include "Error.h"


using  INTERPERTER::ExpIpt;
using  INTERPERTER::FuncIpt;
using  INTERPERTER::AUTO;

//初始化为角度值
int ExpIpt::_sys=0; 

//表达式解释器类的定义：
//SuccessFlags参数表示成功的标志
double ExpIpt::eval(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla)
{
	double num(0); //存储结果的变量
	WordList Wlist;//后缀表达式
	//转换后缀表达式
	convert(begin,end,FuncCla,Wlist);

	_NumStck.clear();//用之前先清空
	bool und;
	double op1,op2;				//两个操作数

	for( AUTO it=Wlist.OnCreteObject()->begin(); it != Wlist.OnCreteObject()->end(); it++ )
	{
		if( isnum( *it ) )
		{
			num=atox(it->GetWordName());
			_NumStck.push(num);
		}
		else
		{
			op2=_NumStck.pop(und);
			op1=_NumStck.pop(und);
			num=count(op1,op2,it->GetWordName().at(0));
			_NumStck.push(num);
		}
	}
	num=_NumStck.pop(und);//取出结果
	return num;
}

inline double ExpIpt::atox(const string& str)
{
	return stod(str);
}

int ExpIpt::open_lev(char op1)
{
	//按数学上等级划分
	switch(op1)
	{
	case '<':
	case '>':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '^':
		return 3;
	default:
		string str="未定义运算符";
		str+=" "+op1;
		throw MYERROR::any_error(str);
	}
}//end open_lev

//比较两个运算符的等级
bool ExpIpt::isproc(char op1,char op2)
{
	if( op1=='(' || op2=='(' )
		return false;

	if( op2==')' )
		return true;

	//特殊的同级运算符是后面的等级高于前面的等级
	if( op1 == '^' && op2 =='^' )
		return false;

	if( open_lev(op1) < open_lev(op2) )
		return false;

	return true;
}


bool ExpIpt::isfunc(const Word& word)
{
	return ( word.GetClass() == WORDCLASS::WordClass::func )?true:false;
}


bool ExpIpt::isnum(const Word& word)
{
	if( word.GetClass() == WORDCLASS::WordClass::num )
		return true;
	return false;
}

bool ExpIpt::isopen(char ch)
{
	return (OperatorChr(ch))? true:false;
}


void PrintWord(Word* pw)
{
	cout<<pw->GetWordName()<<" ";
}

void ExpIpt::convert(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla,WordList& _WCList)
{
	Word symb;		 //表达式中的运算符
	Word topsymb;    //堆栈中的运算符
	my_stack<Word> _StrStack; //存储操作符的堆栈
	bool und;

	auto it=begin;
	while( it != end )
	{
		symb=*it;
		if( isnum(*it) ) //如果为常数则直接添加至后缀表达式中去
			_WCList.AddWord(*it);
		else if( isfunc( *it ) ){//如果为函数则递归交给函数分析类处理
			FuncCla.eval(it,end,*this);
			continue;
		}
		else
		{
			topsymb=_StrStack.pop(und);
			//堆栈中弹出的运算符优先级比表达式中的高时则加入后缀表达式中
			while( und && isproc(topsymb.GetWordName()[0],symb.GetWordName()[0]) )
			{
				_WCList.AddWord(topsymb);
				topsymb=_StrStack.pop(und);
			}

			if( und )
				_StrStack.push(topsymb);

			if( !und || (symb.GetWordName()[0] != ')') )
				_StrStack.push(symb);
			else
				topsymb=_StrStack.pop(und);
		}//end if
		++it;
	}//end while
	while( !_StrStack.empty() )
		_WCList.AddWord(_StrStack.pop(und));
}

double ExpIpt::count(double op1,double op2,char open) 
{
	switch(open)
	{
	case '+':
		return Add(op1,op2);
	case '-':
		return Sub(op1,op2);
	case '*':
		return Mul(op1,op2);
	case '/':
		return Div(op1,op2);
	case '^':
		return Pow(op1,op2);
	case '>':
		return Max(op1,op2);
	case '<':
		return Min(op1,op2);
	case '%':
		return Mod(op1,op2);
	default:
		string temp("未定义的的操作符号出现");
		temp+='\"';temp+=open;temp+='\"';
		throw MYERROR::any_error(temp);
		return 0;
	}
}
//end ExpIpt Class function define


/*###########****##########*/
//begin FuncIpt Class function define
double FuncIpt::eval(AUTO& begin,const AUTO& end,ExpIpt& ExpCla)
{
	double num(0); //结果值
	AUTO it=begin;
	++it;
	AUTO start=it;
	array<double,4> VResult;//存储函数参数值的数组
	int i=TowFunctionStr(begin->GetEncode());
	for( ; i>=1; i-- )
	{
		++it;start=it;
		//参数分析
		Analyse(it,it,end,i);
		num=ExpCla.eval(start,it,*this);

		VResult[i-1]=num;
	}//最后 it 将会指向 函数的结束标志 ')'
	
	num=count(*begin,VResult);
	Process(begin,it,num);
	return num;
}

void FuncIpt::Analyse(const AUTO& begin,AUTO& end,const AUTO& errEnd,int symb)
{
/*****************************************/
#define RightCode WORDCODE::WordCode::right
#define LeftCode  WORDCODE::WordCode::left
#define Comma	  WORDCODE::WordCode::comma
/*****************************************/
	//检查函数的参数正确性,只要检查','号就行
	//end=begin;
	if( symb != 1 ){//不是最后一个参数的处理
		int LastTowFunc=1;
		while( LastTowFunc )
		{
			if( TowFunctionStr(end->GetEncode()) > 1 )
				LastTowFunc+=TowFunctionStr(end->GetEncode())-1;
			else if( end->GetEncode() == Comma ) --LastTowFunc;
			++end;
		}
		--end;//end 将会指向 ',' 单词;
	}
	else//最后一个参数的处理
	{
		int Empty=0;
		while( true )
		{
			if( end == errEnd ) break;
			if( end->GetEncode() == LeftCode ) Empty++;
			else if( end->GetEncode() == RightCode )
			{
				if( !Empty ) break;
				Empty--;
			}//end if 
			++end;
		}//end while
		//循环结束后 end 将会指向 函数的结束符 ')'
	}//end if
}


double FuncIpt::count(const Word& fw,const array<double,4>& vr)
{
#define CODE	WORDCODE::WordCode
	switch(fw.GetEncode())
	{
	case CODE::abs:
		return Abs(vr[0]);
	case CODE::acos:
		return ACos(vr[0]);
	case CODE::atan:
		return ATan(vr[0]);
	case CODE::cos:
		return Cos(vr[0]);
	case CODE::cosh:
		return Cosh(vr[0]);
	case CODE::exp:
		return Exp(vr[0]);
	case CODE::fact:
		return (double)Foct(vr[0]);
	case CODE::floor:
		return (double)Floor(vr[0]);
	case CODE::lg:
		return Lg(vr[0]);
	case CODE::ln:
		return Ln(vr[0]);
	case CODE::log:
		return Log(vr[1],vr[0]);
	case CODE::mod:
		return Mod(vr[1],vr[0]);
	case CODE::pow:
		return Pow(vr[1],vr[0]);
	case CODE::sin:
		return Sin(vr[0]);
	case CODE::sinh:
		return Sinh(vr[0]);
	case CODE::sqrt:
		Sqrt(vr[0]);
	case CODE::sum:
		return Sum(vr[1],vr[0]);
	case CODE::tan:
		return Tan(vr[0]);
	case CODE::tanh:
		return Tanh(vr[0]);
	default:
		return 0;
	}
}

void FuncIpt::Process(AUTO& begin,AUTO& end,double result)
{
	list<Word> *lp=_WList->OnCreteObject();
	begin->SetMemInfo(WORDCLASS::num,WORDCODE::WordCode::constnum,to_string(result));
	++begin;
	++end;
	begin=lp->erase(begin,end);
	--begin;
}