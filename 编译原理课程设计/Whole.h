//File: Whole.h
// Global types and vars for TINY compiler
#pragma  once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
/************************************************************************/
/* 下面是词法分析所用到的一些数据结构的定义
 * */
/************************************************************************/
#define RESERVED_WORD_NUM 8//保留字的个数
#define MAX_CHILDREN_NUM 3//树节点最大的孩子个数
#define SYMBOL_SIZE 256//符号表的大小
//////////////////////////////////////////////////////////////////////////
//定义DFA每个结点，共6个状态
typedef enum DFA_StateType
{
	START_state,INTEGER_state,IDENT_state,ASSIGN_state,COMMENT_state,DONE_state
};
//////////////////////////////////////////////////////////////////////////
typedef enum MyTokenType
{//Token的类型
	IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,//8个保留字
	PLUS,MINUS,TIMES,DIVIDE,EQUAL,LITTLE,L_BRACKET,R_BRACKET,SEMICOLON,ASSIGN,//10种特殊符号
	ID,NUM,//数或标识符，为字符串
	END_FILE,//文件结束符
	programC,stmt_sequenceC,statementC,if_stmtC,repeat_stmtC,assign_stmtC,read_stmtC,write_stmtC,expC,simple_expC,comparison_opC,addopC,mulopC,termC,factorC,//非终结符
	MY_ERROR
};
//////////////////////////////////////////////////////////////////////////
//保留字
static struct RWORD
{
	string reservedS;
	MyTokenType tok;
}reservedWords[RESERVED_WORD_NUM] = {{"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
{"repeat",REPEAT},{"until",UNTIL},{"read",READ},
{"write",WRITE}};
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 符号表的数据结构定义
 * */
/************************************************************************/
typedef struct SymbolTerm
{
	string name;
	int memloc;//内存地址
	vector<int> LineList;//记录同一ID在不同行出现时的行数
	struct SymbolTerm *next;
}*symbolTerm;
/************************************************************************/
/* 下面是语法分析所用到的一些数据结构的定义
 * */
/************************************************************************/
#define STATE_NUM 47//分析表中的状态数，即行数
#define CHAR_NUM 36//分析表中的字符数，即列数,不包括M和N以及#,$
#define PRODUCER_NUM 29//产生式的个数,不包括M和N
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 定义语法树                                                           */
/************************************************************************/
typedef enum {StmtK,ExpK} NodeKind;//结点类型，句子或是表达式
//typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;//5种句子
//typedef enum {OpK,ConstK,IdK} ExpKind;//3种表达式
typedef enum {Void,Integer,Boolean} ExpType;//表达式的类型
typedef struct listNode
{
	int num;
	listNode * nextNode;
}List; // 链表结点
//////////////////////////////////////////////////////////////////////////
typedef struct treeNode
{//语法树节点定义
	struct treeNode * child[MAX_CHILDREN_NUM];//孩子
	struct treeNode * sibling;//兄弟
	int lineNUM;//所在行号，用于出错时打印源代码行数
	/************************************************************************/
	/*语义分析用到的属性                                                    */
	/************************************************************************/
	char op;
	int val;
	string name;
	NodeKind nodeKind;//结点类型
	MyTokenType reservedType;//保留字类型
	ExpType type; //用于后续表达式的类型检查
	/************************************************************************/
	/* 翻译用到的属性
	 * */
	/************************************************************************/
	MyTokenType tokentype;
	List * truelist;
	List * falselist;
	List * Snextlist;
	List * Nnextlist;
	int quad[2];
}TreeNode;
//////////////////////////////////////////////////////////////////////////
typedef struct Token
{//Token结点
	string name;//该Token的内容
	int lineNum;//该Token在源文件中的位于哪一行
	int entry;//在符号表内的地址
	MyTokenType ttype;//该Token的类型
	TreeNode * nptr;//符号的综合属性
}Token;
//////////////////////////////////////////////////////////////////////////
extern TreeNode * syntaxTree;//语法分析树根节点指针
extern vector<TreeNode*> treeStack;//保存树节点的栈
/************************************************************************/
/*LR(0)分析表										
 *当值为a时，若a小于零为移进且下一状态为-a，否则为按第a个产生式归约		*/
/************************************************************************/
#define SEMI_DEL 47//当多一个分号时的错误处理子程序入口
#define ADD_BRACKET 48//当缺少右括号时的错误处理子程序入口
#define DEL_BRACKET 49//当多出右括号时的错误处理子程序入口
const int analyTable[STATE_NUM][CHAR_NUM] = {//
	-9,0,0,0,-10,0,-10,-11,0,0,0,0,0,0,0,0,0,0,-9,0,0,1,2,3,4,5,6,7,8,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-12,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,3,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,4,4,0,4,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,5,5,0,5,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,6,6,0,6,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,7,7,0,7,0,0,0,0,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,8,8,0,8,0,0,0,0,0,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,-19,-17,-20,0,0,0,0,0,0,0,0,0,13,14,0,0,0,15,16,
	-22,0,0,0,-10,0,-10,-11,0,0,0,0,0,0,0,0,0,0,-22,0,0,0,21,3,4,5,6,7,8,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,23,14,0,0,0,15,16,
	-9, 0, SEMI_DEL, SEMI_DEL, -10, SEMI_DEL, -10, -11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9, 0, SEMI_DEL, 0, 0, 24, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0,
	0, -25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEL_BRACKET, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,16,16,16,0,16,0,0,-28,-29,0,0,-30,-31,0,16,16,0,0,0,16,0,0,0,0,0,0,0,0,0,0,26,27,0,0,0,
	0,18,18,18,0,18,0,0,18,18,-33,-34,18,18,0,18,18,0,0,0,18,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,
	0,26,26,26,0,26,0,0,26,26,26,26,26,26,0,26,26,0,0,0,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,29,29,29,0,29,0,0,29,29,29,29,29,29,0,29,29,0,0,0,29,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,35,14,0,0,0,15,16,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,36,14,0,0,0,15,16,
	0,28,28,28,0,28,0,0,28,28,28,28,28,28,0,28,28,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,-37,0,0,0,0,0,0,0,0,0,0,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,13,13,0,13,0,0,0,0,0,0,0,0,-18,0,13,-19,-17,-20,13,0,0,0,0,0,0,0,0,13,14,0,0,0,15,16,
	0, 0, 14, 14, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEL_BRACKET, 14, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,0,2,2,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	-9,0,0,0,-10,0,-10,-11,0,0,0,0,0,0,0,0,0,0,-9,0,0,0,38,3,4,5,6,7,8,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,0,39,0,0,0,15,16,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,16,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,21,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,22,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,20,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,0,0,0,23,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,24,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, -42, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, ADD_BRACKET, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 12, 12, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEL_BRACKET, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,-18,0,0,0,-17,-20,0,0,0,0,0,0,0,0,0,43,14,0,0,0,15,16,
	0,0,-44,-44,0,0,0,0,0,0,0,0,0,0,0,0,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,15,15,15,0,15,0,0,-28,-29,0,0,0,0,0,15,15,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,27,0,0,0,
	0,17,17,17,0,17,0,0,17,17,-33,-34,17,17,0,17,17,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,
	0,25,25,25,0,25,0,0,25,25,25,25,25,25,0,25,25,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,27,27,27,0,27,0,0,27,27,27,27,27,27,0,27,27,0,0,0,27,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0, 0, 11, 11, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEL_BRACKET, 11, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	-9,0,9,9,-10,9,-10,-11,0,0,0,0,0,0,0,0,9,0,-9,0,9,0,45,3,4,5,6,7,8,0,0,0,0,0,0,0,
	0,0,0,-46,0,0,0,0,0,0,0,0,0,0,0,0,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,10,10,0,10,0,0,0,0,0,0,0,0,0,0,10,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};//直接初始化
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 语义规则函数声明
 * 用于建立AST*/
/************************************************************************/
void rule0(vector<Token> & allnptr);
void rule1(vector<Token> & allnptr);
void rule2(vector<Token> & allnptr);
void rule3(vector<Token> & allnptr);
void rule4(vector<Token> & allnptr);
void rule5(vector<Token> & allnptr);
void rule6(vector<Token> & allnptr);
void rule7(vector<Token> & allnptr);
void rule8(vector<Token> & allnptr);
void rule9(vector<Token> & allnptr);
void rule10(vector<Token> & allnptr);
void rule11(vector<Token> & allnptr);
void rule12(vector<Token> & allnptr);
void rule13(vector<Token> & allnptr);
void rule14(vector<Token> & allnptr);
void rule15(vector<Token> & allnptr);
void rule16(vector<Token> & allnptr);
void rule17(vector<Token> & allnptr);
void rule18(vector<Token> & allnptr);
void rule19(vector<Token> & allnptr);
void rule20(vector<Token> & allnptr);
void rule21(vector<Token> & allnptr);
void rule22(vector<Token> & allnptr);
void rule23(vector<Token> & allnptr);
void rule24(vector<Token> & allnptr);
void rule25(vector<Token> & allnptr);
void rule26(vector<Token> & allnptr);
void rule27(vector<Token> & allnptr);
void rule28(vector<Token> & allnptr);
/************************************************************************/
/* 4个产生树节点的函数声明
 * */
/************************************************************************/
//TreeNode * mknode(string s,TreeNode* firstChild,TreeNode* secondChild,TreeNode* thirdChild);
//TreeNode * mk_op_node(char op,TreeNode* leftChild,TreeNode* rightChild);
//TreeNode * mk_id_leaf(Token tk);
//TreeNode * mk_num_leaf(Token tk);
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*产生式表                                                              */
/************************************************************************/
static struct Producer
{
	MyTokenType lChar;//产生式左边的字符
	int rightLength;//产生式右侧句型的长度
	vector<Token> sematicRule(int num,vector<Token> allnptr)
	{
		switch (num)
		{
		case 0: rule0(allnptr );
			break;
		case 1: rule1(allnptr );
			break;
		case 2: rule2(allnptr );
			break;
		case 3: rule3(allnptr );
			break;
		case 4: rule4(allnptr );
			break;
		case 5: rule5(allnptr );
			break;
		case 6: rule6(allnptr );
			break;
		case 7: rule7(allnptr );
			break;
		case 8: rule8(allnptr );
			break;
		case 9: rule9(allnptr );
			break;
		case 10: rule10(allnptr );
			break;
		case 11: rule11(allnptr );
			break;
		case 12: rule12(allnptr );
			break;
		case 13: rule13(allnptr );
			break;
		case 14: rule14(allnptr );
			break;
		case 15: rule15(allnptr );
			break;
		case 16: rule16(allnptr );
			break;
		case 17: rule17(allnptr );
			break;
		case 18: rule18(allnptr );
			break;
		case 19: rule19(allnptr );
			break;
		case 20: rule20(allnptr );
			break;
		case 21: rule21(allnptr );
			break;
		case 22: rule22(allnptr );
			break;
		case 23: rule23(allnptr );
			break;
		case 24: rule24(allnptr );
			break;
		case 25: rule25(allnptr );
			break;
		case 26: rule26(allnptr );
			break;
		case 27: rule27(allnptr );
			break;
		case 28: rule28(allnptr );
			break;
		default://出错处理
			break;
		}

		return allnptr;
	}
}producerTable[PRODUCER_NUM] = {
	{programC,1},//		0.Program(P) → stmt-sequence(S)         
	{stmt_sequenceC,3},//	1.stmt-sequence(S) →stmt-sequence(S) ；statement(D) 
	{stmt_sequenceC,1},//	2.stmt-sequence(S) →statement(D)
	{statementC,1},//		3.statement(D) → if-stmt(I)
	{statementC,1},//		4.statement(D) →  repeat-stmt(L)
	{statementC,1},//		5.statement(D) →  assign-stmt(A) 
	{statementC,1},//		6.statement(D) →  read-stmt(R) 
	{statementC,1},//		7.statement(D) →  write-stmt(W)
	{if_stmtC,5},//		8.if-stmt(I) →if exp(E) then stmt-sequence(S) end 
	{if_stmtC,7},//		9.if-stmt(I) →if exp(E) then stmt-sequence(S) else stmt-sequence(S) end
	{repeat_stmtC,4},//	10.repeat-stmt(L) → repeat stmt-sequence(S)  until exp(E)
	{assign_stmtC,3},//	11.assign-stmt(A) →identifier(id) := exp(E) 
	{read_stmtC,2},//		12.read-stmt(R)  → read  identifier(id)
	{write_stmtC,2},//		13.write-stmt(W) → write  exp(E)
	{expC,3},//    		14.exp(E)→ simple-exp(U) comparison-op(O) simple-exp(U) 
	{expC,1},//				15.exp(E)→ simple-exp(U)
	{simple_expC,3},//		16.simple-exp(U) → simple-exp(U) addop(C) term(T)
	{simple_expC,1},//		17.simple-exp(U) → term(T)
	{comparison_opC,1},//	18.comparison-op(O) →<
	{comparison_opC,1},//	19.comparison-op(O) →=
	{addopC,1},//			20.addop(C)→+	
	{addopC,1},//			21.addop(C)→-
	{mulopC,1},//			22.mulop(G)→*
	{mulopC,1},//			23.mulop(G)→/
	{termC,3},//			24.term(T) → term(T) mulop(G) factor(F)
	{termC,1},//			25.term(T) → factor(F)
	{factorC,3},//			26.factor(F) →( exp(E) )
	{factorC,1},//			27.factor(F) →number
	{factorC,1}// 			28.factor(F) →identifier(id)
};//直接初始化			   
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 语义分析阶段需要用到的数据结构
 * */
/************************************************************************/
typedef struct qtrNode
{
	int num;
	string op;
	string arg1;
	string arg2;
	string result;
	qtrNode * nextNode;
}Qtr;//四元式链表
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////