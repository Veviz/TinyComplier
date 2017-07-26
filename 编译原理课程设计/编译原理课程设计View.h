
// 编译原理课程设计View.h : C编译原理课程设计View 类的接口
//

#pragma once

class TinyCompiler;
class GramTree;
class C编译原理课程设计View : public CEditView
{
protected:
protected: // 仅从序列化创建
	C编译原理课程设计View();
	DECLARE_DYNCREATE(C编译原理课程设计View)

// 特性
public:
	C编译原理课程设计Doc* GetDocument() const;
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C编译原理课程设计View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//CString fileName;
// 生成的消息映射函数
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

#ifndef _DEBUG  // 编译原理课程设计View.cpp 中的调试版本
inline C编译原理课程设计Doc* C编译原理课程设计View::GetDocument() const
   { return reinterpret_cast<C编译原理课程设计Doc*>(m_pDocument); }
#endif

