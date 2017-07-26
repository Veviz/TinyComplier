#pragma once
/************************************************************************/
/*类名：ErrorHandler
 *功能：记录错误，以及打印错误消息
*/
/************************************************************************/
#include "Whole.h"

class C编译原理课程设计Doc;
class ErrorHandler
{
	int firstError;//标记是否是第一个错误
	int errorCount;
public:
	ErrorHandler(void);
	~ErrorHandler(void);
	void printError(int lineno,string s);
	/*
	*void showMessage(CString S);
	*作者：DHY
	*功能：显示编译过程的各个阶段的信息
	*/
	void showMessage(CString S);
};

