#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string reverseWord(string word)			//this function reversing the given word to be able to search in a reverse manner for the puzzle
{
	int len = word.length();
	char x;
	for(int i=0; i < len/2; i++)
	{
		x = word.at(i);					//x is holding the i th index of the word
		word.at(i) = word.at(len-1-i);	//changing the i th index with "len-1-i" th index of the word
		word.at(len-1-i) = x;			//changing the "len-1-i" th index with x which is holding the i th index of the word
	}
	return word;
}

bool rowLevel(string word, vector<vector<char> > & mat)		//searching the given word in a row level
{
	char c;
	int len = word.length(), k=0;
	c = word.at(k);
	bool found = false;

	for(int i=0; i < mat.size() && found == false; i++)
	{
		for(int j=0; j < mat[i].size() && found == false; j++)
		{
			if(mat[i][j] == c && k < len-1)					//checking whether the letter is found or not && whether it is the last index or not
			{
				k++;										//not to cause any crash here while incrementing the k, the index is limited by "len-1"
				c = word.at(k);
			}
			else if ( mat[i][j] == c && k == len-1)			//if the index is the last index and found in the matrix then the word is found
			{
				found = true;
			}
			else if( mat[i][j] != c && k >= 0)				//if the letter is not found then we go back to 0 th index of the word and search from beginning
			{
				k = 0;
				c = word.at(k);
			}
		}
		k=0;												//not to cause any crash, the index is set to 0 again and search from beginning since there is
		c = word.at(k);										//no possibility that we can reach to the indexes where it is out of range of the matrix
	}

	if(found == false)		//if the word is not found, this part is searching the word in the row level but in a reverse manner(i.e. from right to left)
	{                       //Same procedure is in progress!
		k=0;
		c = word.at(k);
		for(int i=0; i < mat.size() && found == false; i++)
		{
			for(int j = mat[i].size()-1; j >= 0 && found == false; j--)
			{
				if(mat[i][j] == c && k < len-1)
				{
					k++;
					c = word.at(k);
				}
				else if ( mat[i][j] == c && k == len-1)
				{
					found = true;
				}
				else if( mat[i][j] != c && k >= 0)
				{
					k = 0;
					c = word.at(k);
				}
			}
			k=0;
			c = word.at(k);
		}
	}
	return found;
}

bool columnLevel(string word, vector<vector<char> > & mat)		//searching the given word in a column level
{
	char c;
	int len = word.length();
	int k=0;
	c = word.at(k);
	bool found = false;

	for(int j=0; j < mat[0].size() && found == false; j++)
	{
		for(int i=0; i < mat.size() && found == false; i++)
		{
			if(mat[i][j] == c && k < len-1)						//checking whether the letter is found or not && whether it is the last index or not
			{
				k++;											//not to cause any crash here while incrementing the k, the index is limited by "len-1"
				c = word.at(k);
			}
			else if ( mat[i][j] == c && k == len-1)				//if the index is the last index and found in the matrix then the word is found
			{
				found = true;
			}
			else if( mat[i][j] != c && k >= 0)					//if the letter is not found then we go back to 0 th index of the word and search from beginning
			{
				k = 0;
				c = word.at(k);
			}
		}
		k=0;													//not to cause any crash, the index is set to 0 again and search from beginning since there is
		c = word.at(k);											//no possibility that we can reach to the indexes where it is out of range of the matrix
	}

	if(found == false)		//if the word is not found, this part is searching the word in the column level but in a reverse manner(i.e. from down to up)
	{						//Same procedure is in progress!
		k=0;
		c = word.at(k);
		for(int j=0; j < mat[0].size() && found == false; j++)
		{
			for(int i = mat.size()-1; i >= 0 && found == false; i--)
			{
				if(mat[i][j] == c && k < len-1)
				{
					k++;
					c = word.at(k);
				}
				else if ( mat[i][j] == c && k == len-1)
				{
					found = true;
				}
				else if( mat[i][j] != c && k >= 0 )
				{
					k = 0;
					c = word.at(k);
				}
			}
			k=0;
			c = word.at(k);
		}
	}
	return found;
}

