#include "stdafx.h"
#include"OutputWnd.h"
#include "ErrorHandler.h"
#include "MainFrm.h"
#include "编译原理课程设计View.h"
//////////////////////////////////////////////////////////////////////////
ErrorHandler::ErrorHandler(void)
{
	errorCount = 0;
	firstError=true;
}
//////////////////////////////////////////////////////////////////////////
ErrorHandler::~ErrorHandler(void)
{
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 函数名：printError
 * 功能：打印错误信息
 * 参数messsage：错误信息
 * 参数lineno：错误行号
 * */
/************************************************************************/
void ErrorHandler::printError(int lineno,string message)
{
	CString errorMassage;
	errorCount++;
	errorMassage.Format("ERRROR NO.%d Line NO. %d %s",errorCount,lineno,message.c_str());
	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->FillBuildWindow(errorMassage);
	if(firstError){
		C编译原理课程设计View *pView=(C编译原理课程设计View *)((CMainFrame *)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
		CEdit *pEdit=&(pView->GetEditCtrl());
		int Istart=pEdit->LineIndex(lineno-1);
		if(Istart!=-1)
		{
			int length=pEdit->LineLength(Istart);
			pEdit->SetSel(Istart,Istart+length);
		}
		firstError=false;
	}
}
void ErrorHandler::showMessage(CString S)
{
	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->FillBuildWindow(S);
}
//////////////////////////////////////////////////////////////////////////
