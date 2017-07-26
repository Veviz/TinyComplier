#pragma once
/************************************************************************/
/*�ʷ�����
 *���룺Դ�ļ�
 *�����Token��
 * ��δ��ɣ�
 1.showSourceCode()*/
/************************************************************************/
#include "Whole.h"
//////////////////////////////////////////////////////////////////////////
class SymbolTab;
class TokenScanner
{
	string inputBuffer;//���뻺����
	int lineIndex;//���ӵ�ָʾ��
	int preIndex;//ǰһ��Token����ʼλ�ã����ڳ����﷨����ʱ���в���������Ӷ��ָ��﷨����
	int lineNum;//��¼�к�
	fstream source_fileP;//Դ�����ļ�ָ��
	fstream list_fileP;//�ʷ�������������
	SymbolTab *symTab;//���ű�
public:
	TokenScanner(SymbolTab *st);
	~TokenScanner(void);
	void initialScanner(string filename);
	void showSourceCode();//����Ļ����ʾԴ�ļ�������
	void closeFiles();

	Token getToken();//ɨ������������
	int getNextChar();//���ļ����ȡһ�У��������뻺�������ӻ�������һ����ȡ�ַ�
	void ungetNextChar();//�Ѷ����һ���ַ��ͻػ�����
	void insertToken();//��ʶ�������Token����Token����
	MyTokenType isReservedWord(string word);//���word�Ƿ�Ϊ�����֣������򷵻����Ӧ��ö��ֵ�����򷵻�ID
	void outPutToken(Token tk);//��Token�����list�ļ���.
	void editBuffer(char ch);//�޸����뻺���������ڴ�����
};
//////////////////////////////////////////////////////////////////////////
