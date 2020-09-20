#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"

using namespace std;

struct info  //creating a struct for every matchcodes, teams, and odds
{
	int matchcode;
	string team1, team2;
	double odd1, odd0, odd2;
};

int checker(ifstream & scoresinput, int & coupon_code) //checking the coupon whether the bets are true or not
{
	string line3;
	while(getline(scoresinput, line3))
	{
		istringstream iss3(line3);
		int matchcode_scores;
		string score;
		iss3 >> matchcode_scores >> score;
		int score1 = atoi(score.substr(0,1));
		int score2 = atoi(score.substr(2));
		if (coupon_code == matchcode_scores)
		{
			scoresinput.clear();
			scoresinput.seekg(0);
			if(score1 > score2)
				return 1;
			else if(score2 > score1)
				return 2;
			else if(score1=score2)
				return 0;
		}
	}
}

int main()
{
	ifstream input;
	ifstream matchesinput;
	ifstream scoresinput;
	string str1, str2, str3;


	cout << "This is a simple betting program." << endl;
	cout << endl << "Please enter a filename which contains whole betting program: ";
	cin >> str1;
	input.open(str1.c_str());

	while ( input.fail()) //asking the right name of the file until the computer gets the right name
	{
		cout << "Error for opening " << str1 << " Please enter filename again: ";
		cin >> str1;
		input.open(str1.c_str());
	}
	cout << "Please enter a filename which contains the matches played by a user: ";
	cin >> str2;

	matchesinput.open(str2.c_str());
	while(matchesinput.fail()) //asking the right name of the file until the computer gets the right name
	{
		cout << "Error for opening " << str2 << " Please enter filename again: ";
		cin >> str2;
		matchesinput.open(str2.c_str());
	}
	cout << "Please enter a filename which contains the match scores of the week: ";
	cin >> str3;

	scoresinput.open(str3.c_str());
	while (scoresinput.fail()) //asking the right name of the file until the computer gets the right name
	{
		cout << "Error for opening " << str3 << " Please enter filename again: ";
		cin >> str3;
		scoresinput.open(str3.c_str());
	}
	cout << endl;

	vector <info> vec;
	string line;

	while (getline(input,line))
	{
		istringstream iss(line);
		int matchcode;
		string word, team2;
		string team1 = " ";
		double odd1, odd0, odd2;
		iss >> matchcode >> word; //taking the second word of the coupon's line
		team1 += word;
		
		while( word != "-") //getting the word for team1 until '-'
		{
			iss >> word;
			team1 = team1 + " " + word;
		}
		iss >> team2 >> odd1 >> odd0 >> odd2; //taking the words after '-'

		info inf;
		inf.matchcode = matchcode;
		inf.team1 = team1;
		inf.team2 = team2;
		inf.odd1 = odd1;
		inf.odd0 = odd0;
		inf.odd2 = odd2;
		vec.push_back(inf);
	}

	string line2, firstword, secondword, thirdword;
	double stake;
	getline(matchesinput, line2);
	istringstream iss2(line2);
	iss2 >> firstword >> secondword >> thirdword;
	stake = atof(secondword); //calculating the stake

	double total, totalodds = 1;
	int count=0;
	bool flag = true;
	bool codeflag = true;
	while (getline(matchesinput, line2))
	{
		istringstream iss2(line2);
		int coupon_code, coupon_odd;
		iss2 >> coupon_code >> coupon_odd;
		
		if (itoa(coupon_code).length() > 3) //if the user enters a matchcode whose length is more than 3
		{
			codeflag = false;
		}
		
		for(int i=0; i < vec.size(); i++)
		{
			info j = vec[i];
			if ( j.matchcode == coupon_code)
			{
				count++;
				cout << j.matchcode << j.team1 << " "  << j.team2 << " ";
				if(checker(scoresinput, coupon_code) == coupon_odd) //checking whether the coupon code exists in the matchscores file
				{
					if(coupon_odd==1)
						total = j.odd1;
					else if (coupon_odd == 0)
						total = j.odd0;
					else if (coupon_odd == 2)
						total = j.odd2;
					cout << total << " " << "SUCCESS" << endl;
					totalodds *= total;
				}
				else
				{
					if(coupon_odd==1)
						total = j.odd1;
					else if (coupon_odd == 0)
						total = j.odd0;
					else if (coupon_odd == 2)
						total = j.odd2;
					cout << total << " " << "FAILED" << endl;
					flag = false;
				}
			}
		}
	}
	if (count<3 || codeflag == false)
	{
		cout << endl << "INVALID COUPON" << endl;
	}
	else if (!flag)
	{
		cout << endl << "YOU LOST, " << "10.55 TL " << "HAS GONE" << endl;
	}
	else
	{
		cout << endl << "TOTAL ODDS: " << totalodds << endl;
		cout << endl << "You won " << stake * totalodds << " TL" << endl;
	}
	
	cout << endl << "!!! BET \"LEGALLY\" AND \"RESPONSIBLY\" !!!" << endl << endl;

	input.close();
	scoresinput.close();
	matchesinput.close();
	return 0;
}