
// ����ԭ��γ����View.h : C����ԭ��γ����View ��Ľӿ�
//

#pragma once

class TinyCompiler;
class GramTree;
class C����ԭ��γ����View : public CEditView
{
protected:
protected: // �������л�����
	C����ԭ��γ����View();
	DECLARE_DYNCREATE(C����ԭ��γ����View)

// ����
public:
	C����ԭ��γ����Doc* GetDocument() const;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~C����ԭ��γ����View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//CString fileName;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCharacteranalysis();
	afx_msg void OnTinycomplier();
	afx_msg void OnProduceasm();
	afx_msg void OnProducec();
	afx_msg void OnUpdateMessageDone(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // ����ԭ��γ����View.cpp �еĵ��԰汾
inline C����ԭ��γ����Doc* C����ԭ��γ����View::GetDocument() const
   { return reinterpret_cast<C����ԭ��γ����Doc*>(m_pDocument); }
#endif

