
// ����ԭ��γ����View.cpp : C����ԭ��γ����View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "����ԭ��γ����.h"
#endif

#include "����ԭ��γ����Doc.h"
#include "����ԭ��γ����View.h"
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

// C����ԭ��γ����View

IMPLEMENT_DYNCREATE(C����ԭ��γ����View, CEditView)

BEGIN_MESSAGE_MAP(C����ԭ��γ����View, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C����ԭ��γ����View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CharacterAnalysis, &C����ԭ��γ����View::OnCharacteranalysis)
	ON_COMMAND(ID_TINYCOMPLIER, &C����ԭ��γ����View::OnTinycomplier)
	ON_COMMAND(ID_PRODUCEASM, &C����ԭ��γ����View::OnProduceasm)
	ON_COMMAND(ID_PRODUCEC, &C����ԭ��γ����View::OnProducec)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CharacterAnalysis,ID_TINYCOMPLIER, &C����ԭ��γ����View::OnUpdateMessageDone)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PRODUCEASM,ID_PRODUCEC, &C����ԭ��γ����View::OnUpdateMessageDone)
END_MESSAGE_MAP()

// C����ԭ��γ����View ����/����

C����ԭ��γ����View::C����ԭ��γ����View()
{
	// TODO: �ڴ˴���ӹ������
	
}

C����ԭ��γ����View::~C����ԭ��γ����View()
{
}

BOOL C����ԭ��γ����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// C����ԭ��γ����View ��ӡ


void C����ԭ��γ����View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C����ԭ��γ����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void C����ԭ��γ����View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void C����ԭ��γ����View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}

void C����ԭ��γ����View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C����ԭ��γ����View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C����ԭ��γ����View ���

#ifdef _DEBUG
void C����ԭ��γ����View::AssertValid() const
{
	CEditView::AssertValid();
}

void C����ԭ��γ����View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

C����ԭ��γ����Doc* C����ԭ��γ����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C����ԭ��γ����Doc)));
	return (C����ԭ��γ����Doc*)m_pDocument;
}
#endif //_DEBUG


// C����ԭ��γ����View ��Ϣ�������


void C����ԭ��γ����View::OnCharacteranalysis()
{
	// TODO: �ڴ���������������
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


void C����ԭ��γ����View::OnTinycomplier()
{
	// TODO: �ڴ���������������
	theApp.TinyC=new TinyCompiler;

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	CString fileName=theApp.getFileName();
	if(!fileName.GetLength())
	{
		MessageBox("���ȴ�Դ�ļ�","δ���ļ�",MB_OK);
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


void C����ԭ��γ����View::OnProduceasm()
{
	// TODO: �ڴ���������������
	CString fileName;
	fileName=theApp.getFileName();

	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
	COutputWnd *pOut=pFrame->getOutputWnd();
	pOut->clearBuildWindow();

	if(!theApp.TinyC)
	{
		MessageBox("������������","Error",MB_OK);
		return;
	}
	if(!transzw(fileName))//�����ɵ�����ַ����ת��Ϊ���
	{
		return;
	}
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);
}


void C����ԭ��γ����View::OnProducec()
{
	// TODO: �ڴ���������������
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
		MessageBox("������������","Error",MB_OK);
		outputC.close();
		return;
	}
	gramTree.change_tree(outputC,(theApp.TinyC)->getTreeBoot());
	outputC.close();
	AfxGetApp()->OpenDocumentFile(fileName)->OnCloseDocument();
	AfxGetApp()->OpenDocumentFile(fileName);
}
void C����ԭ��γ����View::OnUpdateMessageDone(CCmdUI *pCmdUI)
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






