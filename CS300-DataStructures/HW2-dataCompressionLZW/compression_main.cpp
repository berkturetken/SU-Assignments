#include <iostream>
#include <string>
#include "BinarySearchTree.h"
#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

//Berk Türetken, 24222, CS300-HW2 Ziv-Lempel Algorithm, 18.11.2018

int main()
{
	BinarySearchTree bst;
	string str, word= "";
	ifstream input;
	ofstream output;
	output.open("compout.txt");

	cout << "Enter the file name: ";
	cin >> str;

	input.open(str.c_str());
	while(input.fail())								//asking to user until getting for a valid file name
	{
		cout << "Invalid file name!" << endl;
		cout << "Enter a valid file name: ";
		cin >> str;
		input.open(str.c_str());
	}
	char ch;

	while(!input.eof())
	{
		input.get(ch);
		word += ch;
	}
	word = word.substr(0,word.length()-1);	//avoid to get the extra character of word
	
	bool found = true;
	int count = 256, i=2;

	while(word.length() > 1)				//processing until there is left only 1 character in the string
	{
		string s;
		if(found == false){					//if the first two characters are in the string, process the next character
											// (i.e. now, the searching word has 3 characters and goes on like this)
			if(word.length() >= i)			// check whether the word can be seperated
				s = word.substr(0,i);		//if so, do it and process!!!
			else							// EDGE CASE -> if the new word(i.e. it has 3 characters) can not be seperated 
			{
				s = word;					
				output << bst.KeyPrinting(s) << " ";	//print the last word to the file
				output.close();
				break;						// do not process the while loop since there is no word anymore!
			}
		}
		else if(found == true)				//taking the first two character of string to compare with the dictionary
			s = word.substr(0,i);

		// Now, there are 2 cases. 
		// 1) The input that is taken from the string does exist in the dictionary
		// 2) The input that is taken from the string does NOT exist in the dictionary

		if(bst.isExist(s) == false)			// 2.case kicks in (the string is not in the dictionary)
		{
			bst.insertion(s, count);		//insert to the binary search tree with the number which starts with 256	 
			if(i == 2)						//output procedure for a character
				output << (int)s.at(0) << " ";	
			else							//output procedure for a string 
				output << bst.KeyPrinting(s.substr(0,i-1)) << " ";
			
			word = word.substr(i-1);		//to be able to traverse the string char by char (actually one after another),
											//I just cut the string according to the i value
			count++;
			found = true;					//let the function know that now the string is in the dictionary
			i=2;							//since I FIRSTLY check the two consecutive characters in the string, update i value
		}
		else								// 1.case kicks in (the string is ALREADY in the dictionary)
		{
			i++;							//go to the next char in the string
			found = false;					//let the function know that the string which is taken firstly is NOT in the dictionary
		}
	}

	if(word.length() == 1)					//if there is still a character in the word, print it
		output << (int)word.at(0) << endl;

	output.close();
	return 0;
}