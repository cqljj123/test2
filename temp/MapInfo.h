//lexaInfo.h head file
#ifndef _MAPINFO_H_
#define _MAPINFO_H_

#include "stdafx.h"

//����ӳ�����,����������������
namespace MAPINFO
{
	/* ��ϸ�ĳ�Ա�����÷�����ͼ���������������� */

	//����ӳ�䣬����������������������
	class FunctionMap
	{
	public:
		//���캯�����Ҹ���Ĭ�ϵ�һ������ָ���Ƿ���Ҫ����Ա��ʼ��
		FunctionMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	protected:
		map<string,int> _FuncMap;
	};

	//������ӳ����࣬������������������
	class OperatorMap
	{
	public:
		OperatorMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	private:
		map<string,int> _OperatorMap;
	};

	//����ӳ�����,����������������
	class SymbMap
	{
	public:
		//���캯�����Ҹ���Ĭ�ϵ�һ������ָ���Ƿ���Ҫ����Ա��ʼ��
		SymbMap(bool flags=false);
		virtual int GetMeans(const string& word);
		virtual string GetWordName(int means);
	protected:
		virtual void InitInstance();
	private:
		map<string,int> _SympMap;
	};

	//����ӳ���������࣬���ڹ���ӳ���
	class WordMap:public FunctionMap,public OperatorMap,public SymbMap
	{
	public:
		//styleָ�������������͵�ӳ�������ܹ�����������3�ֻ������,���˳���ռ̳е�˳��
		static WordMap* Create(int style);
		/*
		**  ���캯�����Ҹ���Ĭ�ϵ�һ������ָ���Ƿ���Ҫ����Ա��ʼ��
		**	ʹ��000��ʾҪ��ʼ����λ����һ��λ�����һ����
		**	�������ƣ����� 100��ʾ��ʼ��FuctionMap,110��ʾ��ʼ��FunctionMap��OperatorMap
		**  111��ʾȫ����ʼ��
		**	���˳���ռ̳е�˳��
		*/
		WordMap(int flags=0);
		/*����һ��string���ͼ��õ����Ƿ����ˣ���������򷵻���Ӧ�ı��룬
		 *���򽫷���-1ֵ*/
		virtual int GetMeans(const string& word);
		/*����һ��int���ͼ��ñ����Ƿ��ж�Ӧ�ĵ��ʣ�����ж�Ӧ�ĵ����򷵻���Ӧ�ĺ����ַ���
		 *���򽫷���""ֵ*/
		virtual string GetWordName(int means);
		//���ز��������ʱ���,δ�����򷵻�0ֵ
		int GetOperatorMeans(const string& word){
			return OperatorMap::GetMeans(word);
		}
		//���ط��ŵ��ʵı���,δ�����򷵻�0ֵ
		int GetSymbMeans(const string& word){
			return SymbMap::GetMeans(word);
		}
		//���غ������ʵı���,δ�����򷵻�0ֵ
		int GetFuncMeans(const string& word){
			return FunctionMap::GetMeans(word);
		}
	protected:
		//������Ա������ʼ����Ա������Ա��Ӧ�ĺ��������������������캯������
		virtual void InitInstance();
	};
}

#endif