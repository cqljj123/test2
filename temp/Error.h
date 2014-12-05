//error.h head file
#ifndef _ERROR_H_
#define _ERROR_H_

#include "stdafx.h"

//������Ϣ�� 
namespace MYERROR
{
    class any_error
    {
    public:
        any_error();
        //���ô������Ϣ���캯�� 
		any_error(const string& info);
        //�������캯��
        any_error(const any_error& obj);
    public:
        //��ȡ�������Ϣ 
        any_error& operator = (const any_error& obj);
        const char* what();
	private:
        string error;
    };//~ error info
}

#endif