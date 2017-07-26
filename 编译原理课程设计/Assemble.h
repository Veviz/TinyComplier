#pragma   once
#ifndef _ASSEMBLE_H
#define _ASSEMBLE_H

/*
     ���ļ���Ϊ�˽��ļ��ж�ȡ������ַ����ת��Ϊ������
*/

#include "Head.h"
//===============================================================================================
typedef struct triAddrCodeNode
{
	int n;                     //����ַ�ã���¼�û��ָ�����ڵĵ�ַ
	char op[10];                //������
	char arg1[10];              //������1
	char arg2[10];              //������2
	char result[10];            //�������
	char tag[5];
	triAddrCodeNode *next;       //ָ����һ���ڵ�
}triAddrCodeNode , * code;



//================================================================================================
void createCodeNodezw(code &C);//����һ������ַ���������ͷ
void Copyzw(char *a,char *b,int n);//����һ��������������a������Ԫ��ȫ����ֵ��b����
bool readFilezw();//���ļ��ж�ȡ����ַ����,�����������A��
void transStruzw(code &C);//������A�е�Ԫ�ش�������C
bool isVariablezw(char *str);//�жϸ��ַ����ǲ��Ǳ���
bool isExistzw(char *str);//�жϸñ����Ƿ��Ѿ��ڱ�������variable�г��ֹ�
bool isSamezw(char *a,char *b,int n);//�ж������ַ����Ƿ���ȫ��ͬ
void getVariablezw(code C);   //�������������е����б�����������������variable��
void displayzw(code C);//��������
bool initializezw(code C,CString fileName);//��ʼ��������


//����ĸ��������ֱ��Ӧ�ڰ˸�������(read��write��+��-��*��/��:=����תָ�������ת��ֱ����ת��)��Ӧ�Ĳ���
int matchzw(char *op);            //������ַ����Ĳ���ָ��������������жԱȣ��ҳ��ò�����Ӧ�ı��
bool Readzw(code C,int &readNum,CString fileName);            //��Ӧ���ɴӼ��̶�ȡ���ݵĻ�����
bool Writezw(code C,int &writeNum,CString fileName);            //��Ӧ��������Ļ����Ļ�����
bool Addzw(code C,CString fileName);            //��Ӧ���ɼӷ�ָ��Ļ�����
bool Subzw(code C,CString fileName);            //��Ӧ���ɼ���ָ��Ļ�����
bool Mulzw(code C,CString fileName);            //��Ӧ���ɳ˷�ָ��Ļ�����
bool Divzw(code C,CString fileName);            //��Ӧ���ɳ���ָ��Ļ�����
bool Assignzw(code C,CString fileName);            //��Ӧ���ɸ�ֵָ��Ļ�����
bool Jmpzw(code C,CString fileName);            //��Ӧ������תָ��Ļ�����
bool Endzw(code C,CString fileName);                 //��Ӧ����ָ��
void addTagzw(code &C);         //���ӱ�ǩ��Ϊ��ת������
bool analysiszw(code C,int &readNum,int &writeNum,CString fileName);       //��дһ��ת��������������ͨ���ú����ֱ��������ļ���������ʵ�ֶԸ���ָ���ת��

bool transzw(CString fileName);
#endif