#include "stdafx.h"
#include "calc.h";
/*
���������:
֧��+,-
*,/ ,% ,^ָ��,~��������
����c++ ����ʱ�������޸Ķ���
����һ�߽���һ�߼���ķ�ʽ;
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