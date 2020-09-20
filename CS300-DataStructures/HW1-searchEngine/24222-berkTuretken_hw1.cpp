#include <iostream>
#include <string>
#include "LinkedList.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"

using namespace std;

int main()
{
	LinkedList<string> linkedlist;
	string str,line;
	ifstream input;
	cout << "Enter the file name: ";
	cin >> str;

	input.open(str.c_str());
	while(input.fail())				//asking for a filename until the user inputs a valid filename
	{

		cout << "Invalid file name!" << endl;
		cout << "Enter a valid file name: ";
		cin >> str;
		input.open(str.c_str());
	}

	while(getline(input,line))		
	{
		string w;
		int num;
		istringstream iss(line);
		iss >> w >> num;
		ToLower(w);					//lowering all the words to be able to compare properly in the linked list
		linkedlist.insertion(w,num);
	}

	string user_str;
	int user_int;

	cout << "Enter number of words to be searched: ";
	cin >> user_int;		//this is the number of words to be searched that the user enters
	
	while(user_int != 0){	
		string total_user_str;

		cout << "Enter the words: ";
		vector<int> vec;
		for(int i=0; i < user_int; i++)
		{
			cin >> user_str;

			total_user_str = total_user_str + user_str + " ";  //concatenating the words that the user inputs to print properly at the end
			ToLower(user_str);								   //lowering all the words to be able to compare properly in the linked list
			linkedlist.docNumberList(user_str, vec, i);
		}
		int size = vec.size();

		/********** Counting common document numbers **********/
		int ctr = 0;
		for(int m=0; m < size; m++)			
		{
			if(vec[m] != 0)
				ctr++;
		}

		cout << total_user_str << ctr << " ";

		/********** Printing the values in a proper way**********/
		for(int j=0; j<size; j++)
		{
			if(vec[j] != 0)
				cout << vec[j] << " ";
		}
		cout << endl;
		cout << "Enter number of words to be searched: ";
		cin >> user_int;
	}
	return 0;
}