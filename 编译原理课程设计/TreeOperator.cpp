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
/* ������mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* ThirdChild)
 * ���ã�����һ�������ֽ�㣬�����s
 * ˵������Tiny���ԣ��κν�������3�����ӣ�if-then-else�������first��second��third������������
 *		��ֻ���������ӣ���thirdChild=NULL��firstChild����������secondChild��������*/
/************************************************************************/
TreeNode * TreeOperator::mknode(Token tk,string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* thirdChild)
{
	TreeNode * tn = new TreeNode;
	tn->child[0] = firstChild;
	tn->child[1] = secondChild;
	tn->child[2] = thirdChild;
	tn->lineNUM = tk.lineNum;
	tn->name = s;
	tn->nodeKind = StmtK;//��������
	tn->op = 0;
	tn->reservedType = tk.ttype;//��Ǳ���������
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
/* ������mk_op_node(int lineno,bool opFlag,char op,TreeNode* leftChild,TreeNode* rightChild)
 * ���ã�����һ���������㣬�����op
 * opFlag = false����ǲ���ʽ,��������������
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
	tn->reservedType = EQUAL;//opĬ��Ϊequal
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
	tn->type = opFlag?Integer:Boolean;//��ǽ������
	tn->val = -1;//op��valĬ��Ϊ-1;
	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ������mk_id_leaf(Token tk)
 * ���ã�����һ����ʶ����㣬������idS,һ����entryָ���ʶ���ڷ��ű��е����*/
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
	tn->op = 0;//ID��op��Ϊ\0
	tn->reservedType = ID;
	tn->sibling = NULL;
	tn->falselist = NULL;
	tn->Nnextlist = NULL;
	tn->truelist = NULL;
	tn->Snextlist = NULL;
	tn->type = Integer;
	tn->val = -1;//ID��valĬ��Ϊ-1;

	treeStack.push_back(tn);
	return tn;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ������mk_num_leaf(Token tk)
 * ���ã�����һ������㣬,һ����val�������ֵ*/
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
/* ������traverse(TreeNode* root,SemanticsAnalyzer sAnalyZer)
 * ���ܣ�����һ����rootΪ���ڵ����,����dealRoot�������в���
 * */
/************************************************************************/
//����һ���﷨��
void TreeOperator::traverse(TreeNode * root,SemanticsAnalyzer sAnalyZer)
{
	if (root != NULL)
	{
		sAnalyZer.checkNodeType(root);
		for (int i = 0; i < MAX_CHILDREN_NUM; i++)
		{//�ݹ����������
			traverse(root->child[i],sAnalyZer);
		}
		traverse(root->sibling,sAnalyZer);//�������ֵ�����
	}
}
//////////////////////////////////////////////////////////////////////////


