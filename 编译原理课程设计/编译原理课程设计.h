
// 编译原理课程设计.h : 编译原理课程设计 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "Whole.h"


// C编译原理课程设计App:
// 有关此类的实现，请参阅 编译原理课程设计.cpp
//
class TinyCompiler;
class C编译原理课程设计App : public CWinAppEx
{
public:
	C编译原理课程设计App();
private:
	CString curFileName;
public:
	TinyCompiler *TinyC;
	int curStep;

// 重写
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

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C编译原理课程设计App theApp;
