#include "PhraseInfo.h"

using PHRASEINFO::Phrase;
using PHRASEINFO::AUTO;
using WORDCODE::WordCode;
using WORDCLASS::WordClass;

bool Phrase::AnalyseWord(const AUTO& begin,const AUTO& end)
{
	//���ö�ջ�����׺���ʽ����ȷ��
	int n_num=-1;  //�����������������Ƿ�ƥ��
	int c_num=0;  //��������Ƿ�ƥ��
	for( AUTO it=begin; it != end; it++ )
	{
		if( it->GetClass() == WORDCLASS::WordClass::func){
			if( !AnalyseFunc(it,end) ) return false;
			else
				n_num++;
		}
		else if( it->GetEncode() == WORDCODE::WordCode::right ) //������
			--c_num;
		else if( it->GetEncode() == WORDCODE::WordCode::left ) //������
			++c_num;
		else if( it->GetClass() == WORDCLASS::WordClass::num ) //����
		{
			if( !point_numAndch(it->GetWordName()) ){ //���������С���㲻�Ϸ�
				SetErrorInfo("�������Ϸ�:",it->GetWordName());
				return false;
			}
			++n_num;
		}
		else n_num--; //end if
		//Ϊ��ֹ�����ź�����������������ε�����£���Ҫ��ǰ���һ��
		if( n_num < -1 || c_num < 0 ){
			SetErrorInfo("���ʽ����ȷ","����������������ȷ");
			return false;
		}
	}

	if( n_num!=0 || c_num != 0 ){ 
		SetErrorInfo("���ʽ����ȷ","��������������ƥ��");
		return false;
	}
	return true;
}

bool Phrase::point_numAndch(const string& str)
{
	//��ͷ���� '.' �������ʽ����
	if( str[0] == '.' ) return false;
	int i=0,point=0;
	while( str[i] != '\0' )
		if( str[i++] == '.' ) ++point;

	if( point > 1 ) return false;
	return true;
}

bool Phrase::AnalyseFunc(AUTO& begin,const AUTO& end)
{
	//���ȼ�麯���Ƿ񱻶���
	if( !_WordMap->GetFuncMeans(begin->GetWordName()) ){
		SetErrorInfo("δ����ĺ�������",begin->GetWordName());
		return false;
	}

	//��������Ӧ�ý����������� '('
	AUTO it=begin;
	if( ++it == end ){
		SetErrorInfo("����ȱ��������",begin->GetWordName());
		return false;
	}

	if( it->GetEncode() == WordCode::left )
	{
		//�����Ĳ�������
		int par=TowFunctionStr(begin->GetEncode());
		++it;
		AUTO stk=it;
		//��ȡ�����Ĳ���ѹ���ջ��ȥ
		int Empty=0; //�������������ŵ�ƽ��
		int LastTowFunc=0;
		while( it != end )
		{
			if( (par>1) && TowFunctionStr(it->GetEncode()) > 1  )
				LastTowFunc+=TowFunctionStr(it->GetEncode())-1;
			else if( (par>1) && (it->GetEncode() == WordCode::comma) )
			{
				if( !LastTowFunc ){
					Empty=0;
					_StkStr.push(pair<AUTO,AUTO>(stk,it));
					stk=it;++stk;--par;
				}//end if
				LastTowFunc--;
				if( stk == end ){
						SetErrorInfo("����ȱ�ٲ����б�",begin->GetWordName());
						break;
				}//end if
			}
			else if( it->GetEncode() == WordCode::left ) Empty++;
			else if( it->GetEncode() == WordCode::right )
			{
				if( !Empty ){
					_StkStr.push(pair<AUTO,AUTO>(stk,it));
					--par;
					break;
				}
				Empty--;
			}//end if 
			++it;
		}//end while
		if( par ){
			SetErrorInfo("��������������",begin->GetWordName());
			return false;
		}
		else
			begin=it;
	}
	else
	{
		SetErrorInfo("����ȱ��������",begin->GetWordName());
		return false;
	}//end if
	return true;
}

void Phrase::Analyse()
{
	list<Word> *li=_WordList->OnCreteObject();
	if( AnalyseWord(li->begin(),li->end()) )
	{
		pair<AUTO,AUTO> obj;
		bool und;
		while( !_StkStr.empty() ){
			obj=_StkStr.pop(und);
			assert(und);
			if( !AnalyseWord(obj.first,obj.second) )
				break;
		}
	}
}