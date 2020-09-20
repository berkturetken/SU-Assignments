#include <iostream>
#include <string>
#include "DynIntStack.h"

using namespace std;

DynIntStack::DynIntStack()
{
	top = NULL;
}

DynIntStack::~DynIntStack()
{
	StackNode * ptr;
	while(top != NULL)
	{
		ptr = top;
		top = top->next;
		delete ptr;
	}
}

void DynIntStack::push(string word, int occur)
{
	StackNode * newNode;
	newNode = new StackNode;
	newNode -> name = word; 
	newNode -> occur = occur;

	if(isEmpty()){
		top = newNode;
		newNode -> next = NULL;
	}

	else{
		newNode ->next = top;
		top = newNode;
	}
}

void DynIntStack::pop(string & word, int & occur)
{
	StackNode * temp;
	if(isEmpty()){
		cout << "The stack is empty." << endl;
	}
	else{
		word = top->name;
		occur = top->occur;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool DynIntStack::isEmpty(void)
{
	bool status;

	if(top==NULL){
		status = true;
	}
	else{
		status = false;
	}
	return status;
}

