#include <iostream>
#include <string>
#include <vector>

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

using namespace std;

template <class Type>
struct nodeDoc						//creating a node for the main node which contains strings
{
	int num;
	nodeDoc<Type> *down;

	nodeDoc::nodeDoc()
	{
		down = NULL;
	}
};

template <class Type>
struct node							//creating a node for the document node which contains integers
{
	Type data;
	node<Type> *next;
	nodeDoc<Type> *down;

	node::node()
	{
		next = NULL;
		down = NULL;
	}
};


template <class Type>
class LinkedList
{
private:
	node<Type> *head;

public:
	LinkedList();
	~LinkedList();
	void insertion(Type data, int num);
	void print();						//just for debugging purposes
	void docNumberList(string data, vector<int> & vec, int i);
};

template <class Type>
LinkedList<Type>::LinkedList()			//constructor
{
	head = NULL;
}

template <class Type>
LinkedList<Type>::~LinkedList()			//destructor which is deleting all the nodes in the linked list
{
	node<Type> * ptr = head;
	while(ptr != NULL)
	{
		node<Type> * temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

template <class Type>
void LinkedList<Type>::insertion(Type data, int num)		//string insertion to main node or integer insertion to document node
{
	bool found = false;

	node<Type> * isExist = head;
	while(isExist != NULL)
	{
		if(data == isExist->data)							//if the data is already exist in the linked list
		{
			found = true;
			break;											// to be able to catch the last node where the isExist points 
		}
		isExist = isExist->next;
	}

	if(found == false)										//if the word comes to the first time in the linked list
	{
		node<Type> * ptr = new node<Type>;					//ptr is a new node for the string
		nodeDoc<Type> * temp = new nodeDoc<Type>;			//temp is a new node for the integer
		ptr->data = data;
		temp->num = num;

		if(head == NULL)									//if there is no element in the linked list
		{
			head = ptr;
			head->next = NULL;
			head->down = temp;
		}
		else if(data < head->data)	//if the word is smaller than the word which is pointed by head pointer(i.e. computer < sabanci)
		{
			ptr->next = head;
			head = ptr;
			head->down = temp;
		}
		else if(data > head->data)	//if the word is greater than the word which is pointed by head pointer(i.e. university > sabanci)
		{
			node<Type> * current = head;		

			while(current->next != NULL && data > current->next->data)	//traversing the linked list to find a place for the new word
				current = current->next;

			if(current->next == NULL)	//if the word is greater than all of the words in the linked list
			{
				ptr->next = NULL;
				current->next = ptr;
				ptr->down = temp;
			}
			else						//if the word must be placed between head and last nodes in the linked list
			{
				ptr->next = current->next;
				current->next = ptr;
				ptr->down = temp;
			}
		}
	}

	else if(found == true)					//if the word is already exist in the linked list
	{
		if(num < isExist->down->num)		//if the document number is smaller than the first node of integer linked list
		{
			nodeDoc<Type> * temp = new nodeDoc<Type>;
			temp->num = num;
			temp->down = isExist->down;
			isExist->down = temp;
		}
		else if(num > isExist->down->num)	//if the document number is greater than the first node of integer linked list
		{
			nodeDoc<Type> * current = isExist->down;		
			nodeDoc<Type> * current2 = current->down;

			while(current2 != NULL && num > current2->num)
			{
				current = current2;
				current2 = current2->down;
			}

			if(current2 != NULL && num != current2->num)		//if the number must be placed between the head and last node		
			{
				nodeDoc<Type> * temp = new nodeDoc<Type>;
				temp->num = num;
				temp->down = current2;
				current->down = temp;	
			}
			else if(current2 == NULL && num != current->num)	//if the number must be placed at the end of the linked list
			{
				nodeDoc<Type> * temp = new nodeDoc<Type>;
				temp->num = num;
				temp->down = NULL;			
				current->down = temp;
			}
		}
	}
}

/*********** JUST FOR DEBUGGING ***********/
/*
template <class Type>
void LinkedList<Type>::print()				
{
	node<Type> * temp = head;
	while(temp != NULL)
	{
		cout << temp->data << " ";
		nodeDoc<Type> * curr = temp->down;
		while(curr != NULL)
		{
			cout << curr->num << " ";
			curr = curr->down;
		}
		cout << endl;
		temp = temp->next;
	}
}
*/
/********* JUST FOR DEBUGGING ***********/

template <class Type>
void LinkedList<Type>::docNumberList(string data, vector<int> & vec, int i)	//creating vector,
	//comparing and merging the document numbers
{
	int size = vec.size();
	node<Type> * ptr = head;				//ptr is for the main node which stores string

	while(ptr != NULL && data != ptr->data)
		ptr = ptr->next;

	if(ptr != NULL)							//if the word is exist in the linked list
	{
		nodeDoc<Type> * temp = ptr->down;	//temp is for the document node which stores integer
		int count = 0;

		if(i==0)				//if the words that is inputted by the user is coming for the first time
		{
			while(temp != NULL)
			{
				vec.push_back(temp->num);
				temp = temp->down;
			}
		}
		else					//if the words that is inputted by the user is coming second, third, fourth... times
		{
			for(int k=0; k < size; k++) //traversing the vector elements
			{
				bool found = false;
				temp = ptr->down;
				while(temp != NULL)		
				{
					if(vec[k] == temp->num)		//checking whether the element is equal to integer which is stored in the node
						found = true;
					temp = temp->down;	//traversing the linked list (integer one)
				}
				if(found == false)		//if the integer which is stored in vector does not match the document numbers, make it zero
										//so that I can reach the common document numbers easily
				{
					vec[k] = 0;
				}
			}
		}
	}
	else	//if the word is not exist in the linked list, clear the vector since there can not be common document numbers
	{
		vec.clear();
	}
}
#endif