#pragma once
#include "Whole.h"
//���ű��弰��һЩ����
class SymbolTab
{
public:
	symbolTerm HashTable[SYMBOL_SIZE];
	SymbolTab(void);
	~SymbolTab(void);

	void insertTab(Token tk);//��һ��Token������ű�,����������ű����
	int findToken(Token tk);//����tk�ĵ�ַ����δ�ҵ��򷵻�-1
	void printTable();//����Ļ����ʾ���ű�

	int hashVal(string s);//����s��hashֵ
};
