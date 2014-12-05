//mathfunction.cpp source file 
#include "stdafx.h"
#include "mathfunction.h"
#include "Error.h"

int WAYS=0;//ʹ��Ĭ��ֵ

inline void LogErr1(double num_)
{
	if( num_ <= 0 )
		throw MYERROR::any_error("��������С�ڻ����0");
}

inline void LogErr2(double num_)
{
	if( num_ == 1 || num_ <= 0 )
		throw MYERROR::any_error("��������Ϊ0�Ҳ�����1");
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

double Foct(double a) //���������׳�����Χ�ĺ���Ҫ���⴦��һ��
{
	if( a > -0.000000000001 && a < 0.000000000001 )
		throw MYERROR::any_error("�ײ㲻�ܼ��㸺��");
	//��ײ㲻�ܴ���С����
	long num=(long)a;
	double flot=a - (double)num;
	if( flot > -F && flot < F )
		throw MYERROR::any_error("��ײ㲻�ܼ��㸡����");

	long sum=1;
	for( ; a > 0; a-- )
	{
		sum*=a;
		//��ֹԽ��Ĵ���
		if( sum < 0 )
			throw MYERROR::any_error("�ײ㺯��������Χ");
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
		//printf("%s\n","��ĸ����Ϊ0");
		throw MYERROR::any_error("������ĸ����Ϊ0") ;

	return (a/b);
}

double Mod(double num1,double num2)
{
	long n1=(long)num1,n2=(long)num2;
	if( ((num1-(double)n1) > -0.000000000001 && (num1-(double)n1) < 0.000000000001) 
		|| ((num2-(double)n2) > -0.000000000001 && (num2-(double)n2) < 0.000000000001) )
		MYERROR::any_error("ȡ���������Ϊ������");
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