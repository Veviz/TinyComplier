
// ����ԭ��γ����.h : ����ԭ��γ���� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Whole.h"


// C����ԭ��γ����App:
// �йش����ʵ�֣������ ����ԭ��γ����.cpp
//
class TinyCompiler;
class C����ԭ��γ����App : public CWinAppEx
{
public:
	C����ԭ��γ����App();
private:
	CString curFileName;
public:
	TinyCompiler *TinyC;
	int curStep;

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	CString getFileName(){return curFileName;}
public:
	CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	CDocument* OpenDocumentFile(LPCTSTR lpszFileName,BOOL bAddToMRU);
public:
	void OnFileNew();
	void OnFileOpen();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C����ԭ��γ����App theApp;
