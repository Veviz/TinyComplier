#pragma   once
#ifndef _ASSEMBLE_H
#define _ASSEMBLE_H

/*
     本文件是为了将文件中读取的三地址代码转换为汇编代码
*/

#include "Head.h"
//===============================================================================================
typedef struct triAddrCodeNode
{
	int n;                     //做地址用，记录该汇编指令所在的地址
	char op[10];                //操作符
	char arg1[10];              //操作数1
	char arg2[10];              //操作数2
	char result[10];            //操作结果
	char tag[5];
	triAddrCodeNode *next;       //指向下一个节点
}triAddrCodeNode , * code;



//================================================================================================
void createCodeNodezw(code &C);//创建一个三地址代码链表的头
void Copyzw(char *a,char *b,int n);//定义一个拷贝函数，将a数组中元素全部赋值给b数组
bool readFilezw();//从文件中读取三地址代码,并存放在数组A中
void transStruzw(code &C);//将数组A中的元素传给链表C
bool isVariablezw(char *str);//判断该字符串是不是变量
bool isExistzw(char *str);//判断该变量是否已经在变量数组variable中出现过
bool isSamezw(char *a,char *b,int n);//判断两个字符串是否完全相同
void getVariablezw(code C);   //用来查找链表中的所有变量，并锁存在数组variable中
void displayzw(code C);//作调试用
bool initializezw(code C,CString fileName);//初始化汇编程序


//下面的各个函数分别对应于八个操作符(read、write、+、-、*、/、:=、跳转指令（条件跳转和直接跳转）)对应的操作
int matchzw(char *op);            //把三地址代码的操作指令与操作命令表进行对比，找出该操作对应的标号
bool Readzw(code C,int &readNum,CString fileName);            //对应生成从键盘读取数据的汇编代码
bool Writezw(code C,int &writeNum,CString fileName);            //对应生成向屏幕输出的汇编代码
bool Addzw(code C,CString fileName);            //对应生成加法指令的汇编代码
bool Subzw(code C,CString fileName);            //对应生成减法指令的汇编代码
bool Mulzw(code C,CString fileName);            //对应生成乘法指令的汇编代码
bool Divzw(code C,CString fileName);            //对应生成除法指令的汇编代码
bool Assignzw(code C,CString fileName);            //对应生成赋值指令的汇编代码
bool Jmpzw(code C,CString fileName);            //对应生成跳转指令的汇编代码
bool Endzw(code C,CString fileName);                 //对应结束指令
void addTagzw(code &C);         //增加标签，为跳转做安排
bool analysiszw(code C,int &readNum,int &writeNum,CString fileName);       //编写一个转换汇编的主函数，通过该函数分别调用上面的几个函数，实现对各种指令的转换

bool transzw(CString fileName);
#endif