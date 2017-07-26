#include<iostream>
using namespace std;
#include<string.h>
#include<fstream>
#include"Whole.h"
class Analyzer
{
private:
	char ch;
	char strToken[81];
	char reserveword[9][10];//保留字表
	char symboltable[81][10];//符号表
	int consttable[81];//常数表
	int symbolrow[81];
	int constrow[81];
	CString fileName;
protected:
	void getchar(fstream & file);
	bool getbc(fstream & file,int & rownum);
	bool isletter();
	bool isdigit();
	int reserve();
	void retract(fstream & file);
	void insertId(char * strToken,int rownum);
	void insertConst(char * strToken,int rownum);
public:
	void setFileName(CString fileName){this->fileName=fileName;}
public:
	Analyzer()
	{
		int i;
		ch='\0';
		for(i=0;i<81;i++)
			strToken[i]=0;
		strcpy(reserveword[0],"");
		strcpy(reserveword[1],"if");
		strcpy(reserveword[2],"then");
		strcpy(reserveword[3],"else");
		strcpy(reserveword[4],"end");
		strcpy(reserveword[5],"repeat");
		strcpy(reserveword[6],"until");
		strcpy(reserveword[7],"read");
		strcpy(reserveword[8],"write");
		for(i=0;i<81;i++)
		{
			symbolrow[i]=0;
			constrow[i]=0;
			strcpy(symboltable[i],"");
			consttable[i]=0;
		}
	}
	bool analyze(); 
	//Token getToken();
};