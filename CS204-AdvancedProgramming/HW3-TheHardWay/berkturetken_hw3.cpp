#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynIntStack.h"

using namespace std;

//berk turetken

int main()
{
	DynIntStack stack1, stack2, stacktemp, stacktemp2;
	ifstream input, input2;
	string str, str2, choice, word, word2, line, line2;
	string val, val2, val3;  // creating dummy strings for the function pop
	int occur, occur2, size1 = 0, size2 = 0;

	cout << "This program finds the common words of two files using stacks." << endl;
	cout << "---" << endl;
	cout << "Enter the first file name: ";
	cin >> str;

	input.open(str.c_str());
	while(input.fail())		//asking for a valid file name until the user inputs a valid file name for the first file
	{
		cout << "Enter the first file name: ";
		cin >> str;
		input.open(str.c_str());
	}

	cout << "Enter the second file name: ";
	cin >> str2;

	input2.open(str2.c_str());
	while(input2.fail())	//asking for a valid file name until the user inputs a valid file name for the second file
	{
		cout << "Enter the second file name: ";
		cin >> str2;
		input2.open(str2.c_str());
	}

	while (getline(input, line))
	{
		occur = 1;
		istringstream iss(line);
		while (iss >> word){			//putting all the words into the stack without checking their occurances for the first file
			stacktemp.push(word, occur);
			size1++;
		}
	}
	
	while (getline(input2, line2))
	{
		occur2 = 1;
		istringstream iss2(line2);
		while (iss2 >> word2){			//putting all the words into the stack without checking their occurances for the second file
			stacktemp2.push(word2, occur2);
			size2++;
		}
	}
	
	cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
	cin >> choice;

	while( choice != "1" && choice != "2")		//if the user inputs other than "1" or "2", the program gives appropriate message
	{
		cout << "---" << endl;
		cout << "Invalid choice" << endl;
		cout << "---" << endl;
		cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
		cin >> choice;
	}
	cout << "---" << endl;
	
	while(!stacktemp.isEmpty())		//reversing the order of the stack - to get the first order in the file
	{
		stacktemp.pop(val,occur);
		stack1.push(val,occur);
	}

	while(!stacktemp2.isEmpty())	//reversing the order of the stack - to get the first order in the file
	{
		stacktemp2.pop(val,occur);
		stack2.push(val,occur);
	}

	/*organizing the stack according to the occurances of the words for the first file
	(i.e. if the word occurred more than once in the file, the occurance is updated*/
	while(!stack1.isEmpty())
	{
		int cnt = 1;
		stack1.pop(val,occur);
		stacktemp.push(val,occur);
		while(!stack1.isEmpty())
		{
			stack1.pop(val2,occur2);
			if(val == val2)
				cnt++;
			else
				stacktemp.push(val2, occur2);
		}
		size1 = size1 - cnt;
		int i=0;
		while(i < size1)
		{
			stacktemp.pop(val3, occur2);
			stack1.push(val3, occur2);
			i++;		
		}
		stacktemp.pop(val3,occur);		//updating the occurance of the word
		stacktemp.push(val3, cnt);
	}
	while(!stacktemp.isEmpty())		//reversing the order of the stack
	{
		stacktemp.pop(val,occur);
		stack1.push(val,occur);
	}

	/*organizing the stack according to the occurances of the words for the second file
	(i.e. if the word occurred more than once in the file, the occurance is updated*/
	while(!stack2.isEmpty())
	{
		int cnt = 1;
		stack2.pop(val, occur);
		stacktemp2.push(val,occur);
		while(!stack2.isEmpty())
		{
			stack2.pop(val2, occur2);
			if(val == val2)
				cnt++;
			else
				stacktemp2.push(val2,occur2);
		}
		size2 = size2 - cnt;
		int i=0;
		while(i < size2)
		{
			stacktemp2.pop(val3, occur2);
			stack2.push(val3, occur2);
			i++;
		}
		stacktemp2.pop(val3,occur);		//updating the occurance of the word
		stacktemp2.push(val3,cnt);
	}
	while(!stacktemp2.isEmpty())		//reversing the order of the stack
	{
		stacktemp2.pop(val,occur);
		stack2.push(val,occur);
	}

	bool found = false;
	if ( choice == "1")			
	{
		while(!stack1.isEmpty())
		{
			stack1.pop(val,occur);
			found = false;
			while(!stack2.isEmpty() && found == false)
			{
				stack2.pop(val2,occur2);		//traversing the whole list to find the common words for the two files
				if(val == val2)
				{
					if( occur <= occur2)
						cout << "The word \"" << val << "\" occurred at least " << occur <<" time(s) in both files." << endl; 
					else
						cout << "The word \"" << val << "\" occurred at least " << occur2 <<" time(s) in both files." << endl;
					found = true;
				}
				else
					stacktemp.push(val2, occur2);
			}
			while(!stacktemp.isEmpty())		//pushing all the words into the stack2 again to be able to traverse again
			{
				stacktemp.pop(val2, occur2);
				stack2.push(val2, occur2);
			}
		}
	}
	
	else if( choice == "2")
	{
		while(!stack2.isEmpty())
		{
			stack2.pop(val,occur);
			found = false;
			while(!stack1.isEmpty() && found == false)
			{
				stack1.pop(val2,occur2);		//traversing the whole list to find the common words for the two files
				if(val == val2)
				{
					if( occur <= occur2)
						cout << "The word \"" << val << "\" occurred at least " << occur <<" time(s) in both files." << endl; 
					else
						cout << "The word \"" << val << "\" occurred at least " << occur2 <<" time(s) in both files." << endl;
					found = true;
				}
				else
					stacktemp2.push(val2, occur2);
			}
			while(!stacktemp2.isEmpty())		//pushing all the words into the stack1 again to be able to traverse again
			{
				stacktemp2.pop(val2, occur2);
				stack1.push(val2, occur2);
			}
		}
	}
	return 0;
}