///any.cpp
#include "Error.h"

//������Ϣ��
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
}//�������캯���Ķ���

any_error& any_error::operator =(const any_error& obj)
{
	this->error=obj.error;
	return *this;
}//�������ط��ŵĶ���

const char* any_error::what()
{
	return this->error.c_str();
}
