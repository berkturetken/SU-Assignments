#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Berk Türetken, 24222, CS300-HW2 Ziv-Lempel Algorithm, 18.11.2018

int main()
{
	string str;
	ifstream input;
	ofstream output;
	output.open("decompout.txt");

	cout << "Enter the file name: ";
	cin >> str;

	input.open(str.c_str());
	while(input.fail())							//asking to user until getting for a valid file name 
	{
		cout << "Invalid file name!" << endl;
		cout << "Enter a valid file name: ";
		cin >> str;
		input.open(str.c_str());
	}

	bool first = true;							//this bool is for the first number of the compout file
	string s;
	int n;										//to get each numbers from the compout file
	int count = 256;							//since we assume that we have ascii table, the first code that I assigned is "256"
	string keyarray[4096];						//stated in the hw file - creating the dictionary in the array
	for(int i=0; i<256; i++){					//filling the first 256 positions of array with ascii table
		keyarray[i] = (char)i;
	}

	while (input >> n)
	{
		if(first == true)						//to get the first number of the compout files
		{
			output << (char)n;
			s += (char)n;						//updating the s for the next number;
		}
		
		/*Now, there can be 3 cases. 
		1- the number is in the ascii table so it would be definitely in the dictionary.
		2- the number is greater than the ascii table values. Then, there can be 2 cases.
			2.1- If the number is in the dictionary
			2.2- If the number is not in the dictionary
		*/

		if( n <= 255 && first == false)		// First case kicks in (1-)
		{
			output << (char)n;
			string word;					
			word += s + (char)n;					//concetaneting the previous key of code and the first char of that number
			keyarray[count] = word;					//adding to the array
			count++;				
			s = (char)n;							//updating the s. Since n must be a char, we can use like this
		}
		else if( n > 255 && first == false)			// Second case kicks in (2-)
		{
			if(n < count){							// 2.1 kicks in (number is in the dictionary)
				string temporary = keyarray[n];		//finding the key of the code
				output << temporary;
				string word2;
				word2 += s + temporary.at(0);		//concetaneting the previous key of code and the first char of that number
				keyarray[count] = word2;			//adding to the array
				count++;
				s = temporary;			//updating the s. Since n should not be necessarily a char, that's why I created temporary
			}
			else									//2.2 kicks in (number is NOT in the dictionary)
			{
				string newstr;						
				newstr += s + s.substr(0,1);		//concetaneting the previous key of code&first char of the previous key of code
				output << newstr;
				keyarray[count] = newstr;			//adding to the array
				count++;
				s = newstr;				//updating the s. Since n should not be necessarily a char,that's why I created newstr 
			}
		}
		first = false;					//after getting the first number from the compout file, this should be false 
										//to avoid get into the first function again
	}
	return 0;
}