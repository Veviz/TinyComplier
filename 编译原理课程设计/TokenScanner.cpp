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
//����Դ�ļ�������ʼ���ʷ�ɨ����
void TokenScanner::initialScanner(string filename)
{
	source_fileP.open(filename,ios::in);

	if (!source_fileP)
	{//�Ҳ����ļ����Զ��˳�.
		CString errorMes;
		errorMes.Format("%s",filename);
		errorMes+=" open error!";
		CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->GetMainWnd();
		COutputWnd *pOut=pFrame->getOutputWnd();
		pOut->FillBuildWindow(errorMes);
		pOut->FillBuildWindow("���򼴽��˳�...");
		return ;
	}

	string listname;
	listname.assign(filename,0,filename.length()-4);
	listname += ".tkn";
	list_fileP.open(listname,ios::out);
}
//////////////////////////////////////////////////////////////////////////
//���ļ����ȡһ�У��������뻺�������ӻ�������һ����ȡ�ַ�
int TokenScanner::getNextChar()
{
	//��ȡһ��:char *fgets(char *s, int n, FILE *stream);
	
	if (lineIndex < inputBuffer.length())
	{//������������ʣ���ַ�
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
			inputBuffer.insert(0,1,'\n');//���뻻�з�
			return getNextChar();
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//�Ѷ����һ���ַ��ͻػ�����
void TokenScanner::ungetNextChar()
{
	if (!source_fileP.eof() || (source_fileP.eof() && lineIndex < inputBuffer.length()))
	{//������ļ���β��������Ҫ�˻ظ÷���
		lineIndex--;
	}
}
////////////////////////////////////////////////////////////////////////// 
//�ʷ�������������һ��Token�����﷨������
Token TokenScanner::getToken()
{
	MyTokenType cur_Token;
	int tokenStringIndex = 0;//��ʶ������ָʾ��
	DFA_StateType cur_state = START_state;//��ǰ״̬
	bool accept_tag;//����Ƿ���ܸ��ַ�
	string word;//��¼��Token������
	int ch;//�ӻ�����������ַ�
	while (cur_state != DONE_state)
	{
		accept_tag = true;
		ch = getNextChar();//�ӻ���������һ���ַ�
		switch (cur_state)
		{//����DFA��ϵ�ǰ״̬cur_state��ת������chȷ����һ״̬
		case START_state://start״̬��6������
			preIndex = lineIndex;
			if (isdigit(ch))
			{//chΪ����
				cur_state = INTEGER_state;
			}
			else
			{
				if (isalpha(ch))
				{//chΪ��ĸ
					cur_state = IDENT_state;
				} 
				else
				{
					if (ch == ':')
					{//chΪ':'����ת��assign״̬
						cur_state = ASSIGN_state;
					} 
					else
					{
						if (ch == '{')
						{//chΪ'{',Ϊע��
							cur_state = COMMENT_state;
							accept_tag = false;
						} 
						else
						{
							if (ch == ' ' || ch == '\n' || ch == '\t')
							{//chΪ�ո����ά��Start״̬
								accept_tag = false;
							} 
							else
							{//chΪ������ţ�
								switch (ch)
								{
								case EOF://�ļ�������־
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
			{//ʶ����Ϊ��
				cur_Token = NUM;
				cur_state = DONE_state;
				accept_tag = false;
				ungetNextChar();
			} 
			break;
		case IDENT_state:
			if (!isalpha(ch))
			{//ʶ����Ϊ��ʶ��
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
	{//ʶ��ñ�ʶ���Ƿ�Ϊ������
		cur_Token = isReservedWord(word);
	}
	Token tk;
	tk.name = word;
	tk.lineNum = lineNum;
	tk.ttype = cur_Token;
	symTab->insertTab(tk);//������ű�
	outPutToken(tk);
	return tk;
}
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*������editBuffer(char ch)
 *�޸����뻺���������ڴ�����
 *���ܣ���inputBufffer��posλ�ò����ַ���s
*/
/************************************************************************/
void TokenScanner::editBuffer(char ch)
{
	inputBuffer.insert(preIndex - 1,1,ch);
	lineIndex = preIndex - 1;
}

////////////////////////////////////////////////////////////////////////// 
//���word�Ƿ�Ϊ�����֣������򷵻����Ӧ��ö��ֵ�����򷵻�ID
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
//����Ļ����ʾԴ�ļ�������
void TokenScanner::showSourceCode()
{

}
//////////////////////////////////////////////////////////////////////////
//��Token�����list�ļ���.
void TokenScanner::outPutToken(Token tk)
{
	//typedef struct Token
	//{//Token���
	//	string name;//��Token������
	//	int lineNum;//��Token��Դ�ļ��е�λ����һ��
	//	int entry;//�ڷ��ű��ڵĵ�ַ
	//	MyTokenType ttype;//��Token������
	//	TreeNode * nptr;//���ŵ��ۺ�����
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

