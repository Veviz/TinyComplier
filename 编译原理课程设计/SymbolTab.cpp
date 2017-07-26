#include "stdafx.h"
#include "SymbolTab.h"
//////////////////////////////////////////////////////////////////////////
SymbolTab::SymbolTab(void)
{
	for (int i = 0; i < SYMBOL_SIZE; i++)
	{//初始化符号表
		HashTable[i] = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////

SymbolTab::~SymbolTab(void)
{
}
//////////////////////////////////////////////////////////////////////////
//将一个Token插入符号表
void SymbolTab::insertTab(Token tk)
{
	int hv = hashVal(tk.name);
	symbolTerm tPointer = HashTable[hv];

	while ((tPointer) && (tPointer->name != tk.name))
	{//在计算出来的哈希值对应的链中寻找该名字
		tPointer = tPointer->next;
	}

	if (tPointer == NULL)
	{//若没找到，则插入
		tPointer = new SymbolTerm;
		tPointer->name = tk.name;
		tPointer->LineList.push_back(tk.lineNum);
		tPointer->memloc = tk.entry;
		tPointer->next = HashTable[hv];
		HashTable[hv] = tPointer;//在链的头结点处插入
	} 
	else
	{//如果该ID已存在，则添加其出现的行号
		tPointer->LineList.push_back(tk.lineNum);
	}
}
//////////////////////////////////////////////////////////////////////////
//返回tk的地址，若未找到则返回-1
int SymbolTab::findToken(Token tk)
{
	int hv = hashVal(tk.name);
	symbolTerm termP = HashTable[hv];

	while ((termP) && (termP->name != tk.name))
	{//在计算出来的哈希值对应的链中寻找该名字
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
//在屏幕上显示符号表
void SymbolTab::printTable()
{

}
//////////////////////////////////////////////////////////////////////////
//计算s的hash值
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


