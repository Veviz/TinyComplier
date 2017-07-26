#pragma once
#include "Whole.h"
//符号表定义及其一些操作
class SymbolTab
{
public:
	symbolTerm HashTable[SYMBOL_SIZE];
	SymbolTab(void);
	~SymbolTab(void);

	void insertTab(Token tk);//将一个Token插入符号表,并返回其符号表入口
	int findToken(Token tk);//返回tk的地址，若未找到则返回-1
	void printTable();//在屏幕上显示符号表

	int hashVal(string s);//计算s的hash值
};
