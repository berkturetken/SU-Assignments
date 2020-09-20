#include <iostream>
#include <string>
#include <thread>
#include "Queue.h"
#include "randgen.h"
#include <sstream>
#include <fstream>
#include <chrono>
#include <mutex>

using namespace std;

/*** Creating "global variables" to be able to inform threads simultaneous***/

int counter = 0;						// the program can check the files which will be enqueued and dequeued by using global variable counter
Queue q, mainQueue;						// q is the first queue that stores the filenames --- mainQueue is the common queue that both producer and consumer threads can chase it
mutex coutmutex, mymutex1, mymutex2;	// coutmutex -> cout statements, mymutex1 -> producer threads, mymutex2 -> consumer threads

void consumer(int & thrNum)			// for the consumer thread
{
	string filename;
	char ch, letter, maxChar, holder;
	int shiftAmount;

	/*****
		there are 2 conditions ---------
		1) there are files but they are not enqueued yet   
		2) there are no files left
		The problem is handled by using these two conditions with or operator! 
	*****/

	while(counter >= 0 || !mainQueue.isEmpty())
	{
		int maxOccur=0, cnt = 0;
		RandGen gen;
		int number = gen.RandInt(2500, 3500);		// creating a random number between 2500 and 3500 to sleep threads 

		coutmutex.lock();
		cout << "Consumer Thread - " << thrNum << " starts sleeping for " << number << " miliseconds" << endl;
		coutmutex.unlock();

		this_thread::sleep_for(chrono::milliseconds(number));		// thread is sleeping

		mymutex2.lock();
		if(!mainQueue.isEmpty())			// if the file is not empty
		{
			mainQueue.dequeue(filename);
			mymutex2.unlock();
			ifstream input;
			input.open(filename.c_str());

			coutmutex.lock();
			cout << "Consumer Thread - " << thrNum << " is now handling \"" << filename << "\"" << endl;
			coutmutex.unlock();

			if(!input.fail())		// if there is no problem while opening the file
			{
				string newfn = filename.substr(0, filename.find("."));	// creating a new file name to cut the "fileX" part of the "fileX.txt"	

					// finding the most common character in the file -- I got some help from the internet for this algorithm :) (i.e. stackoverflow)
				for(ch = 'a'; ch <='z'; ch++)
				{
					cnt=0;
					while(input.get(letter))
					{
						if(letter == ch)
							cnt++;
					}
					if ( cnt > maxOccur)
					{
						maxOccur = cnt;
						maxChar = ch;
					}
					input.clear();
					input.seekg(0);
				}
				shiftAmount = maxChar - 'e';		// determining the shift amount by subtracting from character "e"
				ofstream output;
				output.open((newfn+"_decrypted.txt").c_str());	// opening the new decrypted file

				/***** Decryption Algorithm starts *****/
				while(input.get(letter))	// reading char by char
				{
					if(letter >= 'a' && letter  <= 'z')		//if the character is a letter which can be decrypted
					{
						holder = letter-shiftAmount;			// holder is just a mediator (aracý deðiþken), for now!
						if(holder < 'a')						// if the letter (I mean holder) is smaller than 'a' ( smaller than 97 in ascii table)
							holder = holder + ('z' - 'a') + 1;	//apply this part! -> bringing the holder in appropriate range and holder is now in the final form!
						else if (holder > 'z')					// if the letter (I mean holder) is greater than 'z' ( greater than 122 in ascii table)
							holder = holder - ('z' - 'a') - 1;	//apply this part! -> bringing the holder in appropriate range and holder is now in the final form!

						output << holder;
					}
					else					// if the holder is already in the range
						output << letter;
				}
				output.close();			// just not to cause any crash

				coutmutex.lock();
				cout << "Consumer Thread - " << thrNum << " done handling \"" << filename << " \"" << " with a shift of " << shiftAmount << " and written the result to \"" << newfn << "_decrypted.txt" << " \"" << endl;
				coutmutex.unlock();
			}
			else		// if there is a problem while opening the file!!!
			{
				coutmutex.lock();
				cout << "Consumer Thread - " << thrNum << " cannot process \"" << filename << " \", there is no such file!" << endl;
				coutmutex.unlock();
			}
		}
		else		// if the file is empty!!!
		{
			mymutex2.unlock();
			if(counter >= 0)
			{
				coutmutex.lock();
				cout << "Consumer Thread - " << thrNum << " cannot find any file to dequeue for now." << endl;
				coutmutex.unlock();
			}
		}
	}
	// when the counter is smaller than 0 meaning there is no file to dequeue, printing appropriate message
	coutmutex.lock();
	cout << "Consumer Thread - " << thrNum << " cannot find any file to dequeue, joining..." << endl;
	coutmutex.unlock();
}

void producer(int & thrNum)			// for the producer threads
{
	string filename;

	while(counter >= 0)								// if there is a file to be dequeued, then while condition works
	{
		RandGen random;
		int num = random.RandInt(1000,4000);		// creating a random number between 1000 and 4000 to sleep threads 

		coutmutex.lock();							// all the time lock the cout statement before it is executed (this is valid for the entire program)
		cout << "Producer Thread - " << thrNum << " starts sleeping for " << num << " miliseconds" << endl; 
		coutmutex.unlock();							// all the time unlock the cout statement after it is executed 

		this_thread::sleep_for(chrono::milliseconds(num));		// thread is sleeping

		mymutex1.lock();
		if(!q.isEmpty())		// if the file is not empty
		{
			q.dequeue(filename);
			mymutex1.unlock();

			coutmutex.lock();
			cout <<	"Producer Thread - " << thrNum << " is now enqueuing \"" << filename << "\"" << endl;
			coutmutex.unlock();

			mymutex1.lock();			// do we need?
			mainQueue.enqueue(filename);
			counter--;			// updating counter
			mymutex1.unlock();
		}
		else		// if the file is empty
		{
			counter--;			// updating counter
			mymutex1.unlock();

			coutmutex.lock();
			cout << "Producer Thread - " << thrNum << " cannot find any file to enqueue, joining..." << endl;
			coutmutex.unlock();
		}
	}
}

int main()
{
	string str;
	cout << "Please enter a filename: ";
	cin >> str;

	while(str != "-")							// asking for a filename until user inputs "-"
	{
		q.enqueue(str);							// q is the first queue that stores the filenames
		counter++;
		cout << "Please enter a filename: ";
		cin >> str;
	}

	/*** Creating 2 Producer, 3 Consumer Threads ***/
	thread thrProducer(&producer, 1);		
	thread thr2Producer(&producer, 2);
	thread thrConsumer(&consumer, 1);
	thread thr2Consumer(&consumer, 2);
	thread thr3Consumer(&consumer, 3);

	/*** Joining all the threads before the program finishes not to cause any crash ***/
	thrProducer.join();
	thr2Producer.join();
	thrConsumer.join();
	thr2Consumer.join();
	thr3Consumer.join();

	cout << "All threads have joined with main, exiting..." << endl;
	return 0;
}