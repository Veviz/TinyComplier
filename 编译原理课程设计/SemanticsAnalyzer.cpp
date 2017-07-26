#include "stdafx.h"
#include "SemanticsAnalyzer.h"
#include "TreeOperator.h"
#include "ErrorHandler.h"
#include "MainFrm.h"
//////////////////////////////////////////////////////////////////////////
SemanticsAnalyzer::SemanticsAnalyzer(ErrorHandler *eHandler)
{
	treeAnalyzer = new TreeOperator;
	errHandler = eHandler;
}


//////////////////////////////////////////////////////////////////////////
SemanticsAnalyzer::~SemanticsAnalyzer(void)
{

}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：checkType
 * 功能：对语法树进行类型检查*/
/************************************************************************/
void SemanticsAnalyzer::checkType(TreeNode * root)
{
	treeAnalyzer->traverse(root,*this);
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数：checkNodeType
 * 功能：对树节点进行类型检查*/
/************************************************************************/
void SemanticsAnalyzer::checkNodeType(TreeNode * node)
{
	switch (node->nodeKind)
	{
	case StmtK://句子类型
		switch (node->reservedType)
		{
		case if_stmtC:
			if (node->child[0]->type == Integer)
			{
				errHandler->printError(node->child[0]->lineNUM,"SEMANTICS ERROR：if test is not Boolean!");
			}
			break;
		case assign_stmtC:
			if (node->child[0]->type != Integer)
			{
				errHandler->printError(node->child[0]->lineNUM,"SEMANTICS ERROR：assignment of non-integer value!");
			}
			break;
		case repeat_stmtC:
			if (node->child[1]->type != Boolean)
			{
				errHandler->printError(node->child[0]->lineNUM,"SEMANTICS ERROR：repeat test is not Boolean!");
			}
			break;
		case write_stmtC:
			if (node->child[0]->type != Integer)
			{
				errHandler->printError(node->child[0]->lineNUM,"SEMANTICS ERROR：write of non-integer value!");
			}
			break;
		default:
			break;
		}
		break;
	case ExpK://表达式类型
		if ((node->child[0] && node->child[0]->type != Integer) || (node->child[1] && node->child[1]->type != Integer))
		{
			errHandler->printError(node->lineNUM,"SEMANTICS ERROR：Op applied to non-integer!");
		}
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
//产生链表
List *SemanticsAnalyzer:: makelist(int nextquad)
{
	List * NewNode = new List;
	NewNode->num = nextquad;
	NewNode->nextNode = NULL;
	return NewNode;
}
//////////////////////////////////////////////////////////////////////////
//回填
void SemanticsAnalyzer::backpath(List * p , int t)
{
	while(p!=NULL)
	{
		Qtr * q = Headqtr->nextNode;
		while(q!=NULL&&q->num!=p->num)
			q = q->nextNode;
		if(q!=NULL)
		{
			char num[3];
			itoa(t,num,10);
			string temp(num);
			q->result = temp;
		}
		else system("pause");
		p = p->nextNode;
	}
}
//////////////////////////////////////////////////////////////////////////
void SemanticsAnalyzer::SemantemeAnalyse(TreeNode * root)
{
	nextquad = 1;
	tempnum = 1;
	Headqtr = new Qtr;
	Headqtr->nextNode = NULL;
	TreeNode * temp = root;
	Traversal(temp,root,-1);
	Output();
}
//////////////////////////////////////////////////////////////////////////
//遍历语法树
void SemanticsAnalyzer::Traversal(TreeNode * curnode , TreeNode * prenode , int i)
{
		if(curnode->child[0] != NULL)
	{//遍历孩子
		if(curnode->reservedType == repeat_stmtC)
			curnode->quad[0] = nextquad;
		Traversal(curnode->child[0],curnode,0);
	}
	else 
	{
	/*	if((curnode->attr.op == NUM||curnode->attr.op == ID)&&i!=-1)
		{
			prenode->child[i].attr.op = curnode->attr.op;
			prenode->child[i].attr.name = curnode->attr.name;
			prenode->child[i].attr.val = curnode->attr.val;
		}*/
		if(curnode->reservedType == read_stmtC)
			emit(curnode,3);
		else return;
	}
	if(curnode->child[1] != NULL)
	{
		if(curnode->reservedType == if_stmtC)
			curnode->quad[0] = nextquad;
		Traversal(curnode->child[1],curnode,1);
	}
	if(curnode->child[2] != NULL)
	{
		curnode->Nnextlist = makelist(nextquad);
		emit(curnode,0);
		if(curnode->reservedType == if_stmtC)
			curnode->quad[1] = nextquad;
		Traversal(curnode->child[2],curnode,2);
	}
	if(curnode->nodeKind == ExpK)
	{
		if(curnode->reservedType == PLUS||curnode->reservedType == MINUS||curnode->reservedType == TIMES||curnode->reservedType == DIVIDE)
		{
			char newtemp[4] = "Z";
			char num[2];
			itoa(tempnum++,num,10);
			strcat(newtemp,num);
			string tempstring(newtemp);
			curnode->name = tempstring;
			switch(curnode->nodeKind)
			{
			case PLUS: curnode->val = curnode->child[0]->val + curnode->child[1]->val;
					   break;
			case MINUS: curnode->val = curnode->child[0]->val - curnode->child[1]->val;
					   break;
			case TIMES: curnode->val = curnode->child[0]->val * curnode->child[1]->val;
					   break;
			case DIVIDE: curnode->val = curnode->child[0]->val / curnode->child[1]->val;
			}
			emit(curnode,1);
		/*	if(i!=-1)
			{   //向父节点传参
				prenode->child[i].attr.name = curnode->attr.name;
				prenode->child[i].attr.val = curnode->attr.val;
			}*/
		}
		else if(curnode->reservedType == EQUAL||curnode->reservedType == LITTLE)
		{
			curnode->truelist = makelist(nextquad);
			curnode->falselist = makelist(nextquad+1);
			emit(curnode,2);
		}
	}
	else 
	{
		if(curnode->reservedType == assign_stmtC||curnode->reservedType == write_stmtC)
			emit(curnode,3);
		if(curnode->reservedType ==repeat_stmtC)
		{
			backpath(curnode->child[1]->falselist,curnode->quad[0]);
			curnode->Snextlist = curnode->child[1]->truelist;
			backpath(curnode->Snextlist,nextquad);		
		}
		if(curnode->reservedType == if_stmtC)
		{
			if(curnode->child[2] != NULL)
			{
				backpath(curnode->child[0]->truelist,curnode->quad[0]);
				backpath(curnode->child[0]->falselist,curnode->quad[1]);
				curnode->Snextlist = merge(curnode->child[1]->Snextlist,curnode->Nnextlist,curnode->child[2]->Snextlist);
				backpath(curnode->Snextlist,nextquad);
			}
			else
			{
				backpath(curnode->child[0]->truelist,curnode->quad[0]);
				curnode->Snextlist = merge(curnode->child[0]->falselist,curnode->child[1]->Snextlist);
				backpath(curnode->Snextlist,nextquad);
			}
		}
	}
	if(curnode->sibling != NULL)
		Traversal(curnode->sibling,curnode,-1);
}
//////////////////////////////////////////////////////////////////////////
//生成三地址码
void SemanticsAnalyzer::emit(TreeNode * curnode,int flag)
{
	Qtr * p = new Qtr;
	Qtr * q = Headqtr;
	if(flag ==0)
	{
		p->op = "j";
		p->arg1 = "#";
		p->arg2 = "#";
		p->result = "0";
		p->nextNode = NULL;
		p->num = nextquad++;
	}
	if(flag == 1)
	{
		string temp1(curnode->child[0]->name);
		string temp2(curnode->child[1]->name);
		string temp3(curnode->name);
		if(curnode->reservedType == PLUS)
			p->op = "+";
		if(curnode->reservedType == MINUS)
			p->op = "-";
		if(curnode->reservedType == TIMES)
			p->op = "*";
		if(curnode->reservedType == DIVIDE)
			p->op = "/";
		p->arg1 = temp1;
		p->arg2 = temp2;
		p->result = temp3;
		p->num = nextquad++;
		p->nextNode = NULL;
	}
	if(flag == 2)
	{
		string temp1(curnode->child[0]->name);
		string temp2(curnode->child[1]->name);
		Qtr * t = new Qtr;
		if(curnode->reservedType == EQUAL)
			p->op = "j=";
		if(curnode->reservedType == LITTLE)
			p->op = "j<";
		p->arg1 = temp1;
		p->arg2 = temp2;
		p->result = "0";
		p->num = nextquad++;
		p->nextNode = NULL;
		t->op = "j";
		t->arg1 = "#";
		t->arg2 = "#";
		t->result = "0";
		t->num = nextquad++;
		t->nextNode = NULL;
		p->nextNode = t;
	}
	if(flag == 3)
	{
		if(curnode->reservedType == assign_stmtC)
		{
			string temp1(curnode->child[0]->name);
			string temp2 = curnode->name.substr(0,curnode->name.length()-2);
			p->op = ":=";
			p->arg1 = temp1;
			p->arg2 = "#";
			p->result = temp2;
			p->num = nextquad++;
			p->nextNode = NULL;
		}
		if(curnode->reservedType == read_stmtC)
		{
			string temp2;
			temp2 = curnode->name.substr(5,curnode->name.length()-5);
			p->op = "read";
			p->arg1 = temp2;
			p->arg2 = "#";
			p->result = "#";
			p->num = nextquad++;
			p->nextNode = NULL;
		}
		if(curnode->reservedType == write_stmtC)
		{
			string temp1(curnode->child[0]->name);
			string temp2(curnode->name);
			p->op = "write";
			p->arg1 = temp1;
			p->arg2 = "#";
			p->result = "#";
			p->num = nextquad++;
			p->nextNode = NULL;
		}
	}
	while(q->nextNode!=NULL)
		q = q->nextNode;
	q->nextNode = p;
}
//////////////////////////////////////////////////////////////////////////
//连接
List *SemanticsAnalyzer:: merge(List * arg1,List * arg2,List * arg3)
{
	if(arg1!=NULL)
	{
		if(arg2!=NULL)
		{
			arg1->nextNode=arg2;
			arg2->nextNode=arg3;
		}
		else
		{
			arg1->nextNode=arg3;
		}
	}
	else
	{
		if(arg2!=NULL)
		{
			arg1=arg2;
			arg2->nextNode=arg3;
		}
		else
		{
			arg1=arg3;
		}
	}
	return arg1;
}
//////////////////////////////////////////////////////////////////////////
void SemanticsAnalyzer::Output()
{
	fstream file;
	file.open("tri_addr_code.txt",ios::out);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("tri_addr_code.txt open error!");
		pOut->FillBuildWindow("程序即将退出...");
		return ;
	}
	Qtr * p = Headqtr->nextNode;
	while(p != NULL)
	{
		file<<p->num<<' '<<p->op<<','<<p->arg1<<','<<p->arg2<<','<<p->result<<'\n';
		p = p->nextNode;
	}
	file<<nextquad<<' '<<'#'<<','<<'#'<<','<<'#'<<','<<'#';
	file.close();
}
//////////////////////////////////////////////////////////////////////////


