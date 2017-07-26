#pragma once
/************************************************************************/
/* 文件名：TinyCompiler.h
 * */
/************************************************************************/
#include "Whole.h"
//尚未完成：
// 1.printTree(TreeNode* syntaxTree);
//////////////////////////////////////////////////////////////////////////

class TokenScanner;
class Parser;
class SymbolTab;
class SemanticsAnalyzer;
class ErrorHandler;
class TinyCompiler
{
	TokenScanner *code_Sanner;
	Parser *code_Parser;
//	CodeOptim code_Optimizer;
//	ToAssembly aim_Code;
	ErrorHandler *errHandler;
	SymbolTab *symbolTable;
	SemanticsAnalyzer * code_Analyzer;
	TreeNode * syntaxTree;//语法树
	fstream file;
public:
	TinyCompiler(void);
	~TinyCompiler(void);

	bool mainProcess(string filename);//编译器的主控程序
	void printTree(TreeNode* syntaxTree,string filename);//打印语法树
	void TraversalTree(TreeNode * curnode,int spacenum);//遍历
	void ChooseType(TreeNode * curnode,int spacenum);//选择相应结点属性输出
	TreeNode * getTreeBoot(){return syntaxTree;};
};
//////////////////////////////////////////////////////////////////////////




