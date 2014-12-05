//mathfunction.h head file

#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_
#include <math.h>

#define TT 3.1415926535
//全局变量，记录三角函数公式使用角度还是弧度来计算的,0代表角度，1代表弧度
extern int WAYS;

inline double SINS(double num)
{
	if( !WAYS )
		return ((num*TT)/180.000000000000);
	else
		return num;
}

#define Sin(NUM) sin(SINS(NUM))
#define Cos(NUM) cos(SINS(NUM))
#define Tan(NUM) tan(SINS(NUM))
#define ASin asin
#define ACos acos
#define ATan atan
#define Sinh sinh
#define Cosh cosh 
#define Tanh tanh
#define Exp exp
#define Floor floor
#define Sqrt(x) sqrt(x)

#define Pow  pow
#define Abs  abs

#define F  0.000000000001
#define TT 3.1415926535

//log的定义：http://baike.baidu.cn/view/331649.htm

//两个错误处理工具
void LogErr1(double num_);
void LogErr2(double num_);

//自定义的函数
double Ln(double a);
double Lg(double a);
double Log(double base,double x);
double Sum(double a,double b);
double Foct(double a);
double Add(double num1,double num2);
double Sub(double num1,double num2);
double Mul(double a,double b);
double Div(long double a,long double b);
double Mod(double num1,double num2);
double Max(double,double);
double Min(double,double);

#endif