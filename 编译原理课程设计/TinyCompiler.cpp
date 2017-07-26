#include "stdafx.h"
#include "TinyCompiler.h"
#include "TokenScanner.h"
#include "Parser.h"
#include "SymbolTab.h"
#include "ErrorHandler.h"
#include "SemanticsAnalyzer.h"
//#include "Assemble.h"
//////////////////////////////////////////////////////////////////////////
TinyCompiler::TinyCompiler(void)
{
	symbolTable = new SymbolTab;//���ű����
	errHandler = new ErrorHandler;
	syntaxTree=NULL;//�﷨��
}
//////////////////////////////////////////////////////////////////////////
TinyCompiler::~TinyCompiler(void)
{

}
//////////////////////////////////////////////////////////////////////////
//�����������س���
bool TinyCompiler::mainProcess(string filename)
{
	/************************************************************************/
	/* �ʷ������׶�                                                         */
	/************************************************************************/
	errHandler->showMessage("TinyComplier��������...");
	code_Sanner = new TokenScanner(symbolTable);
	code_Sanner->initialScanner(filename);//��ʼ��ɨ����
	code_Sanner->showSourceCode();//����Ļ����ʾԴ�ļ�������

	/************************************************************************/
	/*�﷨�����׶�                                                          */
	/************************************************************************/
	errHandler->showMessage("�﷨����������...");
	code_Parser = new Parser(code_Sanner,errHandler);	
	syntaxTree = code_Parser->parse();
	if(!syntaxTree)	//�﷨����ʧ�����˳�ִ��
	{//�˳������ͷ����򿪵��ļ�
		code_Sanner->closeFiles();
		errHandler->showMessage("�﷨����ʧ��...");
		errHandler->showMessage("TinyComplier����ֹ...");
		return false;
	}
	errHandler->showMessage("�﷨�����ɹ�...");
	errHandler->showMessage("�﷨������������...");
	printTree(syntaxTree,filename);//��ӡ�﷨��
	errHandler->showMessage("�﷨�����ɳɹ�...");
	/************************************************************************/
	/* ��������׶�                                                         */
	/************************************************************************/
	code_Analyzer = new SemanticsAnalyzer(errHandler);
	code_Analyzer->checkType(syntaxTree);//�������ͼ��
	code_Analyzer->SemantemeAnalyse(syntaxTree);
	/************************************************************************/
	/* Ŀ��������ɽ׶�                                                     */
	/************************************************************************/
	//======================================================================
	//transzw();//�����ɵ�����ַ����ת��Ϊ���

	//=======================================================================
	code_Sanner->closeFiles();//�˳�����ǰ�ͷų���ռ�õ��ļ���Դ
	return true;
}
//////////////////////////////////////////////////////////////////////////
//��ӡ�﷨��
void TinyCompiler::printTree(TreeNode* syntaxTree,string filename)
{	
	filename.assign(filename,0,filename.length()-4);	
	filename += ".tre";
	file.open(filename,ios::out);
	if(file.fail())
	{
		CString message;
		message.Format("%s",filename);
		errHandler->showMessage(message+" ��ʧ�ܣ�");
		errHandler->showMessage("TinyComplier���˳�...");
		return;
	}
	TraversalTree(syntaxTree,0);
	file.close();
}
//////////////////////////////////////////////////////////////////////////
//��������﷨��
void TinyCompiler::TraversalTree(TreeNode * curnode,int spacenum)
{
	ChooseType(curnode,spacenum);
	if(curnode->child[0] != NULL)
	{
		TraversalTree(curnode->child[0],spacenum+5);
	}
	if(curnode->child[1] != NULL)
	{
		TraversalTree(curnode->child[1],spacenum+5);
	}
	if(curnode->child[2] != NULL)
	{
		TraversalTree(curnode->child[2],spacenum+5);
	}
	if(curnode->sibling != NULL)
	{
		TraversalTree(curnode->sibling,spacenum);
	}
}
//////////////////////////////////////////////////////////////////////////
void TinyCompiler::ChooseType(TreeNode * curnode,int spacenum)
{
	for(int i =0 ;i<spacenum ;i++)
		file<<' ';
	if(curnode->reservedType == if_stmtC)
	   	file<<"if"<<endl;
	else if(curnode->reservedType == repeat_stmtC)
    		file<<"repeat"<<endl;
	else if(curnode->reservedType == assign_stmtC)
	    	file<<"assign to:"<<curnode->name.substr(0,curnode->name.length()-2)<<endl;
	else if(curnode->reservedType == read_stmtC)
	    	file<<"read:"<<curnode->name.substr(5,curnode->name.length()-5)<<endl;
	else if(curnode->reservedType == write_stmtC)
	    	file<<"write"<<endl;
	else if(curnode->reservedType == ID)
    		file<<"id:"<<curnode->name<<endl;
	else if(curnode->reservedType ==NUM)
	    	file<<"const:"<<curnode->name<<endl;
	else file<<"op:"<<curnode->op<<endl;
}

