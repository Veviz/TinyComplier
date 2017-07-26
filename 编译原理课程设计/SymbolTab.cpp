#include "stdafx.h"
#include "SymbolTab.h"
//////////////////////////////////////////////////////////////////////////
SymbolTab::SymbolTab(void)
{
	for (int i = 0; i < SYMBOL_SIZE; i++)
	{//��ʼ�����ű�
		HashTable[i] = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////

SymbolTab::~SymbolTab(void)
{
}
//////////////////////////////////////////////////////////////////////////
//��һ��Token������ű�
void SymbolTab::insertTab(Token tk)
{
	int hv = hashVal(tk.name);
	symbolTerm tPointer = HashTable[hv];

	while ((tPointer) && (tPointer->name != tk.name))
	{//�ڼ�������Ĺ�ϣֵ��Ӧ������Ѱ�Ҹ�����
		tPointer = tPointer->next;
	}

	if (tPointer == NULL)
	{//��û�ҵ��������
		tPointer = new SymbolTerm;
		tPointer->name = tk.name;
		tPointer->LineList.push_back(tk.lineNum);
		tPointer->memloc = tk.entry;
		tPointer->next = HashTable[hv];
		HashTable[hv] = tPointer;//������ͷ��㴦����
	} 
	else
	{//�����ID�Ѵ��ڣ����������ֵ��к�
		tPointer->LineList.push_back(tk.lineNum);
	}
}
//////////////////////////////////////////////////////////////////////////
//����tk�ĵ�ַ����δ�ҵ��򷵻�-1
int SymbolTab::findToken(Token tk)
{
	int hv = hashVal(tk.name);
	symbolTerm termP = HashTable[hv];

	while ((termP) && (termP->name != tk.name))
	{//�ڼ�������Ĺ�ϣֵ��Ӧ������Ѱ�Ҹ�����
		termP = termP->next;
	}

	int result;
	if (termP)
	{
		result = termP->memloc;
	} 
	else
	{
		result = -1;
	}

	return result;
}
//////////////////////////////////////////////////////////////////////////
//����Ļ����ʾ���ű�
void SymbolTab::printTable()
{

}
//////////////////////////////////////////////////////////////////////////
//����s��hashֵ
int SymbolTab::hashVal(string s)
{
	int val = 0;
	for (int i = 0; i < s.length(); i++)
	{
		val = ((val << 4) + s[i]) % SYMBOL_SIZE;
	}
	return val;
}
//////////////////////////////////////////////////////////////////////////


