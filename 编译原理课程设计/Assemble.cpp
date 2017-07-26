/*
          ��assemble.h�ļ��еĺ������ж���
           
*/
#include "stdafx.h"

#include "assemble.h"
#include "MainFrm.h"
#include "ErrorHandler.h"

char tempzw[1000]={0};
char variablezw[100][10]={0}; //���������漰���ı���
//====================================================================
void createCodeNodezw(code &C)//����һ������ַ���������ͷ
{
	C=(code )malloc(sizeof(triAddrCodeNode));
	if(!C)
		exit(0);
	C->n=0;
	C->arg1[0]=C->arg2[0]=C->op[0]=C->result[0]=C->tag[0]=NULL;
	C->next=NULL;
}

//====================================================================
bool readFilezw()
{
	int i=0;
	fstream file;
	file.open("tri_addr_code.txt",ios::in);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("tri_addr_code.txt open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	while(!file.eof())
	{
		tempzw[i]=file.get();
		//cout<<temp[i];
		i++;
	}
	file.close();
	return true;
}
//====================================================================
void transStruzw(code &C)//������A�е�Ԫ�ش�������C
{
	code c1,c2;
	c1=C;
	int i=0;
	int k1,k2,k3,k4;
	int tag;
	while(tempzw[i]!=0)
	{
		tag=0;
		k1=k2=k3=k4=0;
		while(tempzw[i]!=10 && tempzw[i]!=0)
		{
			if(tempzw[i]==',' || tempzw[i]==' ')
				tag++;
			else 
			{
				switch(tag)
				{
				case 0:
				    c1->n=c1->n*10+((int)tempzw[i]-48);
					break;
				case 1:
				    c1->op[k1++]=tempzw[i];
					break;
				case 2:
				    c1->arg1[k2++]=tempzw[i];
					break;
				case 3:
				    c1->arg2[k3++]=tempzw[i];
					break;
				case 4:
				    c1->result[k4++]=tempzw[i];
					break;
				default:
				    exit(0);
				}
			}
			i++;
			if(tempzw[i]==10)
			{
				i++;
				break;
			}
		}
        c1->op[k1]=c1->arg1[k2]=c1->arg2[k3]=c1->result[k4]=0;
		if(tempzw[i]!=0)
		{
		    c2=(code )malloc(sizeof(triAddrCodeNode));
			c2->n=0;
			c2->arg1[0]=c2->arg2[0]=c2->op[0]=c2->result[0]=c2->tag[0]=NULL;
	        c2->next=NULL;
		    c1->next=c2;
		    c1=c2;
		}
	}
}
//====================================================================
bool isVariablezw(char *str)//�жϸ��ַ����ǲ��Ǳ���
{
	int i=0;
	if(str[0]=='#')
		return false;
	else if(str[0]=='T' && str[1]>='0' && str[1]<='9')
		return false;
	else
	{
		while(str[i]!=0)
		{
			if(str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z')
				return true;
			i++;
		}
	}
	return false;
}
//====================================================================
bool isSamezw(char *a,char *b,int n)//�ж������ַ����Ƿ���ȫ��ͬ
{
	int i;
	for(i=0;i<n;i++)
	{	
		if(a[i]!=b[i])
			return false;
	}
	return true;
}
//====================================================================
bool isExistzw(char *str)//�жϸñ����Ƿ��Ѿ��ڱ�������variable�г��ֹ�
{
	int i=0;
	while(variablezw[i][0]!=0)
	{
		if(isSamezw(variablezw[i],str,10))
			return true;
		i++;
	}
	return false;
}
//====================================================================
void getVariablezw(code C)//�������������е����б�����������������variable��
{
	code c;
	c=C;
	int i=0;
	while(c)
	{
		if(isVariablezw(c->arg1))
		{	
			if(!isExistzw(c->arg1))
				Copyzw(c->arg1,variablezw[i++],10);
		}
		if(isVariablezw(c->arg2))
		{
			if(!isExistzw(c->arg2))
			    Copyzw(c->arg2,variablezw[i++],10);
		}
		if(isVariablezw(c->result))
		{
			if(!isExistzw(c->result))
			    Copyzw(c->result,variablezw[i++],10);
		}
		c=c->next;
	}
}
//====================================================================
void displayzw(code C)//��ʾ����C�е�Ԫ�أ�����Ϊ������
{
	int k1,k2,k3,k4;
	code c;
	c=C;
	while(c)
	{
		k1=k2=k3=k4=0;
		cout<<c->n;
		cout<<" ";
		while(c->op[k1]!=0)
			cout<<c->op[k1++];
		cout<<",";
		while(c->arg1[k2]!=0)
			cout<<c->arg1[k2++];
		cout<<",";
		while(c->arg2[k3]!=0)
			cout<<c->arg2[k3++];
		cout<<",";
		while(c->result[k4]!=0)
			cout<<c->result[k4++];
		cout<<"\n";
		c=c->next;
	}
}

//====================================================================
bool initializezw(code C,CString fileName)//��ʼ��������
{
	int i;
	int count=4;
	fstream file;
	char temp[10]={0};
	getVariablezw(C);
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::out);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	file<<";*************************************************************"<<endl;
	file<<";Assemble Code \n";
	file<<";*************************************************************"<<endl;
	file<<".MODEL SMALL\n";
	file<<".DATA\n";
	i=0;
	while(variablezw[i][0]!=0)
	{
		file<<"\t"<<variablezw[i]<<"\tdw"<<"\t0\n";
		i++;
	}
	file<<"\tcount\tdw\t0\n";
	file<<".STACK\n";
	file<<".CODE\n";
	file<<".STARTUP\n";
	return true;
}
//====================================================================

//==========================================================================
//���濪ʼ������ָ��ת��Ϊ���ָ��
bool Readzw(code C,int &readNum,CString fileName)           //��Ӧ���ɴӼ��̶�ȡ���ݵĻ�����
{
	//cout<<"\nThere is the read code\n";
	code c;
	c=C;
	char again[10]={0};
	char next[10]={0};
	sprintf(again,"AGAIN%d",readNum);
	sprintf(next,"NEXT%d",readNum);
	readNum++;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH BX\n";
	file<<"           PUSH AX\n";
	file<<"           MOV BX,0\n";
	file<<again;
	file<<": MOV AH,1\n";
	file<<"           INT 21H\n";
	file<<"           CMP AL,13\n";
	file<<"           JZ ";
	file<<next<<"\n";
	file<<"           SUB AL,30H\n";
	file<<"           MOV AH,0\n";
	file<<"           PUSH AX\n";
	file<<"           MOV AX,10\n";
	file<<"           MUL BX\n";
	file<<"           MOV BX,AX\n";
	file<<"           POP AX\n";
	file<<"           ADD BX,AX\n";
	file<<"           JMP ";
	file<<again<<"\n";
	file<<"\n";
	file<<next;
	file<<": MOV "<<c->arg1<<",BX\n";
	file<<"           POP AX\n";
	file<<"           POP BX\n\n";
	file<<"\n";
	file<<"           MOV AH,2\n";
	file<<"           MOV DL,13\n";
    file<<"           INT 21H\n";
	file<<"           MOV AH,2\n";
	file<<"           MOV DL,10\n";
	file<<"           INT 21H\n";
	//file<<"\nThere is the read code\n\n";
	file.close();
	return true;
}
//====================================================================
bool Writezw(code C,int &writeNum,CString fileName)            //��Ӧ��������Ļ����Ļ�����
{
	//cout<<"\nThere is the write code\n";
	code c;
	c=C;
	char lp[10]={0};
	char print[10]={10};
	sprintf(lp,"LP%d",writeNum);
	sprintf(print,"PRINT%d",writeNum);
	writeNum++;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"\n";
	file<<"           MOV AH,2\n";
	file<<"           MOV DL,13\n";
    file<<"           INT 21H\n";
	file<<"           MOV AH,2\n";
	file<<"           MOV DL,10\n";
	file<<"           INT 21H\n";
	file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           MOV BX,10\n";
	file<<"  "<<lp;
	file<<": CWD\n";
	file<<"           DIV BX\n";
	file<<"           PUSH DX\n";
	file<<"           INC COUNT\n";
	file<<"           CMP AX,0\n";
	file<<"           JNE ";
	file<<lp<<"\n";
	file<<" "<<print;
	file<<": POP DX\n";
	file<<"           ADD DX,30H\n";
	file<<"           MOV AH,2\n";
	file<<"           INT 21H\n";
	file<<"           DEC COUNT\n";
	file<<"           JNE ";
	file<<print<<"\n";
	//file<<"\nThere is the write code\n\n";
	file.close();
	return true;
}
//====================================================================
bool Addzw(code C,CString fileName)            //��Ӧ���ɼӷ�ָ��Ļ�����
{
	//cout<<"\nThere is the add code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH AX\n";
	file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           ADD AX,"<<c->arg2<<"\n";
	file<<"           MOV "<<c->result<<",AX\n";
	file<<"           POP AX\n\n";
	file.close();
	return true;
}
//====================================================================
bool Subzw(code C,CString fileName)            //��Ӧ���ɼ���ָ��Ļ�����
{
	//cout<<"\nThere is the sub code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH AX\n";
	file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           SUB AX,"<<c->arg2<<"\n";
	file<<"           MOV "<<c->result<<",AX\n";
	file<<"           POP AX\n\n";
	file.close();
	return true;
}
//====================================================================
bool Mulzw(code C,CString fileName)           //��Ӧ���ɳ˷�ָ��Ļ�����
{
	//cout<<"\nThere is the mul code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH AX\n";
	file<<"           PUSH BX\n";
	file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           MOV BX,"<<c->arg2<<"\n";
	file<<"           MUL BX\n";
	file<<"           MOV "<<c->result<<",AX\n";
	file<<"           POP BX\n";
	file<<"           POP AX\n\n";
	file.close();
	return true;
}
//====================================================================
bool Divzw(code C,CString fileName)            //��Ӧ���ɳ���ָ��Ļ�����
{
	//cout<<"\nThere is the div code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH AX\n";
	file<<"           PUSH BX\n";
	file<<"           PUSH DX\n";
	file<<"           MOV DX,0\n";
	file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           MOV BX,"<<c->arg2<<"\n";
	file<<"           DIV BX\n";
	file<<"           MOV "<<c->result<<",AX\n";
	file<<"           POP DX\n";
	file<<"           POP BX\n";
	file<<"           POP AX\n\n";
	file.close();
	return true;
}
//====================================================================
bool Assignzw(code C,CString fileName)            //��Ӧ���ɸ�ֵָ��Ļ�����
{
	//cout<<"\nThere is the assign code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"           PUSH AX\n";
	if(c->arg1[0]=='#')
		file<<"           MOV AX,"<<c->arg2<<"\n";
	else
		file<<"           MOV AX,"<<c->arg1<<"\n";
	file<<"           MOV "<<c->result<<",AX\n";
	file<<"           POP AX\n\n";
	file.close();
	return true;

}
//====================================================================
bool Jmpzw(code C,CString fileName)            //��Ӧ������תָ��Ļ�����
{
	//cout<<"\nThere is the jmp code\n";
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	int op;
	op=matchzw(c->op);
	switch(op)
	{
	case 8: //j< 
		if(isVariablezw(c->arg1))//��һ���������Ǳ���
		{
			if(!isVariablezw(c->arg2))//��һ���������Ǳ������ڶ����������Ǿ�����ֵ
			{
		        file<<"           CMP "<<c->arg1<<","<<c->arg2<<"\n";
		        file<<"           JB "<<c->result<<"\n\n";
			}
			else                 //�������������Ǳ���
			{
				
	            file<<"           PUSH AX\n";
				file<<"           MOV AX,"<<c->arg1<<"\n";
				file<<"           CMP AX,"<<c->arg2<<"\n";
				file<<"           JB "<<c->result<<"\n\n";
				file<<"           POP AX\n";
			}
		}
		else                      
		{
			if(isVariablezw(c->arg2)) //�ڶ����������Ǳ�������һ���������Ǿ�����ֵ
			{
			    file<<"           CMP "<<c->arg2<<","<<c->arg1<<"\n";
		        file<<"           JA "<<c->result<<"\n\n";
			}
			else                    //�������������Ǿ�����ֵ����Ȼ��̫�����
			{
				
	            file<<"           PUSH AX\n";
				file<<"           MOV AX,"<<c->arg1<<"\n";
				file<<"           CMP AX,"<<c->arg2<<"\n";
				file<<"           JB "<<c->result<<"\n\n";
	            file<<"           POP AX\n";
			}
		}
		break;
	case 9:                 //j=
		if(isVariablezw(c->arg1))
		{
		    if(!isVariablezw(c->arg2))//��һ���������Ǳ������ڶ����������Ǿ�����ֵ
			{
		        file<<"           CMP "<<c->arg1<<","<<c->arg2<<"\n";
		        file<<"           JZ "<<c->result<<"\n\n";
			}
			else                 //�������������Ǳ���
			{
	            file<<"           PUSH AX\n";
				file<<"           MOV AX,"<<c->arg1<<"\n";
				file<<"           CMP AX,"<<c->arg2<<"\n";
				file<<"           JZ "<<c->result<<"\n\n";
	            file<<"           POP AX\n";
			}
		}
		else
		{
			if(isVariablezw(c->arg2))
			{
			    file<<"           CMP "<<c->arg2<<","<<c->arg1<<"\n";
		        file<<"           JZ "<<c->result<<"\n\n";
			}
			else                    //�������������Ǿ�����ֵ����Ȼ��̫�����
			{
	            file<<"           PUSH AX\n";
				file<<"           MOV AX,"<<c->arg1<<"\n";
				file<<"           CMP AX,"<<c->arg2<<"\n";
				file<<"           JZ "<<c->result<<"\n\n";
	            file<<"           POP AX\n";
			}
		}
		break;
	case 10:                //j
		file<<"           JMP "<<c->result<<"\n\n";

	}
	file.close();
	return true;
}
//====================================================================
bool Endzw(code C,CString fileName)//��ʾ��ຯ���Ѿ���������ʼ��assemble.asmд�������
{
	code c;
	c=C;
	fstream file;
	fileName=fileName.Left(fileName.GetLength()-4);
	fileName+=".asm";
	file.open(fileName,ios::app);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("assemble.asm open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return false;
	}
	if(c->tag[0]!=0)
		file<<c->tag<<":  ";
	file<<"\n.EXIT 0\n";
	file<<"          END";
	return true;
	//file<<"File ends\n";
}
//====================================================================
int matchzw(char *op)
{
	char temp[20]={0};
	int i;
	bool status;
	int result=0;
	fstream file;
	file.open("opration.txt",ios::in);
	if(file.fail())
	{
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow("opration.txt open error!");
		pOut->FillBuildWindow("���򼴽��˳�...");
		return -1;
	}
	while(!file.eof())
	{
		i=0;
		status=true;
		file.getline(temp,sizeof(temp));
		while(op[i]!=0)
		{
			if(op[i]!=temp[i])
			{	
				status=false;
				break;
			}
			i++;
		}
		if(status && temp[i]==' ')
		{
			while(temp[i]==' ')
				i++;
			while(temp[i]!=0)
			{	
				result=result*10+(int)temp[i]-48;
				i++;
			}
			return result;
		}
	}
	return -1;
}
//====================================================================
void Copyzw(char *a,char *b,int n)//����һ��������������a������Ԫ��ȫ����ֵ��b����
{
	int i;
	for(i=0;i<n;i++)
		b[i]=a[i];
}
//====================================================================
void addTagzw(code &C)         //���ӱ�ǩ��Ϊ��ת������
{
	code c1,c2;
	c1=C;
	char temp[10]={0};
	int location,i;
	int number=1;
	while(c1)
	{
		if(c1->op[0]=='j')
		{
			location=i=0;
			Copyzw(c1->result,temp,10);
			while(temp[i]!=0)
				location=location*10+(int)temp[i++]-48;
			c2=C;
			while(c2)
			{
				if(c2->n==location)
				{
					if(c2->tag[0]==0)
					{   
						sprintf(c2->tag,"T%d",number);
					    Copyzw(c2->tag,c1->result,10);
					    number++;
					    break;
					}
					else
					{
						Copyzw(c2->tag,c1->result,10);
					}
				}
				c2=c2->next;
			}
		}
		c1=c1->next;
	}
}
//====================================================================
bool analysiszw(code C,int &readNum,int &writeNum,CString fileName)       //��дһ��ת��������������ͨ���ú����ֱ��������ļ���������ʵ�ֶԸ���ָ���ת��
{
	code c;
	c=C;
	int opration;
	bool analysisSign=true;
	while(c&&analysisSign)
	{
		opration=matchzw(c->op);
		switch(opration)
		{
		case 1:
			analysisSign=Readzw(c,readNum,fileName);
			break;
		case 2:
			analysisSign=Writezw(c,writeNum,fileName);
			break;
		case 3:
			analysisSign=Addzw(c,fileName);
			break;
		case 4:
			analysisSign=Subzw(c,fileName);
			break;
		case 5:
			analysisSign=Mulzw(c,fileName);
			break;
		case 6:
			analysisSign=Divzw(c,fileName);
			break;
		case 7:
			analysisSign=Assignzw(c,fileName);
			break;
		case 8:
		case 9:
		case 10:
			analysisSign=Jmpzw(c,fileName);
			break;
		case 11:
			analysisSign=Endzw(c,fileName);
			break;
		default:
			CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
			COutputWnd *pOut=pFrame->getOutputWnd();
			pOut->FillBuildWindow("The opration is illegal!");
			pOut->FillBuildWindow("���򼴽��˳�...");
			return false;
		}
		c=c->next;
	}
	return true;
}
//====================================================================
bool transzw(CString fileName)
{
	
    int readNum=1;
    int writeNum=1;
	code C;//����ṹ�������ͷ
	ErrorHandler errorHandler;
	errorHandler.showMessage("�����������ɻ��...");
	errorHandler.showMessage("���ڳ�ʼ���������...");
	createCodeNodezw(C);
	errorHandler.showMessage("���ڶ�ȡ�ļ�...");
	if(!readFilezw())//���ļ��н�����ַ���������
		return false;
	errorHandler.showMessage("��ȡ���...");
	errorHandler.showMessage("���ڽ��нṹת��...");
	transStruzw(C);//��������������ַ����洢�ڽṹ��������
	//displayzw(C);//��������
	addTagzw(C);//���������ɵĻ����������ת��ǩ
	if(!initializezw(C,fileName))//��ʼ��������
	{
		errorHandler.showMessage("��ʼ��ʧ��...");
		errorHandler.showMessage("TinyComplier��ֹͣ����...");
		return false;
	}
	errorHandler.showMessage("��ʼ�����...");
	errorHandler.showMessage("��������ת��...");
	if(!analysiszw(C,readNum,writeNum,fileName))//��ʼ��������ַ���룬�����䷭��Ϊ���
	{
		errorHandler.showMessage("ת��ʧ��...");
		errorHandler.showMessage("TinyComplier��ֹͣ����...");
		return false;
	}
	errorHandler.showMessage("ת���ɹ�...");
	errorHandler.showMessage("������������...");
	return true;
}

//====================================================================