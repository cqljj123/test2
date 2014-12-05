//单词编码与语义
#ifndef _DEF_H_
#define _DEF_H_

namespace WORDCODE
{
	//单词编码
	typedef enum tagCode{
		constnum=1, //常数
		left, // '(' 左括号
		right,// ')' 右括号
		comma, // ',' 逗号
		assign,
		/*****操作符分界线*****/
		equal, // '=' //预留符
		add,  // '+'
		minus,// '-'
		mult,// '*'
		div, // '/'
		spow,//'^'
		max,//  ">"
		min,//  "<"
		smod,//  "%"
		/*****函数分界线*****/
		sqrt,//  "求平方根"
		sin, //  "正弦"
		cos, //  "余弦"
		tan, //  "正切"
		acos,//	 "反余弦"
		atan,//  "反正切"
		sinh,//  "双曲正弦"
		cosh,//  "双曲余弦"
		tanh,//  "双曲正切"
		exp, //  "求e的幂"
		lg,	 //  "求以10为底的对数"
		ln,	 //  "求自然对数"
		abs,//   "求绝对值"
		fact,//	 "求阶乘"
		floor,// "求不大于某数的最大整数，例如floor(6.1)=6"
		/*****二元函数分割线*****/
		sum,//	 "求sum(1,3)=1=2+3的和"
		log,//   "求log(a,b)的对数"
		pow,//   "求a的b次方"
		mod//  "取余操作"
	}WordCode;
}


namespace WORDCLASS
{
	//单词类别
	enum WordClass
	{
		def=1,	//自定义的变量
		func,	//函数
		num,	//常数
		symb,   //符号 （ ） ，
		opera,  //操作运算符 + - * / ...
	};
}

#define NUMCHR(ch)  ((ch)>='0' && (ch)<='9')
#define PNUMCHR(ch) (((ch)>='0' && (ch)<='9') || ch == '.' )
#define NUMSTR(ch)	( ((ch)>='0' && (ch)<='9') || (ch)>='a' && \
	(ch)<='z' || (ch)>='A' && (ch) <='Z' )

#define LOWCHR(ch) ((ch)>='a' && (ch)<='z')
#define UPPCHR(ch) ((ch)>='A' && (ch)<='Z')
#define LUCHR(ch) ( ((ch)>='a' && (ch)<='z') || ((ch)>='A' && (ch)<='Z') )

unsigned int OperatorChr(char ch_);
unsigned int SymbChr(char ch_);
unsigned int SymbOperatorChr(char ch_); 
inline unsigned int FunctionStr(int code_)
{
	if( code_ >= WORDCODE::WordCode::sqrt  && code_ <= WORDCODE::WordCode::floor )
		return true;
	return false;
}
inline unsigned int TowFunctionStr(int code_)
{
	if( code_ >= WORDCODE::WordCode::sum && code_ <= WORDCODE::WordCode::mod )
		return 2;
	return 1;
}

#endif
