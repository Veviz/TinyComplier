#pragma once
//���������+����������
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

	List * makelist(int nextquad);//��������
	void backpath(List * p , int t);//����
	void SemantemeAnalyse(TreeNode * root);
	void Traversal(TreeNode * curnode , TreeNode * prenode , int i);//�����﷨��
	void emit(TreeNode * curnode,int flag);//��������ַ��
	List * merge(List * arg1 = NULL,List * arg2 = NULL,List * arg3 = NULL);//����
	void Output();
};

