#include<iostream>
using namespace std;
#include<fstream>
#include<stack>
#include"Whole.h"

class ErrorHandler;

class GramTree
{
private:
	void printtab(fstream & file,int numtab);
	void change_read(fstream & file,TreeNode * node,int tabnum);
	void change_if(fstream & file,TreeNode * node,int tabnum);
	void change_write(fstream & file,TreeNode * node,int tabnum);
	void change_assign(fstream & file,TreeNode * node,int tabnum);
	void change_op(fstream & file,TreeNode * node,int tabnum);
	void change_repeat(fstream & file,TreeNode * node,int tabnum);

protected:
	ErrorHandler *errorHandler;
	
public:
	GramTree()
	{
	}
	void change_tree(fstream &file,TreeNode * node);
};