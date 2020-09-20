#include <iostream>
#include <string>			
#include <vector>

#ifndef _MPQ_H
#define _MPQ_H

using namespace std;

struct structure
{
	int value;
	int label;


	structure (int v=0, int l=0)		
		: value(v), label(l)			
	{}
};

class MPQ
{
public:
	MPQ(int capa);								//"capa" is the int value that is to be our capacity
	~MPQ();
	void insert(int val, int lab);				
	int Remove(int lab);						
	int GetMax();								
	bool IsEmpty();
	void percolateDown(int hole);

private:
	int currentSize;
	int capacity;
	structure* heapArray;						//dynamically allocation for the array
	int* locationArray;
};

MPQ::MPQ(int capa)								//constructor
{
	capacity = capa;
	currentSize = 0;							
	heapArray = new structure[capacity];		//creating a heapArray with dynamically allocation
	locationArray = new int[capacity];			//creating a locatinArray with dynamically allocation
}

MPQ::~MPQ()										//destructor
{
	
	if(!IsEmpty())
	{
		delete[] heapArray;						
	}
	if(!IsEmpty())
	{
		delete[] locationArray;
	}
}

void MPQ::insert(int val, int lab)				//insertion
{
	int hole = ++currentSize;
	for(; hole>1 && val > heapArray[hole/2].value; hole /= 2)
	{
		heapArray[hole].value = heapArray[hole/2].value;
		heapArray[hole].label = heapArray[hole/2].label;
		locationArray[heapArray[hole].label] = hole;
	}
	heapArray[hole].value = val;
	heapArray[hole].label = lab;
	locationArray[lab] = hole;
}

int MPQ::Remove(int label)						//remove
{
	heapArray[locationArray[label]].value = heapArray[currentSize].value;
	heapArray[locationArray[label]].label = heapArray[currentSize].label;
	currentSize -= 1;
	percolateDown(locationArray[label]);
	return locationArray[label];
}

int MPQ::GetMax()
{
	if(!IsEmpty())
		return heapArray[1].value;					
	return 0;
}

bool MPQ::IsEmpty()
{
	if(currentSize==0)
		return true;
	return false;
}

void MPQ::percolateDown(int hole)
{
	int child;
	int tempVal = heapArray[hole].value;				
	int tempLab = heapArray[hole].label;				

	for(; hole*2 <=currentSize; hole = child)
	{
		child = hole*2;
		if(child != currentSize && heapArray[child+1].value > heapArray[child].value)
			child++;
		if(heapArray[child].value > tempVal)
		{
			heapArray[hole].value = heapArray[child].value;
			heapArray[hole].label = heapArray[child].label;
			locationArray[heapArray[hole].label] = hole;
		}
		else
			break;
	}
	heapArray[hole].value = tempVal;
	heapArray[hole].label = tempLab;
	locationArray[heapArray[hole].label] = hole;
}

#endif _MPQ_H