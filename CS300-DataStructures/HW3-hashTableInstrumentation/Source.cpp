#include <iostream>
#include <string>
#include <stdlib.h>
#include "hashtable.h"
#include <ostream>		
#include <fstream>

#define ARRAY_SIZE 3012

using namespace std;

//Berk Türetken, 24222, CS300-HW3 Hash Table Instrumentation, 04.12.2018

struct arrayPart
{
	int probeCount;
	int transactCount;

	arrayPart(int a=0, int b=0)
		:probeCount(a), transactCount(b)
	{}
};

int main()
{
	ofstream out_ins_suc;
	ofstream out_ins_fail;
	ofstream out_del_suc;
	ofstream out_del_fail;
	ofstream out_find_suc;
	ofstream out_find_fail;

	hashtable hashT;

	arrayPart arrInsSuc[ARRAY_SIZE];		//array of insertion success	

	arrayPart arrInsFail[ARRAY_SIZE];		//array of insertion fail	

	arrayPart arrDelSuc[ARRAY_SIZE];		//array of deletion success	

	arrayPart arrDelFail[ARRAY_SIZE];		//array of deletion fail	

	arrayPart arrFindSuc[ARRAY_SIZE];		//array of finding success	

	arrayPart arrFindFail[ARRAY_SIZE];		//array of finding fail
	
	int in=2, d=1, f=5;			//the cases in the hw are inserted here
	int totaltransact = 0;		//total transaction ý tutabilmek için
	int randNum, randNum2;

	while(hashT.getCurrentSize() < ARRAY_SIZE-1 && totaltransact < 1000000 )
	{
		int probingcounter = 0;							
		int prevCurSize = hashT.getCurrentSize();
		
		randNum = rand() % 8;

		if(randNum >=0 && randNum <= in-1)				
		{
			randNum2 = rand();
			randNum2 = randNum2 % 10000000;
			if(hashT.insertion(randNum2, probingcounter) == true)
			{
				arrInsSuc[prevCurSize].probeCount += probingcounter;
				arrInsSuc[prevCurSize].transactCount += 1;
			}
			else
			{
				arrInsFail[prevCurSize].probeCount += probingcounter;
				arrInsFail[prevCurSize].transactCount += 1;
			}
		}

		else if(randNum >= in && randNum <= in+d-1)
		{
			randNum2 = rand();
			randNum2 = randNum2 % 10000000;
			if(hashT.deletion(randNum2, probingcounter) == true)
			{
				arrDelSuc[prevCurSize].probeCount += probingcounter;
				arrDelSuc[prevCurSize].transactCount += 1;
			}
			else
			{
				arrDelFail[prevCurSize].probeCount += probingcounter;
				arrDelFail[prevCurSize].transactCount += 1;
			}
		}

		else
		{
			randNum2 = rand();
			randNum2 = randNum2 % 10000000;
			if(hashT.find(randNum2, probingcounter) == true)
			{
				arrFindSuc[prevCurSize].probeCount += probingcounter;
				arrFindSuc[prevCurSize].transactCount += 1;
			}
			else
			{
				arrFindFail[prevCurSize].probeCount += probingcounter;
				arrFindFail[prevCurSize].transactCount += 1;
			}
		}
		totaltransact++;
	}
	//for debugging
	//cout << "It is done correctly" << endl;

	/***** STARTING TO WRITE THE DATAS TO THE FILE *****/

	out_ins_suc.open("Insert-Success.txt");
	double average, loadfactor;

	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrInsSuc[i].transactCount != 0)
		{
			average = double(arrInsSuc[i].probeCount) / arrInsSuc[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_ins_suc << loadfactor << ';' << average << endl;
		}
	}

	out_ins_fail.open("Insert-Fail.txt");
	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrInsFail[i].transactCount != 0)
		{
			average = double(arrInsFail[i].probeCount) / arrInsFail[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_ins_fail << loadfactor << ';' << average << endl;
		}
	}

	out_del_suc.open("Delete-Success.txt");
	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrDelSuc[i].transactCount != 0)
		{
			average = double(arrDelSuc[i].probeCount) / arrDelSuc[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_del_suc << loadfactor << ';' << average << endl;
		}
	}

	out_del_fail.open("Delete-Fail.txt");
	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrDelFail[i].transactCount != 0)
		{
			average = double(arrDelFail[i].probeCount) / arrDelFail[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_del_fail << loadfactor << ';' << average << endl;
		}
	}

	out_find_suc.open("Find-Success.txt");
	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrFindSuc[i].transactCount != 0)
		{
			average = double(arrFindSuc[i].probeCount) / arrFindSuc[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_find_suc << loadfactor << ';' << average << endl;
		}
	}

	out_find_fail.open("Find-fail.txt");
	for(int i=0; i < ARRAY_SIZE; i++)
	{
		if(arrFindFail[i].transactCount != 0)
		{
			average = double(arrFindFail[i].probeCount) / arrFindFail[i].transactCount;
			loadfactor = double(i) / ARRAY_SIZE;
			out_find_fail << loadfactor << ';' << average << endl;
		}
	}
	
	return 0;
}