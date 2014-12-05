///PhraseInfo.cpp source file
#include "PhraseInfo.h"
#include "Error.h"

using namespace MYERROR;
using namespace WORDCLASS;
using namespace WORDCODE;

//��Lexer�����Ķ���
using namespace PHRASEINFO;

void Lexer::InputExpression(const string& str)
{
	string temp;
	auto it=str.begin();

	//��¼��һ�ζ�ȡ���ǳ����ַ���������һ�ζ�ȡ���Ǻ����ַ�
	bool IsNum=false,IsFunc=false;
	/*��ͷ��'-'����Ϊ����,����ʹ�� at ������Ŀ����
	*������ʽֻ��һ�� - ����at���������׳��쳣��*/
	if( str.at(0) == '-' && NUMCHR( str.at(1) ) ){
		temp+=*it;
		++it;
		IsNum=true;
	}

	Word word;
	char OldOperator=' ';
	for( ; it != str.end(); it++ )
	{
		if( *it == ' ' ) continue; //�ո�����
		if( LUCHR(*it) ){//��ɺ������ַ�
			if( IsNum )
			{//��һ�ζ�ȡ�곣���ַ����󣬽����ʼ���������
				AddConstNumWord(word,temp);//��������Ľ�
				IsNum=false;
				//temp.erase();
			}
			temp+=*it;
			IsFunc=true;
		}
		else if( PNUMCHR(*it) )
		{//��ɳ������ַ�
			if( IsFunc ){//��һ�ζ�ȡ�꺯���ַ����󣬽����ʼ���������ȥ
				AddFunctionWord(word,temp);
				IsFunc=false;
				//temp.erase();
			}
			temp+=*it;
			IsNum=true;
		}
		else //������źͲ�����
		{
			if( IsFunc ) //��һ�ζ�ȡ�꺯����
				AddFunctionWord(word,temp,false);
			else if( IsNum ) //��һ�ζ�ȡ�곣����
				AddConstNumWord(word,temp,false);
			temp.erase();
			IsNum=IsFunc=false;

			if( SymbChr(*it) ) //����'(' ')' ','
			{
				temp=*it;
				AddSymbWord(word,temp);
			}
			else//��������¾�Ϊ������
			{
				temp=*it;
				if( *it == '-' ){
					if( MinusChr(OldOperator) ){//�������������ɸ��ŵ������
						IsNum=true;
						continue;
					}// end if
				}//end if
				AddOperatorWord(word,temp);
			}//end if
		}//end if
		OldOperator=*it;
	}//end for
	if( temp.size() )
	{
		if( IsNum )
			AddConstNumWord(word,temp);
		else
			AddFunctionWord(word,temp);
	}
}

inline void Lexer::AddConstNumWord(Word& word,string& temp,bool IsErase)
{
	word.SetMemInfo(WordClass::num,WordCode::constnum,temp);
	AddWord(word);
	if( IsErase )
		temp.erase();
}

inline void Lexer::AddFunctionWord(Word& word,string& temp,bool IsErase)
{
	WordAnalyse(temp,word);
	if( IsErase )
		temp.erase();
}

inline void Lexer::AddSymbWord(Word& word,string& temp,bool IsErase)
{
	if( temp[0] == '(' )
		word.SetMemInfo(WordClass::symb,WordCode::left,temp);
	else if( temp[0] == ')' )
		word.SetMemInfo(WordClass::symb,WordCode::right,temp);
	else
		word.SetMemInfo(WordClass::symb,WordCode::comma,temp);
	if( IsErase )
		temp.erase();
	AddWord(word);
}

inline void Lexer::AddOperatorWord(Word& word,string& temp,bool IsErase)
{
	int code=OperatorChr(temp[0]);
	word.SetMemInfo(WordClass::opera,code,temp);
	AddWord(word);
	if( IsErase )
		temp.erase();
}

bool Lexer::MinusChr(char ch)
{
	//�� ��-' ǰ��������·���ʱ�������Ϊ����
	switch(ch)
	{
	case '-':
	case '>':
	case '<':
	case '+':
	case '(':
	case ',':
		return true;
	default:
		break;
	}
	return false;
}

inline void Lexer::WordAnalyse(const string& str,Word& word)
{
	int code=this->_FuncMapClass.GetMeans(str);
	word.SetMemInfo(WordClass::func,code,str);
	AddWord(word);
}
