#include "stdafx.h"
#include"OutputWnd.h"
#include "ErrorHandler.h"
#include "MainFrm.h"
#include "����ԭ��γ����View.h"
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
/* ��������printError
 * ���ܣ���ӡ������Ϣ
 * ����messsage��������Ϣ
 * ����lineno�������к�
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
		C����ԭ��γ����View *pView=(C����ԭ��γ����View *)((CMainFrame *)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
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
