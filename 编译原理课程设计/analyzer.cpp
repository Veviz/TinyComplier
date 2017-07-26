#include"stdafx.h"
#include"analyzer.h"
#include"ErrorHandler.h"

void Analyzer::getchar(fstream & file)
{
	ch=file.get();
}
bool Analyzer::getbc(fstream & file,int & rownum)
{
	//跳过空白字符（空格，回车和tab键）
	while((ch==' '||ch=='\n'||ch=='\t')&&(!file.eof()))
	{
		if(ch=='\n')
			rownum++;
		ch=file.get();
	}
	//若读到文件结尾则返回false
	if((ch!=' '||ch!='\n'||ch!='\t')&&(!file.eof()))
		return true;
	else
		return false;
}
bool Analyzer::isletter()
{
	bool sign;
	if(('A'<=ch&&ch<='Z')||('a'<=ch&&ch<='z'))
		sign=true;
	else
		sign=false;
	return sign;
}
bool Analyzer::isdigit()
{
	bool sign;
	if('0'<=ch&&ch<='9')
		sign=true;
	else
		sign=false;
	return sign;
}
int Analyzer::reserve()
{
	int i;
	for(i=1;i<9;i++)
		if(strcmp(reserveword[i],strToken)==0)
			break;
	if(i<9)
		return i;
	else
		return 0;
}
void Analyzer::retract(fstream & file)
{
	file.seekg(-1,ios::cur);
}
void Analyzer::insertId(char * strToken,int rownum)
{
	int i=0;
	while(strcmp(symboltable[i],"")!=0)
		i++;
	strcmp(symboltable[i],strToken);
	symbolrow[i]=rownum;
}
void Analyzer::insertConst(char * strToken,int rownum)
{
	int i=0,j=0;
	int sum=0;
	while(constrow[i]!=0)
		i++;
	while(strToken[j]!='\0')
	{
		sum=10*sum;
		sum=sum+(strToken[j]-'0');
		j++;
	}
	consttable[i]=sum;
	constrow[i]=rownum;
}
bool Analyzer::analyze()
{
	bool AnalyzeSign=true;//显示分析过程工作状态，真时工作正常，否则工作失败
	ErrorHandler cerror;
	string message;
	CString outputName;
	int rownum=1;
	int curnum;
	int i;
	int istart;
	fstream file,ofile;
	int code;
	file.open(fileName,ios::in);
	outputName=fileName.Left(fileName.GetLength()-4);
	outputName+=".tkn";
	ofile.open(outputName,ios::out);
	cerror.showMessage("词法分析已启动...");
	while(!file.eof())
	{
		getchar(file);
		if(!getbc(file,rownum))
			break;
		if(isletter())
		{
			curnum=0;
			while(isletter()||isdigit())
			{
				strToken[curnum]=ch;
				getchar(file);
				curnum++;
			}
			strToken[curnum]='\0';
			retract(file);
			code=reserve();
			if(code==0)
			{//是标识符或者在标识符中出现数字
				i=0;
				//出现错误则提示错误信息
				while(strToken[i]!='\0')
				{
					if(strToken[i]<='9'&&strToken[i]>='0')
					{
						message="标识符中不应有数字出现。";
						cerror.printError(rownum,message);
						AnalyzeSign=false;
					}
					i++;
				}
				if(i>=strlen(strToken))
				{
					insertId(strToken,rownum);
					ofile<<rownum<<":ID,name="<<strToken<<endl;
				}
			}
			else
			{
				ofile<<rownum<<":reserved word:"<<strToken<<endl;
			}
		}
		else
		{
			if(isdigit())
			{
				curnum=0;
				while(isdigit())
				{
					strToken[curnum]=ch;
					getchar(file);
					curnum++;
				}
				strToken[curnum]='\0';
				retract(file);
				insertConst(strToken,rownum);
				ofile<<rownum<<":integer:"<<strToken<<endl;
			}
			else
			{
				if(ch=='='||ch=='+'||ch=='*'||ch=='/'||ch=='-'||ch==';'||ch=='('||ch==')')
				{
					ofile<<rownum<<":symbol:"<<ch<<endl;
				}
				else
				{
					if(ch=='<')
					{
						ofile<<rownum<<":symbol:<"<<endl;
					}
					else
					{
						if(ch=='{')
							while(!file.eof()&&ch!='}')
							{
								getchar(file);
								if(ch=='\n')
									rownum++;
							}
						else
						{
							if(ch==':')
							{
								getchar(file);
								if(ch=='=')
								{
									ofile<<rownum<<":symbol::="<<endl;
								}
								else
								{
									message="出现未识别的字符";
									cerror.printError(rownum,message);
									AnalyzeSign=false;
								}
							}
							else
							{
								message="出现未识别的字符";
								cerror.printError(rownum,message);
								AnalyzeSign=false;
							}
						}
					}
				}
			}
		}
	}
	file.close();
	ofile.close();
	if(AnalyzeSign)
	{
		cerror.showMessage("词法分析成功...");
	}else{
		cerror.showMessage("词法分析失败...");
		cerror.showMessage("TinyComplier已终止...");
	}
	return AnalyzeSign;
}