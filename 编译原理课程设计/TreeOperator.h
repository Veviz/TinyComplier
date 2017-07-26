#pragma once
/************************************************************************/
/* 类名：TreeOperator
 * 功能：
 *		1.提供建立语法树所需要的函数：创建树结点
 *		2.语义分析遍历语法树所需要的函数
 * */
/************************************************************************/
#include "Whole.h"
class SemanticsAnalyzer;
class TreeOperator
{
	vector<TreeNode*> treeStack;//保存树节点的栈
public:
	TreeOperator(void);
	~TreeOperator(void);

	TreeNode * mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* thirdChild);
	TreeNode * mk_op_node(int lineno,bool opFlag,char op,TreeNode* leftChild,TreeNode* rightChild);
	TreeNode * mk_id_leaf(Token tk);
	TreeNode * mk_num_leaf(Token tk);

	void traverse(TreeNode * root,SemanticsAnalyzer sAnalyZer);//遍历一棵语法树
};

