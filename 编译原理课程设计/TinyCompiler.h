#pragma once
/************************************************************************/
/* �ļ�����TinyCompiler.h
 * */
/************************************************************************/
#include "Whole.h"
//��δ��ɣ�
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
	TreeNode * syntaxTree;//�﷨��
	fstream file;
public:
	TinyCompiler(void);
	~TinyCompiler(void);

	bool mainProcess(string filename);//�����������س���
	void printTree(TreeNode* syntaxTree,string filename);//��ӡ�﷨��
	void TraversalTree(TreeNode * curnode,int spacenum);//����
	void ChooseType(TreeNode * curnode,int spacenum);//ѡ����Ӧ����������
	TreeNode * getTreeBoot(){return syntaxTree;};
};
//////////////////////////////////////////////////////////////////////////




