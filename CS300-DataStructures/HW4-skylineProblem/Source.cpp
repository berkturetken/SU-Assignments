#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>		
#include "MPQ.h"
#include <algorithm>

using namespace std;

//Berk Türetken, 24222, CS300-HW4 Skyline, 19.12.2018

struct resultVecProperty
{
	int coordinate;
	int printHeight;
};

struct buildingProperty
{
	int xcoor;
	int position;
	int height;
	int buildingNumber;

	buildingProperty (int x=0, int p=0, int h=0, int bn=0)
		: xcoor(x), position(p), height(h), buildingNumber(bn)
	{}
};

bool sortXCoor (buildingProperty a, buildingProperty b)
{
	if(a.xcoor != b.xcoor)
		return (a.xcoor < b.xcoor);
	else
		return (a.height < b.height);	
	/*****
	if the coordinates are equal to each other, I sort them according to their heights
	to make the edge case problem easier --> (edge case: if there are more than one
	height value at the same x-coordinate) 
	*****/
}

int main()
{
	string fileName, line;
	ifstream input;
	cout << "Enter the file name: ";
	cin >> fileName;

	input.open(fileName.c_str());
	while(input.fail())									//precaution for openning the fail not correctly
	{
		cout << "Invalid file name!" << endl;
		cout << "Enter a valid file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
	}

	int totalBuilding;									
	input >> totalBuilding;								//reading the first line of the input file --> the number of buildings

	MPQ maxHeap(totalBuilding);								//creating the heap
	vector<buildingProperty> mainVec(totalBuilding*2);		//creating a vector with the size of twice number of buildings
	//since we have left and rigth coordinates

	int i=0, label=1, xcoor1, h, xcoor2;					//h = height, label = buildingNumber
	while(!input.eof())
	{
		buildingProperty tempBuilding;
		input >> xcoor1 >> h;					//reading the first two numbers which is the left coordinate of the building

		tempBuilding.xcoor = xcoor1;
		tempBuilding.position = -2;				// -2 for left coordinates of the building, since we have NO negative coordinates, it is okay!
		tempBuilding.height = h;
		tempBuilding.buildingNumber = label;

		mainVec[i] = tempBuilding;

		input >> xcoor2;						//reading the last number which is the right coordinate of the building
		tempBuilding.xcoor = xcoor2;
		tempBuilding.position = -1;				// -1 for right coordinates of the building, since we have NO negative coordinates, it is okay!

		mainVec[i+1] = tempBuilding;

		label++;
		i += 2;
	}
	std::sort(mainVec.begin(), mainVec.end(), sortXCoor);

	vector<resultVecProperty> coutVector((totalBuilding*2)+1);	//!!!UPDATE!!!	//I used coutVector to output the datas in a proper way
	int j=1, size = mainVec.size();
	int tempMax = INT_MIN;
	for(int i=0; i < size; i++)
	{
		if(i==0 && mainVec[i].xcoor != 0)						//inital check -> if there is no building at x=0, I have to print out "0 0"
		{
			coutVector[0].coordinate = 0;
			coutVector[0].printHeight = 0;
		}
		if(mainVec[i].position == -2)							//means that it is left -> we have to insert
		{
			h = mainVec[i].height;
			label = mainVec[i].buildingNumber;
			maxHeap.insert(h, label);
			if(maxHeap.GetMax() != tempMax)						//if there is a change in height, we have to change and output
			{
				tempMax = h;
				if(coutVector[j-1].coordinate == mainVec[i].xcoor)	//condition for whether there is a more than one building in the same x-coordinate
				{
					coutVector[j-1].printHeight = tempMax;		//update the height
				}
				else											//otherwise, add the new coordinate and height to the coutVector
				{
					coutVector[j].coordinate = mainVec[i].xcoor;	
					coutVector[j].printHeight = tempMax;
					j++;
				}
			}	
		}
		else													//means that it is right -> we have to delete
		{
			h = mainVec[i].height;
			label = mainVec[i].buildingNumber;
			maxHeap.Remove(label);
			if(h == tempMax)							//if there is a change in the height, update the coutVector
			{
				tempMax = maxHeap.GetMax();
				if(coutVector[j-1].coordinate == mainVec[i].xcoor)	//condition for whether there is a more than one building in the same x-coordinate
				{
					coutVector[j-1].printHeight = tempMax;			//update the height
				}
				else												//otherwise, add the new coordinate and height to the coutVector
				{
					coutVector[j].coordinate = mainVec[i].xcoor;
					coutVector[j].printHeight = tempMax;
					j++;
				}
			}
		}
	}

	//printing the first index seperately because I have a condition in the for loop for building coordinates which are equal to 0
	cout << coutVector[0].coordinate << " " << coutVector[0].printHeight << endl;	

	/***** PRINTING THE VISIBLE SKYLINE OF THE CITY *****/
	for(int i=1; i < coutVector.size(); i++)
	{
		if(coutVector[i].coordinate != 0 && coutVector[i].printHeight!=coutVector[i-1].printHeight)		//!!!UPDATE!!!
			cout << coutVector[i].coordinate <<	" " << coutVector[i].printHeight << endl;
	}
	return 0;
}