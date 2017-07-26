#include "stdafx.h"
#include "TokenScanner.h"
#include "SymbolTab.h"
#include "MainFrm.h"
//////////////////////////////////////////////////////////////////////////
TokenScanner::TokenScanner(SymbolTab *st)
{
	symTab = st;
	lineIndex = 0;
	lineNum = 0;
}
//////////////////////////////////////////////////////////////////////////
TokenScanner::~TokenScanner(void)
{
	closeFiles();
}
//////////////////////////////////////////////////////////////////////////
//传入源文件名，初始化词法扫描器
void TokenScanner::initialScanner(string filename)
{
	source_fileP.open(filename,ios::in);

	if (!source_fileP)
	{//找不到文件，自动退出.
		CString errorMes;
		errorMes.Format("%s",filename);
		errorMes+=" open error!";
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow(errorMes);
		pOut->FillBuildWindow("程序即将退出...");
		return ;
	}

	string listname;
	listname.assign(filename,0,filename.length()-4);
	listname += ".tkn";
	list_fileP.open(listname,ios::out);
}
//////////////////////////////////////////////////////////////////////////
//从文件里读取一行，存入输入缓冲区；从缓冲区内一个个取字符
int TokenScanner::getNextChar()
{
	//读取一行:char *fgets(char *s, int n, FILE *stream);
	
	if (lineIndex < inputBuffer.length())
	{//缓冲区内尚有剩余字符
		return inputBuffer[lineIndex++];
	} 
	else
	{
		if (source_fileP.eof())
		{
			return EOF;
		}
		else
		{
			getline(source_fileP,inputBuffer);
			lineIndex = 0;
			lineNum++;
			inputBuffer.insert(0,1,'\n');//插入换行符
			return getNextChar();
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//把多读的一个字符送回缓冲区
void TokenScanner::ungetNextChar()
{
	if (!source_fileP.eof() || (source_fileP.eof() && lineIndex < inputBuffer.length()))
	{//如果是文件结尾符，则不需要退回该符号
		lineIndex--;
	}
}
////////////////////////////////////////////////////////////////////////// 
//词法分析器，返回一个Token交给语法分析器
Token TokenScanner::getToken()
{
	MyTokenType cur_Token;
	int tokenStringIndex = 0;//标识符串的指示器
	DFA_StateType cur_state = START_state;//当前状态
	bool accept_tag;//标记是否接受该字符
	string word;//记录该Token的内容
	int ch;//从缓冲区读入的字符
	while (cur_state != DONE_state)
	{
		accept_tag = true;
		ch = getNextChar();//从缓冲区里获得一个字符
		switch (cur_state)
		{//根据DFA结合当前状态cur_state及转移条件ch确定下一状态
		case START_state://start状态共6个出口
			preIndex = lineIndex;
			if (isdigit(ch))
			{//ch为数字
				cur_state = INTEGER_state;
			}
			else
			{
				if (isalpha(ch))
				{//ch为字母
					cur_state = IDENT_state;
				} 
				else
				{
					if (ch == ':')
					{//ch为':'，则转入assign状态
						cur_state = ASSIGN_state;
					} 
					else
					{
						if (ch == '{')
						{//ch为'{',为注释
							cur_state = COMMENT_state;
							accept_tag = false;
						} 
						else
						{
							if (ch == ' ' || ch == '\n' || ch == '\t')
							{//ch为空格符，维持Start状态
								accept_tag = false;
							} 
							else
							{//ch为特殊符号，
								switch (ch)
								{
								case EOF://文件结束标志
									accept_tag = false;
									cur_Token = END_FILE;
									break;
								case '=':
									cur_Token = EQUAL;
									break;
								case '<':
									cur_Token = LITTLE;
									break;
								case '+':
									cur_Token = PLUS;
									break;
								case '-':
									cur_Token = MINUS;
									break;
								case '*':
									cur_Token = TIMES;
									break;
								case '/':
									cur_Token = DIVIDE;
									break;
								case '(':
									cur_Token = L_BRACKET;
									break;
								case ')':
									cur_Token = R_BRACKET;
									break;
								case ';':
									cur_Token = SEMICOLON;
									break;
								default:
									cur_Token = MY_ERROR;
									break;
								}
								cur_state = DONE_state;
							}
						}
					}
				}
			}
			break;
		case INTEGER_state:
			if (!isdigit(ch))
			{//识别结果为数
				cur_Token = NUM;
				cur_state = DONE_state;
				accept_tag = false;
				ungetNextChar();
			} 
			break;
		case IDENT_state:
			if (!isalpha(ch))
			{//识别结果为标识符
				cur_Token = ID;
				cur_state = DONE_state;
				accept_tag = false;
				ungetNextChar();
			}
			break;
		case ASSIGN_state:
			cur_state = DONE_state;
			if (ch == '=')
			{
				cur_Token = ASSIGN;
			}
			else
			{
				accept_tag = false;
				ungetNextChar();
			}
			break;
		case COMMENT_state:
			accept_tag = false;
			if (ch == '}')
			{
				cur_state = START_state;
			} 
			break;
		case DONE_state:
		default:
			cur_Token = MY_ERROR;
			cur_state = DONE_state;
			break;
		}
		if (accept_tag)
		{
			word += (char)ch;
		}
	}
	if (cur_Token == ID)
	{//识别该标识符是否为保留字
		cur_Token = isReservedWord(word);
	}
	Token tk;
	tk.name = word;
	tk.lineNum = lineNum;
	tk.ttype = cur_Token;
	symTab->insertTab(tk);//插入符号表
	outPutToken(tk);
	return tk;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*函数：editBuffer(char ch)
 *修改输入缓冲区，用于错误处理
 *功能：在inputBufffer的pos位置插入字符串s
*/
/************************************************************************/
void TokenScanner::editBuffer(char ch)
{
	inputBuffer.insert(preIndex - 1,1,ch);
	lineIndex = preIndex - 1;
}

////////////////////////////////////////////////////////////////////////// 
//查表，word是否为保留字，若是则返回其对应的枚举值，否则返回ID
MyTokenType TokenScanner::isReservedWord(string word)
{
	for (int i = 0; i < RESERVED_WORD_NUM; i++)
	{
		if (reservedWords[i].reservedS == word)
		{
			return reservedWords[i].tok;
		}
	}
	return ID;
}
//////////////////////////////////////////////////////////////////////////
//在屏幕上显示源文件的内容
void TokenScanner::showSourceCode()
{

}
//////////////////////////////////////////////////////////////////////////
//把Token输出到list文件中.
void TokenScanner::outPutToken(Token tk)
{
	//typedef struct Token
	//{//Token结点
	//	string name;//该Token的内容
	//	int lineNum;//该Token在源文件中的位于哪一行
	//	int entry;//在符号表内的地址
	//	MyTokenType ttype;//该Token的类型
	//	TreeNode * nptr;//符号的综合属性
	//}Token;
	list_fileP<<tk.lineNum<<":"<<tk.ttype<<":"<<tk.name<<endl;
}
void TokenScanner::closeFiles()
{
	if(source_fileP.is_open())
		source_fileP.close();
	if(list_fileP.is_open())
		list_fileP.close();
}
//////////////////////////////////////////////////////////////////////////

