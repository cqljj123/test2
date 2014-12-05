#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#define N 5

template<class T>
class my_stack
{
private:
	int _top;      /*��ǰ��С*/	            
	T *_value;	  /*Ԫ��ֵ*/
	int _max;     /*���Ԫ��ֵ*/
public:
	my_stack(bool init=true);
	my_stack(int n);				//���ع��캯�������С
	my_stack(const my_stack<T> &s); //�������캯��
	T pop(bool &b);					//����ջ��Ԫ��
	bool empty() const;			    //�ж��Ƿ�Ϊ��ջ
	bool isfull() const;		    //�ж϶�ջ�Ƿ�����
	void push(const T& a);			//ѹ��һ��Ԫ��
	void pop();						//����һ������ջ������
	//void push(const T& a,bool *b);  //����һ��ѹ�뺯��
	void setsize(int n);            //���ö�ջ������С 
	int size() const;               //���ض�ջԪ��ʵ�ʴ�С
	void clear();				    //��ն�ջ
	~my_stack(){
		delete []_value;
	}
};

////////////////////////////////////
////class stackʵ���ļ� 

////////////////////////////
/*Ĭ�Ϲ��캯��*/
template<class T>
my_stack<T>::my_stack(bool init)
{
	if( init )
	{
		_top=-1;
		_max=N;
		_value=new T[_max];
	}
	else{
		_value=NULL;
		_max=_top=0;
	}
}/*end my_stack()*/

////////////////////////////
/*�������캯��*/
template<class T>
my_stack<T>::my_stack(const my_stack<T> &s)
{
	_value=new T[_max];
	_top=s._top;
	_max=s._max;
	for(int i=0;i<s._top+1;i++)
		_value[i]=s._value[i];
}/*end my_stack(const my_stack<T> &s)*/

///////////////////////////
//���ع��캯�������С
template<class T>
my_stack<T>::my_stack(int n)
{
	_max=n;
	_top=-1;
	_value=new T[n];
}

/*��ջԪ�ش�С����*/
template<class T>
inline int my_stack<T>::size() const
{
	return _top;
} 

///////////////////////////////
/*���ö�ջ������С*/
template<class T>
void my_stack<T>::setsize(int n)
{
	if(n<0)  return;
	_max=n;
}//end setsize

///////////////////////////////
//����ջ��Ԫ��
template<class T>
T my_stack<T>::pop(bool &b)
{
	//T a;
	if(empty())
	{
		b=false;
		return T();
	}
	//a=_value[_top--];
	b=true;
	return _value[_top--];
}//end pop

/////////////////////////////
//ѹ��ջ��Ԫ��
template<class T>
void my_stack<T>::push(const T& a)
{
	if(isfull())
	{
		_max=2*_max+1;
		T *_New=new T[_max*2];
		for( int i=0; i <= _top; i++ )
			*_New=*_value;
		delete []_value;
		_value=_New;
	}
	_value[++_top]=a;
}//end push

///////////////////////////////
//�ж��Ƿ��ջ
template<class T>
inline bool my_stack<T>::empty() const
{
	return _top==-1;
}//end empty

///////////////////////////////
//�ж��Ƿ��ջ����
template<class T>
inline bool my_stack<T>::isfull() const
{
	return _top==_max;
}//end isfull

////////////////////////////////
//����һ������ջ������
template<class T>
void my_stack<T>::pop()
{
	if(empty())
		return;
	_top--;
}

/*//////////////////////////////
//����һ��ѹ�뺯��
template<class T>
void my_stack<T>::push(const T& a,bool *b)
{
	if(isfull())
	{
		*b=false;
		return;
	}
	_value[++_top]=a;
	*b=true;
}//end push*/

template<class T>
void my_stack<T>::clear()
{
	delete []_value;
	_top=-1;
	_max=N;
	_value=new T[_max];
}

///////////////////////////////////
////end my_stack class's function
#endif











