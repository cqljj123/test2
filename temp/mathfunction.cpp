//mathfunction.cpp source file 
#include "stdafx.h"
#include "mathfunction.h"
#include "Error.h"

int WAYS=0;//使用默认值

inline void LogErr1(double num_)
{
	if( num_ <= 0 )
		throw MYERROR::any_error("真数不能小于或等于0");
}

inline void LogErr2(double num_)
{
	if( num_ == 1 || num_ <= 0 )
		throw MYERROR::any_error("基数不能为0且不等于1");
}

double Ln(double a)
{
	LogErr1(a);
	return log(a);
}

double Lg(double a)
{
	LogErr1(a);
	return log10(a);
}

double Log(double base,double x)
{
	LogErr1(x);
	LogErr2(base);
	return log(x)/log(base);
}

double Sum(double a,double b)
{
	if( b == 0 ) return 0.000000;
	return (a+b)*(b-a+1)/2;
}

double Foct(double a) //像这种容易超出范围的函数要特殊处理一下
{
	if( a > -0.000000000001 && a < 0.000000000001 )
		throw MYERROR::any_error("阶层不能计算负数");
	//求阶层不能存在小数点
	long num=(long)a;
	double flot=a - (double)num;
	if( flot > -F && flot < F )
		throw MYERROR::any_error("求阶层不能计算浮点数");

	long sum=1;
	for( ; a > 0; a-- )
	{
		sum*=a;
		//防止越界的处理
		if( sum < 0 )
			throw MYERROR::any_error("阶层函数超出范围");
	}
	return (double)sum;
}

double Add(double num1,double num2)
{
	return (num1+num2);
}

double Sub(double num1,double num2)
{
	return (num1-num2);
}

double Mul(double a,double b)
{
	return (a*b);
}

double Div(long double a,long double b)
{
	if( (b > -F) && ( b < F) )
		//printf("%s\n","分母不能为0");
		throw MYERROR::any_error("除法分母不能为0") ;

	return (a/b);
}

double Mod(double num1,double num2)
{
	long n1=(long)num1,n2=(long)num2;
	if( ((num1-(double)n1) > -0.000000000001 && (num1-(double)n1) < 0.000000000001) 
		|| ((num2-(double)n2) > -0.000000000001 && (num2-(double)n2) < 0.000000000001) )
		MYERROR::any_error("取余操作不能为浮点数");
	return (double)(n1%n2);
}

double Max(double num1,double num2)
{
	if( num1 <= num2 )
		return 0.0;
	return 1.0;
}

double Min(double num1,double num2)
{
	if( num1 >= num2 )
		return 0.0;
	return 1.0;
}