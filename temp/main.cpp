#include "calculate.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

void parse(string instr)
{
	char * del = ";";
	const char *p;
	char *st = new char[instr.length()+1];
	strcpy(st,instr.c_str());
	p=strtok(st,del);
	vector<string> vec;
	while(p)
	{
		vec.push_back(p);
		//printf("%s\n",p);
		p=strtok(NULL,del);
	}
	for(int i = 1 ;i<vec.size();++i)
	{
		//vec[i].replace(
	}
	delete [] st;
}
int main(int argc,char** argv)
{
	string str;
	calculate cal;
	bool flags;
	string err;
	double num;
	while( 1 )
	{
		cout<<"请输入表达式==>";
		getline(cin,str,'\n');
		//parse(str);
		cal.InputStr(str.c_str());
		
		num=cal.eval(flags,err);
		if( !flags )
			cout<<str<<"="<<err<<endl;
		else
			cout<<str<<"="<<num<<endl;
	}
	system("pause");
	return 0;
}