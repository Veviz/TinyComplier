#pragma once
/************************************************************************/
/*������ErrorHandler
 *���ܣ���¼�����Լ���ӡ������Ϣ
*/
/************************************************************************/
#include "Whole.h"

class C����ԭ��γ����Doc;
class ErrorHandler
{
	int firstError;//����Ƿ��ǵ�һ������
	int errorCount;
public:
	ErrorHandler(void);
	~ErrorHandler(void);
	void printError(int lineno,string s);
	/*
	*void showMessage(CString S);
	*���ߣ�DHY
	*���ܣ���ʾ������̵ĸ����׶ε���Ϣ
	*/
	void showMessage(CString S);
};

