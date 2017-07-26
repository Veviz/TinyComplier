#pragma once
/************************************************************************/
/* ������TreeOperator
 * ���ܣ�
 *		1.�ṩ�����﷨������Ҫ�ĺ��������������
 *		2.������������﷨������Ҫ�ĺ���
 * */
/************************************************************************/
#include "Whole.h"
class SemanticsAnalyzer;
class TreeOperator
{
	vector<TreeNode*> treeStack;//�������ڵ��ջ
public:
	TreeOperator(void);
	~TreeOperator(void);

	TreeNode * mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* thirdChild);
	TreeNode * mk_op_node(int lineno,bool opFlag,char op,TreeNode* leftChild,TreeNode* rightChild);
	TreeNode * mk_id_leaf(Token tk);
	TreeNode * mk_num_leaf(Token tk);

	void traverse(TreeNode * root,SemanticsAnalyzer sAnalyZer);//����һ���﷨��
};

