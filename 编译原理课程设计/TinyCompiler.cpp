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
	symbolTable = new SymbolTab;//符号表对象
	errHandler = new ErrorHandler;
	syntaxTree=NULL;//语法树
}
//////////////////////////////////////////////////////////////////////////
TinyCompiler::~TinyCompiler(void)
{

}
//////////////////////////////////////////////////////////////////////////
//编译器的主控程序
bool TinyCompiler::mainProcess(string filename)
{
	/************************************************************************/
	/* 词法分析阶段                                                         */
	/************************************************************************/
	errHandler->showMessage("TinyComplier启动生成...");
	code_Sanner = new TokenScanner(symbolTable);
	code_Sanner->initialScanner(filename);//初始化扫描器
	code_Sanner->showSourceCode();//在屏幕上显示源文件的内容

	/************************************************************************/
	/*语法分析阶段                                                          */
	/************************************************************************/
	errHandler->showMessage("语法分析已启动...");
	code_Parser = new Parser(code_Sanner,errHandler);	
	syntaxTree = code_Parser->parse();
	if(!syntaxTree)	//语法分析失败则退出执行
	{//退出程序并释放所打开的文件
		code_Sanner->closeFiles();
		errHandler->showMessage("语法分析失败...");
		errHandler->showMessage("TinyComplier已终止...");
		return false;
	}
	errHandler->showMessage("语法分析成功...");
	errHandler->showMessage("语法树生成已启动...");
	printTree(syntaxTree,filename);//打印语法树
	errHandler->showMessage("语法树生成成功...");
	/************************************************************************/
	/* 语义分析阶段                                                         */
	/************************************************************************/
	code_Analyzer = new SemanticsAnalyzer(errHandler);
	code_Analyzer->checkType(syntaxTree);//进行类型检查
	code_Analyzer->SemantemeAnalyse(syntaxTree);
	/************************************************************************/
	/* 目标代码生成阶段                                                     */
	/************************************************************************/
	//======================================================================
	//transzw();//将生成的三地址代码转换为汇编

	//=======================================================================
	code_Sanner->closeFiles();//退出程序前释放程序占用的文件资源
	return true;
}
//////////////////////////////////////////////////////////////////////////
//打印语法树
void TinyCompiler::printTree(TreeNode* syntaxTree,string filename)
{	
	filename.assign(filename,0,filename.length()-4);	
	filename += ".tre";
	file.open(filename,ios::out);
	if(file.fail())
	{
		CString message;
		message.Format("%s",filename);
		errHandler->showMessage(message+" 打开失败！");
		errHandler->showMessage("TinyComplier已退出...");
		return;
	}
	TraversalTree(syntaxTree,0);
	file.close();
}
//////////////////////////////////////////////////////////////////////////
//先序遍历语法数
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

