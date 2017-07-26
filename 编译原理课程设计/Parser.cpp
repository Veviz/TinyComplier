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
/* �﷨����������
 * ���ܣ�����SLR����������﷨��������������������������﷨��*/
/************************************************************************/
TreeNode* Parser::parse()
{
	bool errorSign=false;//Ϊ��ʱ��ʾ���﷨���������������﷨���󣬷������˳��
	int nexState;//��¼��һ״̬
	int lengthProducer;//��¼����ʽ����
	int col,row;
	syntaxTree = NULL;//��ʼ���﷨��ͷ���
	stateStack.push_back(0);//��ʼ״̬��ջ
	reduceTag = false;
	do 
	{
		if (!reduceTag)
		{//�����һѭ���Ķ����ǹ�Լ����Ҫ�ٴλ���µ�Token
			curToken = tkScanner->getToken();//�Ӵʷ��������ǻ�ȡһ��Token
		}

		curToken.nptr = NULL;
		row = stateStack[stateStack.size() - 1];
		col = curToken.ttype;
		tableVal = analyTable[row][col];//��ȡACTION��ֵ

		if (!tableVal || tableVal >= STATE_NUM)
		{//�����﷨����
			if(!syntaxErr())//���д�����
				return NULL;	//������󲻿ɴ������˳���������
			errorSign=true;
		}
		else
		{
			if (tableVal < 0)
			{//ֵС��0���ƽ�
				reduceTag = false;
				nexState = -tableVal;//ȡ���õ���һ״̬
				stateStack.push_back(nexState);
				charStack.push_back(curToken);
			} 
			else
			{//ֵ����0���Լ
				leftChar.lineNum = curToken.lineNum;
				reduceTag = true;
				tableVal--;
				lengthProducer = producerTable[tableVal].rightLength;//����ʽ�Ҳ��ĳ���
				leftChar.ttype = producerTable[tableVal].lChar;//����ʽ����

				sematicDeal(lengthProducer,tableVal);//�����������������޸�

				for (int i = 0; i < lengthProducer; i++)
				{
					stateStack.pop_back();
					charStack.pop_back();
				}
				nexState = analyTable[stateStack[stateStack.size() - 1]][leftChar.ttype];//��ACTION[Sm-r,A]
				stateStack.push_back(nexState);
				charStack.push_back(leftChar);
			}
		}
	} while (charStack[charStack.size() - 1].ttype != programC);//ֱ���ļ�����Ϊֹ
	if (curToken.ttype != END_FILE)
	{//�������ļ���δ�����������ѽ���

	}
	if(!errorSign){//û�������﷨�����򷵻��﷨���ĸ��ڵ��Ա����ִ��
		return syntaxTree;
	}else
	{//�����﷨���󣬲����Ƿ���Լ�������ֹ�﷨��������
		return NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* �����������д���
 * */
/************************************************************************/
void Parser::sematicDeal(int lengthProducer,int tableVal)
{
	vector <Token> tempNptr;
	leftChar.nptr = NULL;
	tempNptr.push_back(leftChar);//������һ������ʽ�󲿷��ŵ��ۺ����ԡ�
	for (int i = 1; i <= lengthProducer; i++)
	{//�Ѹò���ʽ�����ַ����ۺ����Դ��������������������Ӧ���޸�
		tempNptr.push_back(charStack[charStack.size() - 1 - lengthProducer + i]);
	}
	tempNptr = producerTable[tableVal].sematicRule(tableVal,tempNptr);//�����������ۺ����Խ��д���

	leftChar.nptr = tempNptr[0].nptr;//��Լʽ�󲿾��������������ۺ����ԵĽ����

	if (tableVal == S_D_NO)
	{//����1�Ź�Լʽstmt-sequence(S) ��stmt-sequence(S) ��statement(D) ���й�Լʱ��Ҫָ��S���ֵ���D
		TreeNode * next = (*(tempNptr[1].nptr)).sibling;
		TreeNode * preNext = next;
		while (next)
		{
			preNext = next;
			next = next->sibling;
		}
		if (!preNext)
		{
			(*(tempNptr[1].nptr)).sibling = tempNptr[3].nptr;//��S.nextnode = D.nptr;

		} 
		else
		{
			(*(preNext)).sibling = tempNptr[3].nptr;//��S.nextnode = D.nptr;
		}
	}
	if (!syntaxTree && !tableVal)
	{//��syntaxTreeΪ�գ����ѹ�Լ��Programʱ����syntaxTreee���и�ֵ
		syntaxTree = leftChar.nptr;
	}
	for (int i = 1; i <= lengthProducer; i++)
	{//��Լʽ�Ҳ���ջ��
		charStack[charStack.size() - 1 - lengthProducer + i] = tempNptr[i];
	}
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*�﷨������
/************************************************************************/
bool Parser::syntaxErr()
{
	bool sign=true;
	switch (tableVal)
	{
	case 0://����������ֱ���˳�
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR,compiler is exiting!");
		sign=false;
		break;
	case SEMI_DEL://��һ���ֺ�
		reduceTag = true;
		charStack.pop_back();//�����ֺ�
		stateStack.pop_back();//����ջ��״̬
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR: unexpected semicolon!");
		break;
	case ADD_BRACKET://��һ��������
		reduceTag = false;
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR: right parenthesis!");
		tkScanner->editBuffer(')');
		break;
	case DEL_BRACKET://��һ��������
		reduceTag = false;
		errHandler->printError(curToken.lineNum,"SYNTAX ERRROR��unexpected right parenthesis!");
		break;
	default:
		break;
	}
	return sign;
}
//////////////////////////////////////////////////////////////////////////



