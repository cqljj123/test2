#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#define N 5

template<class T>
class my_stack
{
private:
	int _top;      /*当前大小*/	            
	T *_value;	  /*元素值*/
	int _max;     /*最大元素值*/
public:
	my_stack(bool init=true);
	my_stack(int n);				//重载构造函数分配大小
	my_stack(const my_stack<T> &s); //拷贝构造函数
	T pop(bool &b);					//弹出栈顶元素
	bool empty() const;			    //判断是否为空栈
	bool isfull() const;		    //判断堆栈是否满了
	void push(const T& a);			//压入一个元素
	void pop();						//另外一个弹出栈顶函数
	//void push(const T& a,bool *b);  //另外一个压入函数
	void setsize(int n);            //设置堆栈容量大小 
	int size() const;               //返回堆栈元素实际大小
	void clear();				    //清空堆栈
	~my_stack(){
		delete []_value;
	}
};

////////////////////////////////////
////class stack实现文件 

////////////////////////////
/*默认构造函数*/
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
/*拷贝构造函数*/
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
//重载构造函数分配大小
template<class T>
my_stack<T>::my_stack(int n)
{
	_max=n;
	_top=-1;
	_value=new T[n];
}

/*堆栈元素大小函数*/
template<class T>
inline int my_stack<T>::size() const
{
	return _top;
} 

///////////////////////////////
/*设置堆栈容量大小*/
template<class T>
void my_stack<T>::setsize(int n)
{
	if(n<0)  return;
	_max=n;
}//end setsize

///////////////////////////////
//弹出栈顶元素
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
//压入栈顶元素
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
//判断是否空栈
template<class T>
inline bool my_stack<T>::empty() const
{
	return _top==-1;
}//end empty

///////////////////////////////
//判断是否堆栈满了
template<class T>
inline bool my_stack<T>::isfull() const
{
	return _top==_max;
}//end isfull

////////////////////////////////
//另外一个弹出栈顶函数
template<class T>
void my_stack<T>::pop()
{
	if(empty())
		return;
	_top--;
}

/*//////////////////////////////
//另外一个压入函数
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











