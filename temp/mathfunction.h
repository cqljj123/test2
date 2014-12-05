//mathfunction.h head file

#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_
#include <math.h>

#define TT 3.1415926535
//ȫ�ֱ�������¼���Ǻ�����ʽʹ�ýǶȻ��ǻ����������,0����Ƕȣ�1������
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

//log�Ķ��壺http://baike.baidu.cn/view/331649.htm

//������������
void LogErr1(double num_);
void LogErr2(double num_);

//�Զ���ĺ���
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