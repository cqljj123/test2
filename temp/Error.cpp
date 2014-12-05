///any.cpp
#include "Error.h"

//错误信息类
using namespace MYERROR;


any_error::any_error()
{
	error="NULL";
}

any_error::any_error(const string& info)
{
	error=info;
}

any_error::any_error(const any_error& obj)
{
	*this=obj;
}//结束构造函数的定义

any_error& any_error::operator =(const any_error& obj)
{
	this->error=obj.error;
	return *this;
}//结束重载符号的定义

const char* any_error::what()
{
	return this->error.c_str();
}
