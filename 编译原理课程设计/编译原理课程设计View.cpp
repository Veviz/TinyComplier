
// 编译原理课程设计View.cpp : C编译原理课程设计View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "编译原理课程设计.h"
#endif

#include "编译原理课程设计Doc.h"
#include "编译原理课程设计View.h"
#include  "MainFrm.h"
#include "analyzer.h"
#include "TinyCompiler.h"
#include "TreetoC.h"
#include "Assemble.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
Token curToken;

// C编译原理课程设计View

IMPLEMENT_DYNCREATE(C编译原理课程设计View, CEditView)

BEGIN_MESSAGE_MAP(C编译原理课程设计View, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C编译原理课程设计View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CharacterAnalysis, &C编译原理课程设计View::OnCharacteranalysis)
	ON_COMMAND(ID_TINYCOMPLIER, &C编译原理课程设计View::OnTinycomplier)
	ON_COMMAND(ID_PRODUCEASM, &C编译原理课程设计View::OnProduceasm)
	ON_COMMAND(ID_PRODUCEC, &C编译原理课程设计View::OnProducec)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CharacterAnalysis,ID_TINYCOMPLIER, &C编译原理课程设计View::OnUpdateMessageDone)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PRODUCEASM,ID_PRODUCEC, &C编译原理课程设计View::OnUpdateMessageDone)
END_MESSAGE_MAP()

// C编译原理课程设计View 构造/析构

C编译原理课程设计View::C编译原理课程设计View()
{
	// TODO: 在此处添加构造代码
	
}

C编译原理课程设计View::~C编译原理课程设计View()
{
}

BOOL C编译原理课程设计View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// C编译原理课程设计View 打印


void C编译原理课程设计View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C编译原理课程设计View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认 CEditView 准备
	return CEditView::OnPreparePrinting(pInfo);
}

void C编译原理课程设计View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 开始打印
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void C编译原理课程设计View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 结束打印
	CEditView::OnEndPrinting(pDC, pInfo);
}

void C编译原理课程设计View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C编译原理课程设计View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C编译原理课程设计View 诊断

#ifdef _DEBUG
void C编译原理课程设计View::AssertValid() const
{
	CEditView::AssertValid();
}

void C编译原理课程设计View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

C编译原理课程设计Doc* C编译原理课程设计View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C编译原理课程设计Doc)));
	return (C编译原理课程设计Doc*)m_pDocument;
}
#endif //_DEBUG


// C编译原理课程设计View 消息处理程序


void C编译原理课程设计View::OnCharacteranalysis()
{
	// TODO: 在此添加命令处理程序代码
	CString fileName;

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	fileName=theApp.getFileName();
	Analyzer chAnalysis;
	chAnalysis.setFileName(fileName);

	AfxGetApp()->m_pDocManager->SaveAllModified();

	if(!chAnalysis.analyze())
	{
		return;
	}
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".tkn";
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);

	theApp.curStep=1;
}


void C编译原理课程设计View::OnTinycomplier()
{
	// TODO: 在此添加命令处理程序代码
	theApp.TinyC=new TinyCompiler;

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	CString fileName=theApp.getFileName();
	if(!fileName.GetLength())
	{
		MessageBox("请先打开源文件","未打开文件",MB_OK);
		(theApp.TinyC)->~TinyCompiler();
		theApp.TinyC=NULL;
		return;
	}
	if(!theApp.TinyC->mainProcess(fileName.GetBuffer()))
	{
		fileName.ReleaseBuffer();
		return;
	}
	fileName.ReleaseBuffer();

	theApp.curStep=2;

	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".tre";
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);
}


void C编译原理课程设计View::OnProduceasm()
{
	// TODO: 在此添加命令处理程序代码
	CString fileName;
	fileName=theApp.getFileName();

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	if(!theApp.TinyC)
	{
		MessageBox("请先启动编译","Error",MB_OK);
		return;
	}
	if(!transzw(fileName))//将生成的三地址代码转换为汇编
	{
		return;
	}
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);
}


void C编译原理课程设计View::OnProducec()
{
	// TODO: 在此添加命令处理程序代码
	fstream outputC;
	GramTree gramTree;
	CString fileName=theApp.getFileName();
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".cpp";
	outputC.open(fileName,ios::out);

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	if(!theApp.TinyC)
	{
		MessageBox("请先启动编译","Error",MB_OK);
		outputC.close();
		return;
	}
	gramTree.change_tree(outputC,(theApp.TinyC)->getTreeBoot());
	outputC.close();
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);
}
void C编译原理课程设计View::OnUpdateMessageDone(CCmdUI *pCmdUI)
{
	if(ID_CharacterAnalysis==pCmdUI->m_nID)
	{
		if(theApp.curStep<0)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
	if(ID_TINYCOMPLIER==pCmdUI->m_nID)
	{
		if(theApp.curStep<1)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
	if(ID_PRODUCEASM==pCmdUI->m_nID)
	{
		if(theApp.curStep<2)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
	if(ID_PRODUCEC==pCmdUI->m_nID)
	{
		if(theApp.curStep<2)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
}






