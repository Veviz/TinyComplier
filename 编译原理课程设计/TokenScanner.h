#pragma once
/************************************************************************/
/*词法分析
 *输入：源文件
 *输出：Token流
 * 尚未完成：
 1.showSourceCode()*/
/************************************************************************/
#include "Whole.h"
//////////////////////////////////////////////////////////////////////////
class SymbolTab;
class TokenScanner
{
	string inputBuffer;//输入缓冲区
	int lineIndex;//句子的指示器
	int preIndex;//前一个Token的起始位置，用于出现语法错误时进行插入操作，从而恢复语法分析
	int lineNum;//记录行号
	fstream source_fileP;//源程序文件指针
	fstream list_fileP;//词法分析结果的输出
	SymbolTab *symTab;//符号表
public:
	TokenScanner(SymbolTab *st);
	~TokenScanner(void);
	void initialScanner(string filename);
	void showSourceCode();//在屏幕上显示源文件的内容
	void closeFiles();

	Token getToken();//扫描器的主程序
	int getNextChar();//从文件里读取一行，存入输入缓冲区；从缓冲区内一个个取字符
	void ungetNextChar();//把多读的一个字符送回缓冲区
	void insertToken();//将识别出来的Token插入Token表中
	MyTokenType isReservedWord(string word);//查表，word是否为保留字，若是则返回其对应的枚举值，否则返回ID
	void outPutToken(Token tk);//把Token输出到list文件中.
	void editBuffer(char ch);//修改输入缓冲区，用于错误处理
};
//////////////////////////////////////////////////////////////////////////
