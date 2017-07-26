/************************************************************************/
/* 文件名：utili.cpp
 * 内容：
 *		1.每个产生式对应的语义规则
 *		2.建树所需要用的函数*/
/************************************************************************/
#include "stdafx.h"
#include "Whole.h"
#include "SymbolTab.h"
#include "TreeOperator.h"
TreeOperator *treeOp = new TreeOperator;
//////////////////////////////////////////////////////////////////////////
void rule0(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //Program(P) → stmt-sequence(S)         
void rule1(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //stmt-sequence(S) →stmt-sequence(S) ；statement(D) 
void rule2(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //stmt-sequence(S) →statement(D)
void rule3(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //statement(D) → if-stmt(I)
void rule4(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //statement(D) →  repeat-stmt(L)
void rule5(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //statement(D) →  assign-stmt(A) 
void rule6(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //statement(D) →  read-stmt(R) 
void rule7(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
} //statement(D) →  write-stmt(W)
void rule8(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mknode(allnptr[0],"if",allnptr[2].nptr,allnptr[4].nptr,NULL);
} //if-stmt(I) →if exp(E) then stmt-sequence(S) end 
void rule9(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mknode(allnptr[0],"if",allnptr[2].nptr,allnptr[4].nptr,allnptr[6].nptr );
} //if-stmt(I) →if exp(E) then stmt-sequence(S) else stmt-sequence(S) end
void rule10(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mknode(allnptr[0],"repeat",allnptr[2].nptr,allnptr[4].nptr,NULL );
}//repeat-stmt(L) → repeat stmt-sequence(S)  until exp(E)
void rule11(vector<Token> & allnptr){
	string s;
	s = allnptr[1].name;
	s += ":=";
	allnptr[0].nptr = treeOp->mknode(allnptr[0],s,allnptr[3].nptr,NULL,NULL );
}//assign-stmt(A) →identifier(id) := exp(E) 
void rule12(vector<Token> & allnptr){
	string s;
	s = allnptr[2].name;
	allnptr[0].nptr = treeOp->mknode(allnptr[0],"read " + s,NULL,NULL,NULL );
}//read-stmt(R)  → read  identifier(id)
void rule13(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mknode(allnptr[0],"write",allnptr[2].nptr,NULL,NULL );
}//write-stmt(W) → write  exp(E)
void rule14(vector<Token> & allnptr){
	(*allnptr[2].nptr).child[0] = allnptr[1].nptr;//左孩子
	(*allnptr[2].nptr).child[1] = allnptr[3].nptr;//右孩子
	allnptr[0].nptr = allnptr[2].nptr;
}//exp(E)→ simple-exp(U) comparison-op(O) simple-exp(U) 
void rule15(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
}//exp(E)→ simple-exp(U)
void rule16(vector<Token> & allnptr){
	(*allnptr[2].nptr).child[0] = allnptr[1].nptr;//左孩子
	(*allnptr[2].nptr).child[1] = allnptr[3].nptr;//右孩子
	allnptr[0].nptr = allnptr[2].nptr;
}//simple-exp(U) → simple-exp(U) addop(C) term(T)
void rule17(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
}//simple-exp(U) → term(T)
void rule18(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,0,'<',NULL,NULL );
}//comparison-op(O) →<
void rule19(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,0,'=',NULL,NULL );
}//comparison-op(O) →=
void rule20(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,1,'+',NULL,NULL );
}//addop(C)→+	
void rule21(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,1,'-',NULL,NULL );
}//addop(C)→-
void rule22(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,1,'*',NULL,NULL );
}//mulop(G)→*
void rule23(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_op_node(allnptr[0].lineNum,1,'/',NULL,NULL );
}//mulop(G)→/
void rule24(vector<Token> & allnptr){
	(*allnptr[2].nptr).child[0] = allnptr[1].nptr;//左孩子
	(*allnptr[2].nptr).child[1] = allnptr[3].nptr;//右孩子
	allnptr[0].nptr = allnptr[2].nptr;
}//term(T) → term(T) mulop(G) factor(F)
void rule25(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[1].nptr;
}//term(T) → factor(F)
void rule26(vector<Token> & allnptr){
	allnptr[0].nptr = allnptr[2].nptr;
}//factor(F) →( exp(E) )
void rule27(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_num_leaf(allnptr[1]);
}//factor(F) →number
void rule28(vector<Token> & allnptr){
	allnptr[0].nptr = treeOp->mk_id_leaf(allnptr[1]);
}//factor(F) →identifier(id)

