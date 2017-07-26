#include "stdafx.h"
#include "Parser.h"
#include "TokenScanner.h"
#include "ErrorHandler.h"
//////////////////////////////////////////////////////////////////////////
Parser::Parser(TokenScanner *Scanner,ErrorHandler * eHandler)
{
	tkScanner = Scanner;
	errHandler = eHandler;
}
//////////////////////////////////////////////////////////////////////////
Parser::~Parser(void)
{
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 语法分析主函数
 * 功能：根据SLR分析表进行语法分析，并按照语义规则建立抽象语法树*/
/************************************************************************/
TreeNode* Parser::parse()
{
	bool errorSign=false;//为真时表示在语法分析过程中遇到语法错误，否则分析顺利
	int nexState;//记录下一状态
	int lengthProducer;//记录产生式长度
	int col,row;
	syntaxTree = NULL;//初始化语法树头结点
	stateStack.push_back(0);//初始状态入栈
	reduceTag = false;
	do 
	{
		if (!reduceTag)
		{//如果上一循环的动作是归约则不需要再次获得新的Token
			curToken = tkScanner->getToken();//从词法分析器那获取一个Token
		}

		curToken.nptr = NULL;
		row = stateStack[stateStack.size() - 1];
		col = curToken.ttype;
		tableVal = analyTable[row][col];//获取ACTION的值

		if (!tableVal || tableVal >= STATE_NUM)
		{//出现语法错误
			if(!syntaxErr())//进行错误处理
				return NULL;	//如果错误不可处理，则退出分析过程
			errorSign=true;
		}
		else
		{
			if (tableVal < 0)
			{//值小于0则移进
				reduceTag = false;
				nexState = -tableVal;//取反得到下一状态
				stateStack.push_back(nexState);
				charStack.push_back(curToken);
			} 
			else
			{//值大于0则归约
				leftChar.lineNum = curToken.lineNum;
				reduceTag = true;
				tableVal--;
				lengthProducer = producerTable[tableVal].rightLength;//产生式右部的长度
				leftChar.ttype = producerTable[tableVal].lChar;//产生式的左部

				sematicDeal(lengthProducer,tableVal);//按语义规则进行属性修改

				for (int i = 0; i < lengthProducer; i++)
				{
					stateStack.pop_back();
					charStack.pop_back();
				}
				nexState = analyTable[stateStack[stateStack.size() - 1]][leftChar.ttype];//即ACTION[Sm-r,A]
				stateStack.push_back(nexState);
				charStack.push_back(leftChar);
			}
		}
	} while (charStack[charStack.size() - 1].ttype != programC);//直到文件结束为止
	if (curToken.ttype != END_FILE)
	{//错误处理：文件尚未结束，代码已结束

	}
	if(!errorSign){//没有遇到语法错误则返回语法树的根节点以便后续执行
		return syntaxTree;
	}else
	{//遇到语法错误，不管是否可以继续都终止语法树的生成
		return NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 按语义规则进行处理
 * */
/************************************************************************/
void Parser::sematicDeal(int lengthProducer,int tableVal)
{
	vector <Token> tempNptr;
	leftChar.nptr = NULL;
	tempNptr.push_back(leftChar);//先推入一个产生式左部符号的综合属性。
	for (int i = 1; i <= lengthProducer; i++)
	{//把该产生式所有字符的综合属性传给语义规则函数，进行相应的修改
		tempNptr.push_back(charStack[charStack.size() - 1 - lengthProducer + i]);
	}
	tempNptr = producerTable[tableVal].sematicRule(tableVal,tempNptr);//按语义规则对综合属性进行处理

	leftChar.nptr = tempNptr[0].nptr;//归约式左部经语义规则处理后其综合属性的结果。

	if (tableVal == S_D_NO)
	{//当用1号归约式stmt-sequence(S) →stmt-sequence(S) ；statement(D) 进行归约时，要指明S的兄弟是D
		TreeNode * next = (*(tempNptr[1].nptr)).sibling;
		TreeNode * preNext = next;
		while (next)
		{
			preNext = next;
			next = next->sibling;
		}
		if (!preNext)
		{
			(*(tempNptr[1].nptr)).sibling = tempNptr[3].nptr;//即S.nextnode = D.nptr;

		} 
		else
		{
			(*(preNext)).sibling = tempNptr[3].nptr;//即S.nextnode = D.nptr;
		}
	}
	if (!syntaxTree && !tableVal)
	{//若syntaxTree为空，且已归约到Program时，对syntaxTreee进行赋值
		syntaxTree = leftChar.nptr;
	}
	for (int i = 1; i <= lengthProducer; i++)
	{//归约式右部在栈顶
		charStack[charStack.size() - 1 - lengthProducer + i] = tempNptr[i];
	}
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*语法错误处理
/************************************************************************/
bool Parser::syntaxErr()
{
	bool sign=true;
	switch (tableVal)
	{
	case 0://不做错误处理直接退出
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR,compiler is exiting!");
		sign=false;
		break;
	case SEMI_DEL://多一个分号
		reduceTag = true;
		charStack.pop_back();//弹出分号
		stateStack.pop_back();//弹出栈顶状态
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR: unexpected semicolon!");
		break;
	case ADD_BRACKET://少一个右括号
		reduceTag = false;
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR: right parenthesis!");
		tkScanner->editBuffer(')');
		break;
	case DEL_BRACKET://多一个右括号
		reduceTag = false;
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR：unexpected right parenthesis!");
		break;
	default:
		break;
	}
	return sign;
}
//////////////////////////////////////////////////////////////////////////



