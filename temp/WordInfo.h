//Token.h head file

#ifndef _WORDINFO_H_
#define _WORDINFO_H_
#include "stdafx.h"

//�����
namespace WORDINFO
{
	//������,��¼�������ƣ���������
	class Word
	{
	public:
		Word(){}
		template<typename type>
		Word(int Class,int Encode,const type& Value){
			SetValueName(Value);
		}
	public:
		//���ص������
		int GetClass() const{
			return _class;
		}
		//���ص��ʱ���
		int GetEncode() const{
			return _encode;
		}
		//���ص�������
		string& GetWordName(){
			return _WordName;
		}
		string GetWordName() const{
			return _WordName;
		}
		//���ó�Ա��������𡢱��롢�뵥����Ϣ
		void SetMemInfo(int cla,int encode,const string& str){
			_class=cla;
			_encode=encode;
			_WordName=str;
		}
	private:
		string _WordName;//��������
		int _class;	   //�������
		int _encode;   //���ʱ���
	private:
		//��_WordName��ֵ,�����캯������
		template<typename type>
		void SetValueName(const type& value);
	};

	//����������
	class WordList
	{
	public:
		//����������
		virtual void AddWord(const Word& word);
		//��ȥ������
		virtual void DelWrod(Word& word);
		//�����ַ����б����ָ��
		virtual list<Word>* OnCreteObject(){
			return &_WordList;
		}
		int GetSize() const;
	protected:
		list<Word> _WordList;
	};
}
#endif