#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct teaminfo
{
	string teamname;
	int matches_played,win,draw,lost,scored,conceded,difference,point;
};

void SelectionSort(vector<teaminfo> & vec)
{
	int j, k,maxIndex;
	teaminfo temp;
	for(k=0; k < vec.size() - 1; k++)
	{   
		maxIndex = k;             // maximal element index
		for(j=k+1; j < vec.size(); j++)
		{   
			if (vec[j].point > vec[maxIndex].point ) 
				maxIndex = j;     // new max, store index
			if (vec[j].point == vec[maxIndex].point )
			{
				if (vec[j].difference > vec[maxIndex].difference)
					maxIndex = j;
			}
			if ( vec[j].point == vec[maxIndex].point && vec[j].difference == vec[maxIndex].difference )
			{
				if (vec[j].teamname < vec[maxIndex].teamname )
					maxIndex = j;
			}
		}
		temp = vec[k];     // swap max and k-th elements
		vec[k]= vec[maxIndex];
		vec[maxIndex] = temp;
	}
}

int main()
{
	ifstream input;
	string str1, str2, line2, team1name, team2name;
	int score1, score2;
	vector<teaminfo> vec;

	cout << "Please enter a filename: ";
	cin >> str1;
	input.open(str1.c_str());
	while (input.fail())
	{
		cout << "Program cannot open " << str1 << endl;
		cout << "Please enter a filename: ";
		cin >> str1;
		input.open(str1.c_str());
	}

	while(getline(input, line2))
	{
		istringstream iss(line2);
		iss >> team1name >> score1 >> score2 >> team2name;
		bool flag = true;
		bool flag2 = true;
		for (int i=0; i < vec.size() & (flag || flag2); i++)
		{
			if(team1name == vec[i].teamname)
			{
				vec[i].matches_played++;
				vec[i].scored+=score1;
				vec[i].conceded+=score2;
				vec[i].difference += (score1-score2);
				if(score1 > score2)
				{
					vec[i].win++;
					vec[i].point+=3;
				}
				else if(score2 > score1)
					vec[i].lost++;
				else if(score1 == score2)
				{
					vec[i].draw++;
					vec[i].point++;
				}
				flag = false;
			}

			if(team2name == vec[i].teamname)
			{
				vec[i].matches_played++;
				vec[i].scored+=score2;
				vec[i].conceded+=score1;
				vec[i].difference += (score2-score1);
				if(score2 > score1)
				{
					vec[i].win++;
					vec[i].point+=3;
				}
				else if(score1 > score2)
					vec[i].lost++;
				else if(score1 == score2)
				{
					vec[i].draw++;
					vec[i].point++;
				}
				flag2 = false;
			}
		}

		if(flag == true)
		{
			int count = 0, win = 0, scored = 0, conceded = 0, point = 0, lost = 0, draw = 0;
			count++;
			scored += score1;
			conceded += score2;
			if(score1 > score2)
			{
				win++;
				point = point + 3;
			}
			else if(score2 > score1)
				lost++;
			else if(score1 == score2)
			{
				draw++;
				point = point + 1;
			}
			teaminfo inf;
			inf.teamname = team1name;
			inf.matches_played = count;
			inf.win = win;
			inf.draw = draw;
			inf.lost = lost;
			inf.scored = scored;
			inf.conceded = conceded;
			inf.difference = scored - conceded;
			inf.point = point;
			vec.push_back(inf);
		}

		if(flag2 == true)
		{
			int count2 = 0, win2 = 0, scored2 = 0, conceded2 = 0, point2 = 0, lost2 = 0, draw2 = 0;
			count2++;
			scored2 += score2;
			conceded2 += score1;
			if(score2 > score1)
			{
				win2++;
				point2 = point2 + 3;
			}
			else if(score1 > score2)
				lost2++;
			else if(score1 == score2)
			{
				draw2++;
				point2 = point2 + 1;
			}
			teaminfo inf2;
			inf2.teamname = team2name;
			inf2.matches_played = count2;
			inf2.win = win2;
			inf2.draw = draw2;
			inf2.lost = lost2;
			inf2.scored = scored2;
			inf2.conceded = conceded2;
			inf2.difference = scored2 - conceded2;
			inf2.point = point2;
			vec.push_back(inf2);
		}
	}
	SelectionSort(vec);

	bool flag3 = true;
	cout << "Please enter a team name: ";
	string searchTeam;
	cin >> searchTeam;
	for(int i=0; i < vec.size() && flag3; i++)
	{
		if(vec[i].teamname == searchTeam)
		{
			cout <<	"Rank: " << i+1 << endl;
			cout << "Matches played: " << vec[i].matches_played << endl;
			cout << "Wins: " << vec[i].win << endl;
			cout << "Draws: " << vec[i].draw << endl;
			cout << "Losts: " << vec[i].lost << endl;
			cout << "Goals scored: " << vec[i].scored << endl;
			cout << "Goals conceded: " << vec[i].conceded << endl;
			cout << "Goal difference: " << vec[i].difference << endl;
			cout << "Points: " << vec[i].point << endl;
			flag3 = false;
		}
	}
	if(flag3)
		cout << "There is no such team!" << endl;
	return 0;
}