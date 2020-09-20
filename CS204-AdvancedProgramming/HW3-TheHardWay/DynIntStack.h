
using namespace std;

#ifndef DYNSTACK_H		
#define DYNSTACK_H
#include <string>


struct StackNode
{
	string name;
	int occur;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode * top;
public:
	DynIntStack(void);
	void push(string, int);
	void pop(string &, int &);
	bool isEmpty(void);
	~DynIntStack();
};

#endif