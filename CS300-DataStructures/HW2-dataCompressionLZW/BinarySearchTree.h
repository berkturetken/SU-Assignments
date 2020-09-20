#include <iostream>
#include <string>

//Berk Türetken, 24222, CS300-HW2 Ziv-Lempel Algorithm, 18.11.2018

#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

using namespace std;

struct BinaryNode
{
	int code;
	string key;
	BinaryNode * left;
	BinaryNode * right;		

	BinaryNode::BinaryNode()
	{
		left = NULL;
		right = NULL;
	}
};

class BinarySearchTree
{
private:
	BinaryNode * root;
	void makeEmpty(BinaryNode * & t)						//private make empty function in the private section of the class
	{
		if( t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}
public:
	BinarySearchTree();
	~BinarySearchTree();
	bool isExist(string key);
	void insertion(string key, int code);
	int KeyPrinting(string key);
};

BinarySearchTree::BinarySearchTree()						//constructor
{
	root = NULL;
}

BinarySearchTree::~BinarySearchTree()						//destructor -> deleting all the nodes in the BST
{
	makeEmpty(root);
}

bool BinarySearchTree::isExist(string word)					//traversing the BST whether the node is there or not
{
	BinaryNode * ptr = root;
	bool found = false;

	if(root != NULL)
	{
		if(root->key == word)
			found = true;	

		while(ptr != NULL && found == false)
		{
			if(ptr->key < word)
				ptr = ptr->right;
			else if(ptr->key > word)
				ptr = ptr->left;
			else
				found = true;
		}
	}
	return found;
}

void BinarySearchTree::insertion(string word, int num)		//inserting the given node with the word and count number
{
	bool dirRight = true;
	if(root == NULL)
	{
		BinaryNode * ptr = new BinaryNode;
		root = ptr;
		root->key = word;
		root->code = num;
	}
	else
	{
		BinaryNode * ptr = root;
		BinaryNode * prev;
		while(ptr != NULL)
		{
			if(ptr->key < word)
			{
				prev = ptr;
				ptr = ptr->right;
				dirRight = true;
			}
			else if(ptr->key > word)
			{
				prev = ptr;
				ptr = ptr->left;
				dirRight = false;
			}
		}
		ptr = new BinaryNode;
		ptr->key = word;
		ptr->code = num;
		if(dirRight == true)
			prev->right = ptr;
		else
			prev->left = ptr;
	}
}

int BinarySearchTree::KeyPrinting(string word)		//printing the key of the code according the spesific key
{
	BinaryNode * ptr = root;

	if(root != NULL)
	{
		if(root->key == word)
			return root->code;	

		while(ptr != NULL)
		{
			if(ptr->key < word)
				ptr = ptr->right;
			else if(ptr->key > word)
				ptr = ptr->left;
			else
				return ptr->code;
		}
	}
}

#endif