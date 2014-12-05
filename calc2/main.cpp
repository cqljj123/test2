#include "stdafx.h"
#include "calc.h";
/*
桌面计算器:
支持+,-
*,/ ,% ,^指数,~对数运算
根据c++ 程序时间语言修改而来
采用一边解析一边计算的方式;
*/
int _tmain(int argc, _TCHAR* argv[])
{
	mycalc calc1;
	char buf[1000];
	while(1)
	{
		std::cin.getline(buf,999,'\n');	
	//std::cout<<calc1.calc("x=22+5;y=x+1")<<"\n";
	std::cout<<"reslult: "<<calc1.calc(buf)<<"\n";
	//system("pause");
	}
	return 0;
}