#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;
// berk turetken  

bool checker1(string s) // checking three conditions; wrong char at the first index, wrong char at the last index, two operands in succession
{
	int length = s.length();
	int index = s.length()-1;
	if ( s.at(0) != '+' && s.at(0) != '-' && s.at(0) != '/' && s.at(0) != '*' )
	{
		if (s.at(index) != '+' && s.at(index) != '-' && s.at(index) != '/' && s.at(index) != '*' )
		{
			for ( int i=0; i<length; i++)
			{
				if (s.find("++") == string::npos && s.find("+-") == string::npos && s.find("-+") == string::npos && s.find("--") == string::npos &&
					s.find("**") == string::npos && s.find("//") == string::npos && s.find("*/") == string::npos && s.find("*/") == string::npos)
				{
					return true;
				}
			}
			return false;
		}
		return false;
	}
	return false;
}

bool checker2(string s) // checking the invalid chars
{
	int length = s.length();
	bool flag = true;
	for (int i = 0; i < length; i++)
	{
		if ( s.at(i) == '1'|| s.at(i) == '2' || s.at(i) == '3' || s.at(i) == '4' || s.at(i) == '5' || s.at(i) == '6' || s.at(i) == '7' || 
			s.at(i) == '8' || s.at(i) == '9' || s.at(i) == '0' || s.at(i) == '+' || s.at(i) == '-' || s.at(i) == '/' || s.at(i) == '*')
		{
			i++;
			flag;
		}

		else
		{
			i++;
			flag = !flag;
		}
	}
	return flag;
}

int calculate_addsubtract(string s) // if there exists + and - signs, making the necessary calculations
{
	int i = s.length() - 1;
	string number;
	int num, sum = 0;
	while ( i >= 0)
	{
		if (s.at(i) == '+')
		{
			number = s.substr(i+1);
			num = atoi(number);
			sum += num;
			s = s.substr(0, i);
		}
		else if (s.at(i) == '-')
		{
			number = s.substr(i+1);
			num = atoi(number);
			sum -= num;
			s = s.substr(0, i);
		}
		i--;
	}
	int x = sum + atoi(s);
	return x;
}

double calculate_multdivision(string s) // if there exists * and / signs, making the necessary calculations
{
	int i = s.length() - 1;
	string number;
	double num, sum = 1;
	while ( i >= 0)
	{
		if (s.at(i) == '*')
		{
			number = s.substr(i+1);
			num = atoi(number);
			sum = sum * num;
			s = s.substr(0, i);
		}
		else if (s.at(i) == '/')
		{
			number = s.substr(i+1);
			num = atoi(number);
			sum = sum / num;
			s = s.substr(0, i);
		}
		i--;
	}
	double x = sum * atoi(s);
	return x;
}

int main()
{
	string line;
	cout << "Please enter the expression to calculate: ";
	cin >> line;

	while (line != "QUIT" && line != "quit" && line != "EXIT" && line != "exit" && line != "END" && line != "end")
	{
		if (checker1(line) && checker2(line)) // checking the validity of the input
		{
			if( line.find("+") != string::npos || line.find("-") != string::npos)
			{
				cout << calculate_addsubtract(line) << endl;
				cout << endl << "Please enter the expression to calculate: ";
				cin >> line;
			}
			else if (line.find("/") != string::npos || line.find("*") != string::npos) 
			{
				if (line.find("/0") == string::npos) // checking whether the number is divided by 0 or not
				{
					cout << calculate_multdivision(line) << endl;
					cout << endl << "Please enter the expression to calculate: ";
					cin >> line;
				}
				else
				{
					cout << "You cannot divide by 0" << endl;
					cout << endl << "Please enter the expression to calculate: ";
					cin >> line;
				}
			}
			else 
			{
				cout << line << endl;
				cout << endl << "Please enter the expression to calculate: ";
				cin >> line;
			}
		}
		else 
		{
			cout << "Invalid entry" << endl;
			cout << endl << "Please enter the expression to calculate: ";
			cin >> line;
		}
	}
	cout << "GOOD BYE" << endl; 
	return 0;
}