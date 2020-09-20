#include <iostream>
#include <string>

using namespace std;
// berk turetken

void display(string totalname, double totalcost) // displaying the messages and totalcost according to the bill amount
{
	
	if (totalcost == 49) // while totalcost is equal to the basecost
	{
		cout << totalname << ", total cost of your phone usage is " << totalcost << " TL." << " You did not exceed your base package.";
	}
	else if (totalcost > 49 && totalcost < 100) // while totalcost is between basecost and 100 TL
	{
		cout << totalname << ", total cost of your phone usage is " << totalcost << " TL." << " You exceeded your base package.";
	}
	else if (totalcost >= 100) // while totalcost is larger or equal to the 100 TL
	{
		cout << totalname << ", total cost of your phone usage is " << totalcost << " TL." << " You exceeded your base package too much."
			<<	" We suggest you to change your base package.";
	}
}

void calculationBill(int minute, int sms, int internet, int addCall, int addSms, int addInternet, string totalname)
{
	
	int basecost = 49; // defining the basecost as 49 TL if the user spends her/his base package requirements
	double totalcost, totalminute, totalsms, totalinternet;
	
	if (minute > 500 + addCall * 250)					/* if the person buys an additional package
	and exceeds also his/her minutes additional package's minutes, below equation works */
	{
		totalminute = (minute - (500 + 250 * addCall) ) * (0.66) + (addCall * 12);
	}
	else if (minute <= 500 + addCall * 250)				/* if the person buys an additional package 
	and does not exceed the additional package's minutes, below equation works */	
	{
		totalminute = addCall * 12;
	}


	if (sms > 1000 + addSms * 250)						/* if the person buys an additional package
	and exceeds also his/her additional package's SMSs, below equation works */
	{
		totalsms = (sms - (1000 + 250 * addSms) ) * (0.55) + (addSms * 12);
	}
	else if (sms <= 1000 + addSms * 250)				/* if the person buys an additional package 
	and does not exceed the additional package's minutes, below equation works */
	{
		totalsms = addSms * 12;
	}
	

	if (internet > 3072 + addInternet * 1024)			/* if the person buys an additional package
	and exceeds also his/her additional package's MBs, below equation works */
	{
		totalinternet = (internet - (3072 + 1024 * addInternet) ) * (10.24) + (addInternet * 12);
	}
	else if ( internet <= 3072 + addInternet * 1024)	/* if the person buys an additional package 
	and does not exceed the additional package's minutes, below equation works */
	{
		totalinternet = addInternet * 12;
	}
	
	totalcost = totalminute + totalsms + totalinternet + basecost;	

	display(totalname, totalcost);
}
	

bool checker(int x, string totalname, string service)
{
	if(x >= 0)  // checking whether the minutes, SMSs and MBs have valid values
	{
		return true;
	}
	else
	{
		cout << totalname << ", " << service << " cannot be smaller than 0.";
		return false;
	}
}


void fundamental(string totalname)
{

	int minute, sms, internet, addCall, addSms, addInternet;
	cout << totalname << ", please enter how many minutes you used this month: ";
	cin >> minute; 
	if (checker(minute, totalname, "number of minutes" ))		/*sending the minutes to the checker function to check whether
	it is valid or invalid, and then continues if it is valid */
	{
		cout << totalname << ", please enter how many SMSs you sent this month: ";
		cin >> sms;
		if (checker(sms, totalname, "number of SMSs"))			/*sending the SMSs to the checker function to check whether
	it is valid or invalid, and then continues if it is valid */
		{
			cout << totalname << ", please enter how many MBs you used this month: ";
			cin >> internet;
			if (checker(internet, totalname, "internet usage")) /*sending the MBs to the checker function to check whether
	it is valid or invalid, and then continues if it is valid */
			{
				cout << totalname << ", please specify how many additional packages you bought for calls, SMS and internet in this order: ";
				cin >> addCall >> addSms >> addInternet;
				calculationBill(minute, sms, internet, addCall, addSms, addInternet, totalname);
			}		
		}
	}
}

int main()
{
	string name, lastname, totalname;
		
	cout << "Please enter your name: ";
	cin >> name >> lastname;
	totalname = name + " " + lastname + " ";	//merging the first name and surname
	fundamental(totalname);

	cout << endl << "Please enter your name: ";
	cin >> name >> lastname;
	totalname = name + " " + lastname;  //merging the first name and surname
	fundamental(totalname);

	cin.ignore();
	cin.get();
	return 0;
}