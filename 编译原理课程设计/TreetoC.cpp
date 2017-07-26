#include "stdafx.h"
#include"TreetoC.h"
#include "ErrorHandler.h"
void GramTree::printtab(fstream & file,int numtab)
{
	for(int i=0;i<numtab;i++)
	{
		file<<'\t';
	}
}

void GramTree::change_read(fstream & file,TreeNode * node,int tabnum)
{
	printtab(file,tabnum);
	file<<"cin>>";
	char name[81];
	//file<<node->child[0]->name<<endl;
	int i=5,j=0;
	strcpy(name,node->name.c_str());
	while(name[i]!='\0')
	{
		name[j]=name[i];
		i++;
		j++;
	}
	name[j]='\0';
	file<<name<<";"<<endl;
	if(node->sibling!=NULL)
	{
		switch(node->sibling->reservedType)
		{
		case read_stmtC:
			change_read(file,node->sibling,tabnum);
			break;
		case if_stmtC:
			change_if(file,node->sibling,tabnum);
			break;
		case write_stmtC:
			change_write(file,node->sibling,tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->sibling,tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->sibling,tabnum);
			break;
		case PLUS:
			change_op(file,node->sibling,tabnum);
			break;
		case MINUS:
			change_op(file,node->sibling,tabnum);
			break;
		case TIMES:
			change_op(file,node->sibling,tabnum);
			break;
		case DIVIDE:
			change_op(file,node->sibling,tabnum);
			break;
		case EQUAL:
			change_op(file,node->sibling,tabnum);
			break;
		case LITTLE:
			change_op(file,node->sibling,tabnum);
			break;
		default:
			break;
		}
	}

}
void GramTree::change_if(fstream & file,TreeNode * node,int tabnum)
{
	printtab(file,tabnum);
	file<<"if(";
	switch(node->child[0]->reservedType)
	{
	case EQUAL:
		change_op(file,node->child[0],tabnum);
		break;
	case LITTLE:
		change_op(file,node->child[0],tabnum);
		break;
	}
	file<<")"<<endl;
	tabnum++;
	printtab(file,tabnum-1);
	file<<"{"<<endl;
	if(node->child[1]!=NULL)
	{
		switch(node->child[1]->reservedType)
		{
		case read_stmtC:
			change_read(file,node->child[1],tabnum);
			break;
		case if_stmtC:
			change_if(file,node->child[1],tabnum);
			break;
		case write_stmtC:
			change_write(file,node->child[1],tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->child[1],tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->child[1],tabnum);
			break;
		case PLUS:
			change_op(file,node->child[1],tabnum);
			break;
		case MINUS:
			change_op(file,node->child[1],tabnum);
			break;
		case TIMES:
			change_op(file,node->child[1],tabnum);
			break;
		case DIVIDE:
			change_op(file,node->child[1],tabnum);
			break;
		case EQUAL:
			change_op(file,node->child[1],tabnum);
			break;
		case LITTLE:
			change_op(file,node->child[1],tabnum);
			break;
		default:
			break;
		}
	}
	printtab(file,tabnum-1);
	file<<"}"<<endl;
	if(node->child[2]!=NULL)
	{
		printtab(file,tabnum-1);
		file<<"else"<<endl;
		printtab(file,tabnum-1);
		file<<"{"<<endl;
		switch(node->child[2]->reservedType)
		{
		case read_stmtC:
			change_read(file,node->child[2],tabnum);
			break;
		case if_stmtC:
			change_if(file,node->child[2],tabnum);
			break;
		case write_stmtC:
			change_write(file,node->child[2],tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->child[2],tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->child[2],tabnum);
			break;
		case PLUS:
			change_op(file,node->child[2],tabnum);
			break;
		case MINUS:
			change_op(file,node->child[2],tabnum);
			break;
		case TIMES:
			change_op(file,node->child[2],tabnum);
			break;
		case DIVIDE:
			change_op(file,node->child[2],tabnum);
			break;
		case EQUAL:
			change_op(file,node->child[2],tabnum);
			break;
		case LITTLE:
			change_op(file,node->child[2],tabnum);
			break;
		default:
			break;
		}
		printtab(file,tabnum-1);
		file<<"}"<<endl;
	}

	if(node->sibling!=NULL)
	{
		switch(node->sibling->reservedType)
		{
		case read_stmtC:
			change_read(file,node->sibling,tabnum-1);
			break;
		case if_stmtC:
			change_if(file,node->sibling,tabnum-1);
			break;
		case write_stmtC:
			change_write(file,node->sibling,tabnum-1);
			break;
		case repeat_stmtC:
			change_repeat(file,node->sibling,tabnum-1);
			break;
		case assign_stmtC:
			change_assign(file,node->sibling,tabnum-1);
			break;
		case PLUS:
			change_op(file,node->sibling,tabnum-1);
			break;
		case MINUS:
			change_op(file,node->sibling,tabnum-1);
			break;
		case TIMES:
			change_op(file,node->sibling,tabnum-1);
			break;
		case DIVIDE:
			change_op(file,node->sibling,tabnum-1);
			break;
		case EQUAL:
			change_op(file,node->sibling,tabnum-1);
			break;
		case LITTLE:
			change_op(file,node->sibling,tabnum-1);
			break;
		default:
			break;
		}
	}
}
void GramTree::change_write(fstream & file,TreeNode * node,int tabnum)
{//表达式和IDname怎么区分
	TreeNode * cur;
	printtab(file,tabnum);
	file<<"cout<<";
	if(node->child[0]!=NULL)
	{
		cur=node->child[0];
		if(cur->reservedType==ID||cur->reservedType==NUM)
			file<<cur->name;
		else
		{
			file<<'\"';
			if(cur->reservedType==PLUS||cur->reservedType==MINUS||cur->reservedType==TIMES||cur->reservedType==DIVIDE||cur->reservedType==EQUAL||cur->reservedType==LITTLE)
				change_op(file,cur,tabnum);
			file<<'\"';
		}
	}
	file<<";"<<endl;
	if(node->sibling!=NULL)
	{
		switch(node->sibling->reservedType)
		{
		case read_stmtC:
			change_read(file,node->sibling,tabnum);
			break;
		case if_stmtC:
			change_if(file,node->sibling,tabnum);
			break;
		case write_stmtC:
			change_write(file,node->sibling,tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->sibling,tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->sibling,tabnum);
			break;
		case PLUS:
			change_op(file,node->sibling,tabnum);
			break;
		case MINUS:
			change_op(file,node->sibling,tabnum);
			break;
		case TIMES:
			change_op(file,node->sibling,tabnum);
			break;
		case DIVIDE:
			change_op(file,node->sibling,tabnum);
			break;
		case EQUAL:
			change_op(file,node->sibling,tabnum);
			break;
		case LITTLE:
			change_op(file,node->sibling,tabnum);
			break;
		default:
			break;
		}
	}
}
void GramTree::change_assign(fstream & file,TreeNode * node,int tabnum)
{
	TreeNode * cur;
	char name[81];
	printtab(file,tabnum);
	strcpy(name,node->name.c_str());
	int i=0;
	while(name[i]!=':')
		i++;
	name[i]='\0';
	file<<name;
	file<<"=";
	cur=node->child[0];
	if(cur->reservedType==PLUS||cur->reservedType==MINUS||cur->reservedType==TIMES||cur->reservedType==DIVIDE||cur->reservedType==EQUAL||cur->reservedType==LITTLE)
	{
		change_op(file,cur,tabnum);
		file<<";"<<endl;
	}
	if(cur->reservedType==ID||cur->reservedType==NUM)
	{
		file<<cur->name;
		file<<";"<<endl;
	}
	if(node->sibling!=NULL)
	{
		switch(node->sibling->reservedType)
		{
		case read_stmtC:
			change_read(file,node->sibling,tabnum);
			break;
		case if_stmtC:
			change_if(file,node->sibling,tabnum);
			break;
		case write_stmtC:
			change_write(file,node->sibling,tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->sibling,tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->sibling,tabnum);
			break;
		case PLUS:
			change_op(file,node->sibling,tabnum);
			break;
		case MINUS:
			change_op(file,node->sibling,tabnum);
			break;
		case TIMES:
			change_op(file,node->sibling,tabnum);
			break;
		case DIVIDE:
			change_op(file,node->sibling,tabnum);
			break;
		case EQUAL:
			change_op(file,node->sibling,tabnum);
			break;
		case LITTLE:
			change_op(file,node->sibling,tabnum);
			break;
		default:
			break;
		}
	}
}
void GramTree::change_op(fstream & file,TreeNode * node,int tabnum)
{
	TreeNode * cur;
	bool sign;//标记是否要加右括号
	cur=node->child[0];
	sign=false;
	if((node->reservedType==TIMES||node->reservedType==DIVIDE)&&(cur->reservedType==PLUS||cur->reservedType==MINUS))
		sign=true;
	if(sign)
		file<<"(";
	if(cur->reservedType==PLUS||cur->reservedType==MINUS||cur->reservedType==TIMES||cur->reservedType==DIVIDE||cur->reservedType==LITTLE||cur->reservedType==EQUAL)
		change_op(file,cur,tabnum);
	if(cur->reservedType==ID||cur->reservedType==NUM)
		file<<cur->name;
	if(sign)
		file<<")";
	switch(node->reservedType)
	{
	case PLUS:
		file<<"+";
		break;
	case MINUS:
		file<<"-";
		break;
	case TIMES:
		file<<"*";
		break;
	case DIVIDE:
		file<<"/";
		break;
	case LITTLE:
		file<<"<";
		break;
	case EQUAL:
		file<<"=";
		break;
	}
	cur=node->child[1];
	sign=true;
	if(((cur->reservedType==TIMES||cur->reservedType==DIVIDE)&&(node->reservedType==PLUS||node->reservedType==MINUS))||cur->reservedType==ID||cur->reservedType==NUM)
		sign=false;
	if(sign)
		file<<"(";
	if(cur->reservedType==PLUS||cur->reservedType==MINUS||cur->reservedType==TIMES||cur->reservedType==DIVIDE||cur->reservedType==LITTLE||cur->reservedType==EQUAL)
		change_op(file,cur,tabnum);
	if(cur->reservedType==ID||cur->reservedType==NUM)
		file<<cur->name;
	if(sign)
		file<<")";
}
void GramTree::change_repeat(fstream & file,TreeNode * node,int tabnum)
{
	printtab(file,tabnum);
	file<<"do"<<endl;
	printtab(file,tabnum);
	file<<"{"<<endl;
	tabnum++;
	TreeNode * cur;
	if(node->child[0]!=NULL)
	{
		switch(node->child[0]->reservedType)
		{
		case read_stmtC:
			change_read(file,node->child[0],tabnum);
			break;
		case if_stmtC:
			change_if(file,node->child[0],tabnum);
			break;
		case write_stmtC:
			change_write(file,node->child[0],tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->child[0],tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->child[0],tabnum);
			break;
		case PLUS:
			change_op(file,node->child[0],tabnum);
			break;
		case MINUS:
			change_op(file,node->child[0],tabnum);
			break;
		case TIMES:
			change_op(file,node->child[0],tabnum);
			break;
		case DIVIDE:
			change_op(file,node->child[0],tabnum);
			break;
		case EQUAL:
			change_op(file,node->child[0],tabnum);
			break;
		case LITTLE:
			change_op(file,node->child[0],tabnum);
			break;
		default:
			break;
		}
	}
	printtab(file,tabnum-1);
	file<<"}while(";
	file<<node->child[1]->child[0]->name;
	if(node->child[1]->reservedType==EQUAL)
		file<<"!=";
	else
		if(node->child[1]->child[0]->reservedType==LITTLE)
			file<<">=";
	cur=node->child[1]->child[1];
	if(cur->reservedType==PLUS||cur->reservedType==MINUS||cur->reservedType==TIMES||cur->reservedType==DIVIDE||cur->reservedType==LITTLE||cur->reservedType==EQUAL)
		change_op(file,cur,tabnum);
	if(cur->reservedType==ID||cur->reservedType==NUM)
		file<<cur->name;
	file<<");"<<endl;
	if(node->sibling!=NULL)
	{
		switch(node->sibling->reservedType)
		{
		case read_stmtC:
			change_read(file,node->sibling,tabnum);
			break;
		case if_stmtC:
			change_if(file,node->sibling,tabnum);
			break;
		case write_stmtC:
			change_write(file,node->sibling,tabnum);
			break;
		case repeat_stmtC:
			change_repeat(file,node->sibling,tabnum);
			break;
		case assign_stmtC:
			change_assign(file,node->sibling,tabnum);
			break;
		case PLUS:
			change_op(file,node->sibling,tabnum);
			break;
		case MINUS:
			change_op(file,node->sibling,tabnum);
			break;
		case TIMES:
			change_op(file,node->sibling,tabnum);
			break;
		case DIVIDE:
			change_op(file,node->sibling,tabnum);
			break;
		case EQUAL:
			change_op(file,node->sibling,tabnum);
			break;
		case LITTLE:
			change_op(file,node->sibling,tabnum);
			break;
		default:
			break;
		}
	}
}
void GramTree::change_tree(fstream &file,TreeNode * node)
{
	errorHandler=new ErrorHandler;
	errorHandler->showMessage("转C已启动生成...");
	file<<"#include<iostream>"<<endl;
	file<<"using namespace std;"<<endl;
	file<<"int main()"<<endl;
	file<<"{"<<endl;
	errorHandler->showMessage("已完成初始输入...");
	int tabnum=1;
	switch(node->reservedType)
	{
	case read_stmtC:
		change_read(file,node,tabnum);
		break;
	case if_stmtC:
		change_if(file,node,tabnum);
		break;
	case write_stmtC:
		change_write(file,node,tabnum);
		break;
	case repeat_stmtC:
		change_repeat(file,node,tabnum);
		break;
	case assign_stmtC:
		change_assign(file,node,tabnum);
		break;
	case PLUS:
		change_op(file,node,tabnum);
		break;
	case MINUS:
		change_op(file,node,tabnum);
		break;
	case TIMES:
		change_op(file,node,tabnum);
		break;
	case DIVIDE:
		change_op(file,node,tabnum);
		break;
	case EQUAL:
		change_op(file,node,tabnum);
		break;
	case LITTLE:
		change_op(file,node,tabnum);
		break;
	default:
		break;
	}
	file<<'\t'<<"return 0;"<<endl;
	file<<"}"<<endl;
	errorHandler->showMessage("转化成功...");
}