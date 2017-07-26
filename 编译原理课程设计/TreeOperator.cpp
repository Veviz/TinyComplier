#include "stdafx.h"
#include "TreeOperator.h"
#include "SemanticsAnalyzer.h"
//////////////////////////////////////////////////////////////////////////
TreeOperator::TreeOperator(void)
{
}
//////////////////////////////////////////////////////////////////////////
TreeOperator::~TreeOperator(void)
{
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* ThirdChild)
 * 作用：建立一个保留字结点，标号是s
 * 说明：对Tiny而言，任何结点最多有3个孩子（if-then-else情况），first、second、third按次序从左而右
 *		若只有两个儿子，则thirdChild=NULL，firstChild即左子树，secondChild即右子树*/
/************************************************************************/
TreeNode * TreeOperator::mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* thirdChild)
{
	TreeNode * tn = new TreeNode;
	tn->child[0] = firstChild;
	tn->child[1] = secondChild;
	tn->child[2] = thirdChild;
	tn->lineNUM = tk.lineNum;
	tn->name = s;
	tn->nodeKind = StmtK;//句子类型
	tn->op = 0;
	tn->reservedType = tk.ttype;//标记保留字类型
	tn->sibling = NULL;
	tn->type = Void;
	tn->val = -1;
	tn->falselist = NULL;
	tn->Nnextlist = NULL;
	tn->truelist = NULL;
	tn->Snextlist = NULL;
	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：mk_op_node(int lineno,bool opFlag,char op,TreeNode* leftChild,TreeNode* rightChild)
 * 作用：建立一个运算符结点，标号是op
 * opFlag = false标记是布尔式,否则是算术运算
/************************************************************************/
TreeNode * TreeOperator::mk_op_node(int lineno,bool opFlag,char op,TreeNode* leftChild,TreeNode* rightChild)
{
	TreeNode * tn = new TreeNode;

	tn->child[0] = leftChild;
	tn->child[1] = rightChild;
	tn->child[2] = NULL;
	tn->lineNUM = lineno;
	tn->name = op;
	tn->nodeKind = ExpK;
	tn->op = op;
	tn->reservedType = EQUAL;//op默认为equal
	if(op == '+')  tn->reservedType = PLUS;
	if(op == '-')  tn->reservedType = MINUS;
	if(op == '*')  tn->reservedType = TIMES;
	if(op == '/')  tn->reservedType = DIVIDE;
	if(op == '<')  tn->reservedType = LITTLE;
	tn->sibling = NULL;
	tn->falselist = NULL;
	tn->Nnextlist = NULL;
	tn->truelist = NULL;
	tn->Snextlist = NULL;
	tn->type = opFlag?Integer:Boolean;//标记结点属性
	tn->val = -1;//op的val默认为-1;
	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：mk_id_leaf(Token tk)
 * 作用：建立一个标识符结点，名字是idS,一个域entry指向标识符在符号表中的入口*/
/************************************************************************/
TreeNode * TreeOperator::mk_id_leaf(Token tk)
{
	TreeNode * tn = new TreeNode;
	tn->child[0] = NULL;
	tn->child[1] = NULL;
	tn->child[2] = NULL;
	tn->lineNUM = tk.lineNum;
	tn->name = tk.name;
	tn->nodeKind = ExpK;
	tn->op = 0;//ID的op设为\0
	tn->reservedType = ID;
	tn->sibling = NULL;
	tn->falselist = NULL;
	tn->Nnextlist = NULL;
	tn->truelist = NULL;
	tn->Snextlist = NULL;
	tn->type = Integer;
	tn->val = -1;//ID的val默认为-1;

	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：mk_num_leaf(Token tk)
 * 作用：建立一个数结点，,一个域val存放数的值*/
/************************************************************************/
TreeNode * TreeOperator::mk_num_leaf(Token tk)
{
	TreeNode * tn = new TreeNode;
	tn->child[0] = NULL;
	tn->child[1] = NULL;
	tn->child[2] = NULL;
	tn->lineNUM = tk.lineNum;
	tn->name = tk.name;
	tn->nodeKind = ExpK;
	tn->op = 0;
	tn->reservedType = NUM;
	tn->sibling = NULL;
	tn->falselist = NULL;
	tn->Nnextlist = NULL;
	tn->truelist = NULL;
	tn->Snextlist = NULL;
	tn->type = Integer;
	tn->val = atoi(tk.name.c_str());
	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：traverse(TreeNode* root,SemanticsAnalyzer sAnalyZer)
 * 功能：遍历一棵以root为根节点的树,依照dealRoot函数进行操作
 * */
/************************************************************************/
//遍历一棵语法树
void TreeOperator::traverse(TreeNode * root,SemanticsAnalyzer sAnalyZer)
{
	if (root != NULL)
	{
		sAnalyZer.checkNodeType(root);
		for (int i = 0; i < MAX_CHILDREN_NUM; i++)
		{//递归遍历其子树
			traverse(root->child[i],sAnalyZer);
		}
		traverse(root->sibling,sAnalyZer);//遍历其兄弟子树
	}
}
//////////////////////////////////////////////////////////////////////////


