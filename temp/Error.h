//error.h head file
#ifndef _ERROR_H_
#define _ERROR_H_

#include "stdafx.h"

//错误信息类 
namespace MYERROR
{
    class any_error
    {
    public:
        any_error();
        //设置错误的信息构造函数 
		any_error(const string& info);
        //拷贝构造函数
        any_error(const any_error& obj);
    public:
        //获取错误的信息 
        any_error& operator = (const any_error& obj);
        const char* what();
	private:
        string error;
    };//~ error info
}

#endif