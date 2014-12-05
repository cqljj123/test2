//Interperter.h head file

#ifndef _INTERPERTER_H_
#define _INTERPERTER_H_

#include "WordInfo.h"

using namespace WORDINFO;

namespace INTERPERTER
{
	//��������
	typedef list<Word>::iterator AUTO;
	class FuncIpt;

	//���ʽ������
	class ExpIpt
	{
	public:
		ExpIpt(WordList* WList=NULL){
			SetWordListPtr(WList);
		}
	public:
		void SetWordListPtr(WordList* WList){
			_WList=WList;
		}
	public:
		//���㺯��

		/*����ת����ı��ʽ
		 *begin[in]���Ǹ��ദ��ĵ�һ��λ��
		 *end[in]:���ദ������һ��λ��
		 *FuncCla[in]����һ�εݹ飬���ݵĺ������ʽ�������,�Ա�ʹ�����ݹ���ת�����������ദ��*/
		double eval(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla);
	protected:
		//�жϡ���顢�Ƚ��ຯ��
		bool isnum(const Word& word);			//�ж��Ƿ�Ϊһ������
		bool isfunc(const Word& word);		    //�жϵ����Ƿ�Ϊ����

		bool isproc(char op1,char op2);			//�Ƚ���������������ȼ�												
	public:
		bool isopen(char ch);					//�ж��Ƿ�Ϊ�����

	protected:
		//ת���ຯ��
		double    atox(const string &str);		//���ַ�ת��ΪҪ���������
		//����׺���ʽת��Ϊ��׺
		//_WCListΪ��׺���ʽ����
		void convert(const AUTO& begin,const AUTO& end,FuncIpt& FuncCla,WordList& _WCList);

	private:
		//�����ຯ��
		int open_lev(char op1);				    //������ȼ�
		//������������
		double  count(double op1,double op2,char open);		 
	public:
		//������������Ҫ��������
		~ExpIpt() {}
	public:
		//��ʾ�ǶȻ��߻��ȵı�����0Ϊ�Ƕ�ֵ 1Ϊ������
		static int _sys;
	private:
		//����洢���ʽ�ĵ���������
		WordList *_WList;
		my_stack<double> _NumStck;	//�洢�������Ķ�ջ
	};

	//����������
	class FuncIpt
	{
	public:
		FuncIpt(WordList* WList=NULL){
			SetWordListPtr(WList);
		}
	public:
		void SetWordListPtr(WordList* WList){
			_WList=WList;
		}
	public:
		/*�������ձ��ʽ��������󷵻ؽ��
		 *begin[in,out]���Ǹ��ദ��ĵ�һ��λ��
		 *end[in,out]:������ʶ���Ľ���λ�ã�����Ľ���λ��Ӧ�ÿ���ķ�������ȥ��ʶ
		 *ExpCla[in]����һ�εݹ飬���ݵĳ�����ʽ�������,�Ա�ʹ�����ݹ���ת�����洦����
		 */
		double eval(AUTO& begin,const AUTO& end,ExpIpt& ExpCla);
	public:
		/*Analyse
		 *�������ڼ����ʽ����ȷ�ԣ�������һ����ȷ���ʽ���У�
		 *    ��ʹ��begin~end ���
		 *begin[in]  : ��ʼ����λ��,���λ�ò��ᱻ��д
		 *end[out]   : ���շ�����Ľ���λ��,���λ�ý��ᱻ��д
		 *errEnd[out]: һ������Ľ�����������ǰ��������ʽ����λ���Ǵ���� 
		 *symb[in]   : ��ʶ���Ƿ������һ��������1��ʾ�����һ������
		 *��ע�� begin��end�Ĳ������ݵ�ʱ��Ӧ����һ�µ�
		 */
		void Analyse(const AUTO& begin,AUTO& end,const AUTO& errEnd,int symb);
	protected:
		//����������ʽ
		void Process(AUTO& begin,AUTO& end,double result);
		//���㺯���Ľ��
		double count(const Word& fw,const array<double,4>& vr); 
	private:
		WordList *_WList;
	};
}

#endif