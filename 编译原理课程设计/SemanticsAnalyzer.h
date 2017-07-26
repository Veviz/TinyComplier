#pragma once
//语义分析器+代码生成器
#include "Whole.h"
class TreeOperator;
class ErrorHandler;
class SemanticsAnalyzer
{
	TreeOperator *treeAnalyzer;
	ErrorHandler *errHandler;

	int nextquad ; 
	Qtr * Headqtr;
	int tempnum;
public:
	SemanticsAnalyzer(ErrorHandler *eHandler);
	~SemanticsAnalyzer(void);

	void checkType(TreeNode * root);
	void checkNodeType(TreeNode * node);

	List * makelist(int nextquad);//产生链表
	void backpath(List * p , int t);//回填
	void SemantemeAnalyse(TreeNode * root);
	void Traversal(TreeNode * curnode , TreeNode * prenode , int i);//遍历语法树
	void emit(TreeNode * curnode,int flag);//生成三地址码
	List * merge(List * arg1 = NULL,List * arg2 = NULL,List * arg3 = NULL);//连接
	void Output();
};