bool diagonalLevel(string word, vector <vector<char> > & mat, int & joker)		//searching the given word in a diagonal level
{
	int k=0, len=word.length();
	char c=word.at(k);
	bool found=false;

	for(int i=0; i<mat.size() && found == false; i++)
	{
		joker = 1;
		for(int j=0; j<mat[0].size() && found == false; j++)
		{
			if(c==mat[i][j] && k < len-1 && j != mat[0].size()-1 && i != mat.size()-1) 
			{		//checking whether the letter is found or not && whether it is the last index or not && whether the row or column is not the last row or column in the matrix
				k++;
				c=word.at(k);
				i++;
			}
			else if(c==mat[i][j] && k == len-1)		//if the index is the last index and found in the matrix then the word is found
			{
				found=true;
			}
			else if(c!=mat[i][j] && k>0)			//if the letter is not found then we go back to 0 th index of the word and search from beginning
			{
				i = i-k;
				j = j-k;
				k=0;
				c=word.at(k);
			}
			else if(c==mat[i][j] && k!=len-1 && (j == mat[0].size()-1 || i == mat.size()-1) )
			{				//this is the case that the letter is found and is not the last letter of the word and also the row or column of the matrix is not to last row or column of the matrix
				i=i-k;		//go back to the row that the 0 th index is in that row
				j=j-k;		//go back to the column that the 0 th index is in that column
				k=0;
				c = word.at(k);
			}
		}
		k=0;				//not to cause any crash, the index is set to 0 again and search from beginning since there is
		c = word.at(k);		//no possibility that we can reach to the indexes where it is out of range of the matrix
	}
	

	if(found == false)		//if the word is not found, this part is searching the word in the diagonal level but in a reverse manner
	{						//Same procedure is in progress!
		string revWord = reverseWord(word);
		k=0;
		len=word.length();
		c=revWord.at(k);

		for(int i=0; i<mat.size() && found == false; i++)
		{
			joker = 1;
			for(int j=0; j<mat[0].size() && found == false; j++)
			{
				if(c==mat[i][j] && k < len-1 && j != mat[0].size()-1 && i != mat.size()-1)
				{		
					k++;
					c=revWord.at(k);
					i++;
				}
				else if(c==mat[i][j] && k == len-1)
				{
					found=true;
				}
				else if(c!=mat[i][j] && k>0)
				{
					i = i-k;
					j = j-k;
					k=0;
					c=revWord.at(k);
				}
				else if(c==mat[i][j] && k!=len-1 && (j == mat[0].size()-1 || i == mat.size()-1) )
				{
					i=i-k;
					j=j-k;
					k=0;
					c = revWord.at(k);
				}
			}
			k=0;	
			c = revWord.at(k);
		}
	}

	if(found == false)		//if the word is not found, this part is searching the word in the diagonal level with using joker!
	{
		k=0;
		c=word.at(k);
		for(int i=0; i<mat.size() && found == false; i++)
		{
			joker = 1;
			for(int j=0; j<mat[0].size() && found == false;j++)
			{
				if(c==mat[i][j] && k < len-1 && j != mat[0].size()-1 && i != mat.size()-1 )
				{	//checking whether the letter is found or not && whether it is the last index or not && whether the row or column is not the last row or column in the matrix
					k++;
					c=word.at(k);
					i++;
				}
				else if(c==mat[i][j] && k == len-1)		//if the index is the last index and found in the matrix then the word is found
				{
					found=true;
				}
				else if(c!=mat[i][j] && k>=0)			//if the letter is not found, we go inside that loop
				{
					if(joker ==1 && k==len-1)			//in case of we have a joker and the letter is the last letter of the word, this means
					{									//we found that word successfully by using a joker
						joker--;
						found =true;						
					}
					else if(joker == 0)					////if there is no joker then we go back to 0 th index of the word and search from beginning
					{
						i = i-k;
						j = j-k;
						k=0;
						c=word.at(k);
						joker++;
					}
					else if(joker == 1 && k != len-1 && i != mat.size()-1) //if there is a joker and the letter is not the last letter of the word
					{						//not to cause any crash here while incrementing the i, the i is limited by "# of rows-1"
						k++;
						c=word.at(k);
						i++;
						joker--;
					}
				}
				else if(c==mat[i][j] && k!=len-1 && (j == mat[0].size()-1 || i == mat.size()-1) ) 
				{	//this is the case that the letter is found and is not the last letter of the word and also the row or column of the matrix is not to last row or column of the matrix
					i=i-k;		//go back to the row that the 0 th index is in that row
					j=j-k;		//go back to the column that the 0 th index is in that column
					k=0;
					c = word.at(k);
				}
			}
			k=0;					//not to cause any crash, the index is set to 0 again and search from beginning since there is
			c = word.at(k);			//no possibility that we can reach to the indexes where it is out of range of the matrix
		}
	}

	if(found == false)			//if the word is not found with joker, this part is searching the word with joker in the diagonal level but in a reverse manner
	{							//Same procedure is in progress!
		string revWord = reverseWord(word);
		k=0;
		len=word.length();
		c=revWord.at(k);
		for(int i=0; i<mat.size() && found == false; i++)
		{
			joker = 1;
			for(int j=0; j<mat[0].size() && found == false;j++)
			{
				if(c==mat[i][j] && k < len-1 && j != mat[0].size()-1 && i != mat.size()-1 )
				{
					k++;
					c=revWord.at(k);
					i++;
				}
				else if(c==mat[i][j] && k == len-1)
					found=true;
				else if(c!=mat[i][j] && k>=0)
				{
					if(joker ==1 && k==len-1)
					{
						joker--;
						found =true;						
					}
					else if(joker == 0)  
					{
						i = i-k;
						j = j-k;
						k=0;
						c=revWord.at(k);
						joker++;
					}
					else if(joker ==1 && k != len-1 && i != mat.size()-1)
					{
						k++;
						c=revWord.at(k);
						i++;
						joker--;
					}
				}
				else if(c==mat[i][j] && k!=len-1 && (j == mat[0].size()-1 || i == mat.size()-1) )
				{
					i=i-k;
					j=j-k;
					k=0;
					c = revWord.at(k);
				}
			}
			k=0;	
			c = revWord.at(k);
		}
	}
	return found;
}

