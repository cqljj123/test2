//���ʱ���������
#ifndef _DEF_H_
#define _DEF_H_

namespace WORDCODE
{
	//���ʱ���
	typedef enum tagCode{
		constnum=1, //����
		left, // '(' ������
		right,// ')' ������
		comma, // ',' ����
		assign,
		/*****�������ֽ���*****/
		equal, // '=' //Ԥ����
		add,  // '+'
		minus,// '-'
		mult,// '*'
		div, // '/'
		spow,//'^'
		max,//  ">"
		min,//  "<"
		smod,//  "%"
		/*****�����ֽ���*****/
		sqrt,//  "��ƽ����"
		sin, //  "����"
		cos, //  "����"
		tan, //  "����"
		acos,//	 "������"
		atan,//  "������"
		sinh,//  "˫������"
		cosh,//  "˫������"
		tanh,//  "˫������"
		exp, //  "��e����"
		lg,	 //  "����10Ϊ�׵Ķ���"
		ln,	 //  "����Ȼ����"
		abs,//   "�����ֵ"
		fact,//	 "��׳�"
		floor,// "�󲻴���ĳ�����������������floor(6.1)=6"
		/*****��Ԫ�����ָ���*****/
		sum,//	 "��sum(1,3)=1=2+3�ĺ�"
		log,//   "��log(a,b)�Ķ���"
		pow,//   "��a��b�η�"
		mod//  "ȡ�����"
	}WordCode;
}


namespace WORDCLASS
{
	//�������
	enum WordClass
	{
		def=1,	//�Զ���ı���
		func,	//����
		num,	//����
		symb,   //���� �� �� ��
		opera,  //��������� + - * / ...
	};
}

#define NUMCHR(ch)  ((ch)>='0' && (ch)<='9')
#define PNUMCHR(ch) (((ch)>='0' && (ch)<='9') || ch == '.' )
#define NUMSTR(ch)	( ((ch)>='0' && (ch)<='9') || (ch)>='a' && \
	(ch)<='z' || (ch)>='A' && (ch) <='Z' )

#define LOWCHR(ch) ((ch)>='a' && (ch)<='z')
#define UPPCHR(ch) ((ch)>='A' && (ch)<='Z')
#define LUCHR(ch) ( ((ch)>='a' && (ch)<='z') || ((ch)>='A' && (ch)<='Z') )

unsigned int OperatorChr(char ch_);
unsigned int SymbChr(char ch_);
unsigned int SymbOperatorChr(char ch_); 
inline unsigned int FunctionStr(int code_)
{
	if( code_ >= WORDCODE::WordCode::sqrt  && code_ <= WORDCODE::WordCode::floor )
		return true;
	return false;
}
inline unsigned int TowFunctionStr(int code_)
{
	if( code_ >= WORDCODE::WordCode::sum && code_ <= WORDCODE::WordCode::mod )
		return 2;
	return 1;
}

#endif
