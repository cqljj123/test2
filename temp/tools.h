//tools.h head file
#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ios;


template<typename Iterator,typename OS>
void Print(Iterator it,Iterator end,OS& out,char limit=' ')
{
	while( it != end )
	{
		out<<*it<<limit;
		++it;
	}
}

//将信息输出到文本文件中
template<typename type>
void PrintFile(const char* filename,const type& Info,char limit=' ')
{
	ofstream ofile(filename,ios::in|ios::out);
	ofile.seekp(0,ios::end);
	ofile<<Info;
	if( limit != '0' )
		ofile<<limit;
	ofile.close();
}

template<typename Iterator>
void PrintItFile(const char* filename,Iterator begin,Iterator end,char limit=' ')
{
	while( begin != end )
	{
		PrintFile(filename,*begin,limit);
		++begin;
	}
}

template<typename Iterator,typename obj>
void PrintCout(Iterator begin,Iterator end,void (*pf)(obj))
{
	while( begin != end )
	{
		pf(&(*begin));
		++begin;
	}
}

#endif 
