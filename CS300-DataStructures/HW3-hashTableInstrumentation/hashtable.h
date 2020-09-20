#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>

#define SIZE 3011

using namespace std;

class hashtable
{
public:
	hashtable();
	bool insertion(int num, int & probingcounter);
	bool deletion(int num, int & probingcounter);
	bool find(int num, int & probingcounter);
	int getCurrentSize();		//getter - to access the currentSize in the main which is private data

	enum PartType {EMPTY, ACTIVE, DELETED};

private:
	struct HashPart
	{
		int number;
		PartType info;
	};
	int currentSize;
	vector<HashPart> hashvec;		

};

//hash function
int hashfunc(int num)
{
	return num % SIZE;
}

hashtable::hashtable()
{
	vector<HashPart> hashvect(SIZE);
	hashvec = hashvect;
	currentSize = 0;
}

bool hashtable::deletion(int num, int & probingcounter)
{
	probingcounter = 0;
	int hashvecSize = hashvec.size();		
	int i = hashfunc(num);
	int temp = hashfunc(num);
	int checker = 0;

	for(i; hashvec[i].info != EMPTY && i < hashvecSize; i++)
	{
		if(hashvec[i].number == num && hashvec[i].info != DELETED)
		{
			hashvec[i].info = DELETED;
			currentSize--;
			return true;			//silinecek �ey listede var ve ba�ar�yla silindi
		}
		if(i == hashvecSize-1)	//listenin ba��na yolluyor aramay� devam ettirmek i�in
		{
			checker++;					
			if(checker == 2)			//e�er buraya ikinci defa girdiyse, kesinlikle hash table � dola�m��t�r bir kere!
				return false;
			i=-1;
			hashvecSize = temp;		
		}
		probingcounter++;
	}
	return false;
}

bool hashtable::find(int num, int & probingcounter)
{
	probingcounter = 0;
	int hashvecSize = hashvec.size();			
	int i = hashfunc(num);
	int temp = hashfunc(num);
	int checker = 0;

	for(i; hashvec[i].info != EMPTY && i < hashvecSize; i++)
	{
		if(hashvec[i].number == num && hashvec[i].info != DELETED)
		{
			return true;
		}
		if(i == hashvecSize-1)
		{
			checker++;					
			if(checker == 2)			//e�er buraya ikinci defa girdiyse, kesinlikle hash table � dola�m��t�r bir kere!
				return false;
			i=-1;
			hashvecSize = temp;
		}
		probingcounter++;
	}
	return false;
}

bool hashtable::insertion(int num, int & probingcounter)
{
	int hashvecSize = hashvec.size();		//global yap�labilir ��nk� sabit
	int i = hashfunc(num);
	int temp = hashfunc(num);
	int checker = 0;
	probingcounter = 0;					//ka� defa probing yap�ld���n� bulmak i�in
	bool isDeleted = false;
	int tempIndex;

	for(i; hashvec[i].info != EMPTY && i < hashvecSize; i++)
	{
		if(hashvec[i].number == num)
			return false;				//faillad�m, ��nk� insert edece�im say� zaten hashtable da

		if(hashvec[i].info == DELETED && isDeleted == false)
		{
			tempIndex = i;
			isDeleted = true;
		}

		if(i == hashvecSize-1)
		{
			checker++;
			if(checker == 2)
				return false;
			i=-1;
			hashvecSize = temp;
		}
		probingcounter++;
	}

	if(isDeleted == true)
	{
		hashvec[tempIndex].number = num;
		hashvec[tempIndex].info = ACTIVE;
		currentSize++;
		return true;
	}
	else
	{
		hashvec[i].number = num;		//bo�sa direk koyabilirim say�y�
		hashvec[i].info = ACTIVE;
		currentSize++;
		return true;
	}
}

int hashtable::getCurrentSize()
{
	return currentSize;
}

#endif