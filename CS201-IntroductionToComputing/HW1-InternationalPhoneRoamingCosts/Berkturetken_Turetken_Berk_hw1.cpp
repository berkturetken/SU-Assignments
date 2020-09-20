#include <iostream>
#include <string>

using namespace std;
//berk turetken

int main()
{
	string name;
	double price_outgoing, price_incoming, price_internet, internet_usage, price_SMS;
	int minute, SMS;
	double x, y, z, k, total, tax, fee;

	cout << "Please enter your name: ";
	cin >> name;   // the user has to input his/her name

	cout << endl << name << ", please enter the price for outgoing call per minute: ";
	cin >> price_outgoing;
	cout << name << ", please enter how many minutes you have talked in outgoing calls: ";
	cin >> minute;
	
	x = price_outgoing * minute; /* calculating the price for outgoing calls by multiplying "price per minute" and "minute that user talked" by 
	assigning a new variable x */
	cout << name << ", you have spent " << x << " TL for outgoing calls you made while you are abroad." << endl;

	cout << endl << name << ", please enter the price for incoming call per minute: ";
	cin >> price_incoming;
	cout << name << ", please enter how many minutes you have talked in incoming calls: ";
	cin >> minute;

	y = price_incoming * minute; /* calculating the price for incoming calls by multiplying "price per minute" and "minute that user talked" by 
	assigning a new variable y */
	cout << name << ", you have spent " << y << " TL for incoming calls you made while you are abroad." << endl; 

	cout << endl << name << ", please enter the price for internet usage per MB: ";
	cin >> price_internet;
	cout << name <<	", please enter how many GBs you have used: ";
	cin >> internet_usage;

	z = price_internet * 1024 * internet_usage; // converting mb to gb by using the formula 1 gb = 1024 mb
	/* calculating the price for internet usage by multiplying "price per MB" and "GB that user used" by 
	assigning a new variable x */
	cout << name << ", you have spent " << z << " TL for the internet while you are abroad." << endl;
	
	cout << endl << name << ", please enter the price for one SMS: ";
	cin >> price_SMS;
	cout << name << ", please enter the number of SMS you have sent: ";
	cin >> SMS;

	k = price_SMS * SMS;  /* calculating the price for SMS by multiplying "price per SMS" and "SMS that user sent" by 
	assigning a new variable y */
	cout << name << ", you have spent " << k << " TL for the SMS while you are abroad." << endl;

	total = x + y + z + k;  // assigning a new variable "total" for the total services
	tax = total * 0.18;     // multiplying by %18 for the tax
	fee = total + tax;      // adding the tax and total value for the fee with tax

	cout << endl << name << ", total cost for all roaming services is " << total << " TL." << endl;
	cout << name << ", tax is " << tax << " TL." << endl;
	cout << name << ", total roaming bill fee with tax is " << fee << " TL.";
	
	cin.ignore();
	cin.get();
		return 0;
}