int main()
{
	vector <vector<char> > mat;
	ifstream input;
	string str, line, word;
	char ch;
	int past=0, joker = 1, totalscore = 0;

	cout << "This program allows you to play a Sunday morning puzzle on your computer." << endl;
	cout << "---" << endl;
	cout << "Enter the matrix file name: ";
	cin >> str;

	input.open(str.c_str());
	while(input.fail())  //asking to the user until the user inputs a correct file
	{
		cout << "Invalid file name!" << endl;
		cout << "---" << endl;
		cout << "Enter the matrix file name: ";
		cin >> str;
		input.open(str.c_str());
	}

	while(getline(input,line))  //first of all reading the file line by line
	{
		int current = 0;
		istringstream iss(line);
		vector<char> temp;
		while(iss.get(ch))    //for each line, reading the lines char by char
		{
			temp.push_back(ch);
			current++;    //current is holding the number of columns for each row
		}
		mat.push_back(temp);

		if(past != current && past != 0)    //if past is not equal to the current then there is no row equality!
		{
			cout << "The matrix does not have row equality, terminating..." << endl;
			return 0;
		}
		else 
			past = current;
	}

	cout << "---" << endl;
	cout << "Enter a word: ";
	cin >> word;

	while(word.length() > 2)   //until the user enters a word which its length is smaller than 3, the user can enter words that s/he want to find in the matrix
	{
		int len = word.length();
		if (rowLevel(word, mat) == true)   //In this block, program calculates the total points according to some calculation rules and the user's inputs
		{
			if(len <= 5)
			{
				cout << word << " is found in the row level. It contributes " << len << " points." << endl;
				totalscore = totalscore + len;
			}
			else
			{
				cout << word << " is found in the row level. It contributes " << len+2 << " points." << endl;
				totalscore = totalscore + len + 2;
			}
		}
		else if (columnLevel(word, mat) == true)
		{
			if(len <= 5)
			{
				cout << word << " is found in the column level. It contributes " << len << " points." << endl;
				totalscore = totalscore + len;
			}
			else
			{
				cout << word << " is found in the column level. It contributes " << len+2 << " points." << endl;
				totalscore = totalscore + len + 2;
			}

		}
		else if (diagonalLevel(word, mat, joker) == true)
		{
			if(joker==1)
			{
				if(len <= 5)
				{
					cout << word << " is found in the diagonal level. It contributes " << len*2 << " points." << endl;
					totalscore = totalscore + (len*2);
				}
				else
				{
					cout << word << " is found in the diagonal level. It contributes " << len*2+2 << " points." << endl;
					totalscore = totalscore + (len*2+2);
				}
			}
			else
			{
				if(len <=5)
				{
					cout << word << " is found in the diagonal level. One letter was replaced by joker. It contributes " << (len*2)-2 << " points." << endl;
					totalscore = totalscore + (len*2) -2;
				}
				else
				{
					cout << word << " is found in the diagonal level. One letter was replaced by joker. It contributes " << (len*2) << " points." << endl;
					totalscore = totalscore + (len*2);
				}
			}
		}
		else
		{
			cout << word << " is not found in the matrix. 5 points are deducted." << endl;
			totalscore = totalscore -5;
		}

		cout << "---" << endl;
		cout << "Enter a word: ";
		cin >> word;
	}
	cout << "---" << endl;
	cout << "Game has ended." << endl;
	cout << "Total score of the words: " << totalscore << endl;
	return 0;
}