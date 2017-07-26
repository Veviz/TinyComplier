#pragma once
//语法分析+语义分析+中间代码生成
//输入：Token流
// 输出：语法树、四元式列表
// 
// 尚未完成：
// 1.语法错误如何处理
// 4.void Parser::syntaxErr()

#include "Whole.h"
#define S_D_NO 1//当用1号归约式stmt-sequence(S) →stmt-sequence(S) ；statement(D) 进行归约时，要指明S的兄弟是D
////////////////////////////////////////////////////////////////////////// 
/************************************************************************/
/* 建立AST所需要的函数                                                  */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
class TokenScanner;
class ErrorHandler;
class Parser
{
	Token leftChar;//产生式左部
	vector<int> stateStack;//状态栈
	vector<Token> charStack;//符号栈
	int tableVal;//记录查分析表所得的值
	bool reduceTag;//是否进行归约标记
	TokenScanner *tkScanner;//词法分析器
	ErrorHandler *errHandler;
	TreeNode * syntaxTree;
	Token curToken;//接收来自词法分析器的Token流
public:
	Parser(TokenScanner *Scanner,ErrorHandler * eHandler);
	~Parser(void);

	TreeNode* parse();//进行语法分析,返回一棵语法树
	void sematicDeal(int l,int tv);//按语义规则进行处理
	bool syntaxErr();//语法错误处理:打印错误的行数以及信息，并继续进行语法分析,返回值决定是否继续执行
//	void printError(int lineno,string message);//打印错误消息
};
//////////////////////////////////////////////////////////////////////////
