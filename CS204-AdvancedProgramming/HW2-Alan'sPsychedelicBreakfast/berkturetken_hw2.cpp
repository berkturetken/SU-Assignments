#include <iostream>
#include <string>
#include "strutils.h"
#include <sstream>

using namespace std;

//Berk Türetken --- 13.07.2018

struct node  //the structure is suitable for doubly circular linked list
{
	string Item;
	int Quantity, EstPrice, total;
	node *prev;
	node *next;
};
node * head = NULL; 
node * tail = NULL;


bool DeleteList(node *& head, string item)	//deleting any node that user wants to delete
{
	bool flag = false;

	if(head == NULL)						//if there is no information in the node
		return flag;

	else if (head->Item == item)			//if user wants to delete the head node
	{
		node * temp = head;
		if(head == tail)					//this case is about the head == tail, i.e. there is only one node
		{
			flag = true;
			delete temp;
			head = NULL;
		}
		else								//if there are more than one node
		{
			flag = true;
			tail->next = head->next;
			head = head->next;
			head->prev = tail;
			delete temp;
		}
		return flag;
	}
	else if (tail->Item == item)			//if user wants to delete the head node
	{
		flag = true;
		node * temp = tail;
		head->prev = tail->prev;
		tail = tail->prev;
		tail->next = head;
		delete temp;
		return flag;
	}
	else									//remaining conditions (i.e. if the node is in the middle of the list)
	{
		node * temp = head->next;
		node * ptr;
		while(temp != head)
		{
			if(temp->Item == item)
			{
				flag = true;
				ptr = temp;
				ptr->prev->next = ptr->next;
				ptr = ptr->next;
				ptr->prev = temp->prev;
				delete temp;
				return flag;
			}
			temp = temp->next;
		}
	}
	return flag;
}

void Insertion(node *& head, string item, int quan)		//adding any node that user wants to add
{
	int price;
	bool deletion = false;
	bool found = false;
	bool flag = false;
	node * str = head; 
	int newQuan = 0, oldprice, oldQuan;

	if(head!=NULL)
	{
		do{											//checking whether the node is new or already exist
			if(str->Item == item)
			{
				oldprice = str->EstPrice;			//store the price to use it later
				oldQuan = str->Quantity;			//store the quantity to use it later
				newQuan = str->Quantity + quan;		//adding the quantity to the old quantity
				DeleteList(head, item);
				deletion = true;
			}
			str = str->next;		
		}while(str != head && deletion == false);
	}
	if(deletion==true)								//if the node is already exist, this if works to update the data
	{
		quan = newQuan;
		price = oldprice;
		node*temp = new node;
		temp->Item = item;
		temp->Quantity = quan;
		temp->EstPrice = price;
		temp->total = quan*price;
		str = head;

		cout << "---" << endl;
		cout << "The quantity of the item " << item << " is increased by " << quan-oldQuan << ". The final quantity is " << quan << "." << endl;
		flag = true;								//not to write the same cout statement, the flag is used
	}
	if(deletion == false){							//if the node is new, this if works and asks to the user to input the price
		cout << "Enter estimated price for the item: ";
		cin >> price;
	}

	if(head == NULL)								//for the case that the list is empty
	{
		node * temp = new node;						//creating a new node and fill it up with proper informations
		temp->Item = item;
		temp->Quantity = quan;
		temp->EstPrice = price;
		temp->total = quan * price;

		temp->next = temp;							//make some connections
		temp->prev = temp;							//since it is the only node, it is both head and tail
		head = temp;
		tail = head;
	}
	else											//for the case that the list is not empty
	{
		node*temp = new node;						//creating a new node and fill it up with proper informations
		temp->Item = item;
		temp->Quantity = quan;
		temp->EstPrice = price;
		temp->total = quan*price;
		str = head;

		do{											//checking whether the new node's total price(quan*price) is equal to any node in the list or not
			if(str->total == quan*price)
			{
				if(str == head)						// 1.CASE => the new node's total price is equal to the head node's total price
				{
					if(str->Item > item)			// i.e (1.1) => sausages > biscuit
					{
						temp->next = head;			//make the arrangements between related nodes
						head->prev = temp;
						head = temp;
						head->prev = tail;
						tail->next = head;
						found = true;
					}
					else if(str->Item < item)		// i.e. (1.2) => sausages < sweet
					{
						temp->next = str->next;		//make the arrangements between related nodes
						temp->prev = str;
						str->next->prev = temp;
						str->next = temp;
						found = true;
					}
				}
				else if(str == tail)				// 2.CASE => the new node's total price is equal to the tail node's total price
				{
					if(str->Item > item)			// i.e. (2.1) => bread > ashoura(aþure)
					{
						temp->next = str;			//make the arrangements between related nodes
						temp->prev = str->prev;
						str->prev->next = temp;
						str->prev = temp;
						found = true;
					}
					else if(str->Item < item)		// i.e. (2.2) => bread < orange juice
					{
						tail->next = temp;			//make the arrangements between related nodes
						temp->prev = tail;
						tail = temp;
						head->prev = tail;
						tail->next = head;
						found = true;
					}
				}
				else								// 3.CASE => the new node's total price is equal to the any node's total price between head and tail node
				{
					if(str->Item > item)			// i.e. (3.1) => coffee > biscuit
					{
						temp->next = str;			//make the arrangements between related nodes
						temp->prev = str->prev;
						str->prev->next = temp;
						str->prev = temp;
						found = true;
					}
					else if(str->Item < item)		// i.e. (3.2) => sausages < sweeet
					{			
						temp->next = str->next;		//make the arrangements between related nodes
						temp->prev = str;
						str->next->prev = temp;
						str->next = temp;
						found = true;
					}
				}
			}
			str = str->next;
		}while(str != head && found == false);


		if(found == false)							//if there is no equality (total prices) between two nodes then found should be "false" and this if works!
		{
			if( tail->total > (quan * price) )		// 1.CASE => if the new node is smaller than the tail node
			{
				tail->next = temp;					//make the arrangements between related nodes
				temp->prev=tail;
				tail = temp;
				head->prev = tail;
				tail->next = head;
			}

			if( head->total < (quan * price) )		// 2.CASE => if the new node is greater than the tail node
			{
				temp->next = head;					//make the arrangements between related nodes
				head->prev = temp;		
				head = temp;
				head->prev = tail;
				tail->next = head;
			}

			else if( (head->total > quan*price) && (tail->total < quan*price) )		// 3.CASE => if the new node is smaller than head node and greater than tail node
			{
				bool flag = true;
				node * ptr = head;
				do{									//traversing the list to find a "proper" place for the new node in the list
					if(ptr->total > quan*price)
					{
						ptr = ptr->next;
					}
					else
						flag = false;
				}while(ptr!=head && flag);

				temp->next = ptr;					//make the arrangements between related nodes
				temp->prev = ptr->prev;
				ptr->prev->next = temp;
				ptr->prev = temp;
			}
		}
	}
	if(flag == false)								//if flag is still false then the node is for sure new node and print the proper cout statement
	{
		cout << "---" << endl;
		cout << "The item " << item << " of quantity " << quan << " is added to the list." << endl;
	}

}

void PrintList(node *& head)						//printing the whole list in a regular manner
{
	if(head != NULL)
	{
		cout << "Item: " << head->Item << endl;
		cout << "Quantity: " << head->Quantity << endl;
		cout << "Est. Price: " << head->EstPrice << endl;
		cout << "---" << endl;
		node * temp = head->next;
		while ( temp != head)						//traversing the list until it reaches the head again
		{
			cout << "Item: " << temp->Item << endl;
			cout << "Quantity: " << temp->Quantity << endl;
			cout << "Est. Price: " << temp->EstPrice << endl;
			cout << "---" << endl;
			temp = temp->next;
		}
	}
	else											//this is the case when there is nothing in the list
	{
		cout << "The shopping list is empty." << endl; 
		cout << "---" << endl;
	}
}

void PrintReverseList(node *& head)					//printing the whole list in a reverse manner
{
	if(head != NULL)
	{

		cout << "Item: " << tail->Item << endl;
		cout << "Quantity: " << tail->Quantity << endl;
		cout << "Est. Price: " << tail->EstPrice << endl;
		cout << "---" << endl;
		node * temp = tail->prev;
		while(temp != tail)							//traversing the list until it reaches the tail again
		{
			cout << "Item: " << temp->Item << endl;
			cout << "Quantity: " << temp->Quantity << endl;
			cout << "Est. Price: " << temp->EstPrice << endl;
			cout << "---" << endl;
			temp = temp->prev;
		}
	}
	else											//printing the whole list in a reverse manner									
	{
		cout << "The shopping list is empty." << endl;	
		cout << "---" << endl;
	}

}

void totalEstimation(node *& head)					//calculating the kinds and total price of the things in the list
{
	int priceall = 0, counter = 0;
	node * temp = head;

	do{												//traversing whole list
		if(head != NULL)
		{
			priceall = priceall + temp->total;
			counter++;	
			temp = temp->next;
		}
	}while(temp != head);

	cout << "The total estimated price of " << counter << " kinds of items is: " << priceall << endl;
	cout << "---" << endl;
}

void menu()															//option part for Alan's choices
{
	cout << "MENU" << endl;
	cout << "1. Add item to the shopping list" << endl;
	cout << "2. Delete item from the shopping list" << endl;
	cout << "3. Print the shopping list" << endl;
	cout << "4. Print the shopping list in reverse order" << endl;
	cout << "5. Show total estimated cost of the list" << endl;
	cout << "6. Exit" << endl;
	cout << "---" << endl;
	cout << "Enter your choice: ";
}

int main()
{
	string word, item, line, fullitem, deleteword;
	int input = 0, quan;

	cout << "This program helps Alan with gathering the shopping list for his psychedelic breakfast." << endl;
	cout << "---" << endl;

	menu();
	while(cin >> word)
	{
		cout << "---" << endl;	
		if(word.length() == 1)										//if the user inputs "1b", this can be cause a problem since the program uses "atoi"
			input = atoi(word);										//by using word.length(), we avoid from such a problem

		if(input == 1)												//adding option
		{
			cout <<	"Enter name for the item: ";
			cin >> item;
			getline(cin,line);
			fullitem += item + " ";

			istringstream iss(line);
			while(iss >> item)
			{
				fullitem += item + " ";								//adding all the inputs in a proper way
			}
			fullitem = fullitem.substr(0, fullitem.length()-1);		//another option => using "StripWhite"
			ToUpper(fullitem);

			cout << "Enter quantity for the item: ";
			cin >> quan;
			Insertion(head, fullitem, quan);
			cout << "---" << endl;

			fullitem = "";
		}

		else if(input == 2)											//"delete" option
		{
			cout << "Enter an item name to delete from the list: ";
			cin >> deleteword;
			ToUpper(deleteword);
			cout << "---" << endl;

			if(DeleteList(head, deleteword) == true)				//if the word is in the list, the function returns true
				cout << "The item " << deleteword << " is deleted from the list." << endl;
			else
				cout << "The item " << deleteword << " could not be found in the list." << endl;
			cout << "---" << endl;
		}

		else if(input == 3)											//"print" option			
			PrintList(head);

		else if(input == 4)											//"print reverse" option
			PrintReverseList(head);

		else if(input == 5)											//"total price(estimation)" option
			totalEstimation(head);

		else if(input == 6)											//"exit" option
		{
			delete head;											//delete the node, thus we lose the connection to reach the list
			head = NULL;
			cout << "Clearing the shopping list..." << endl;
			cout << "Exiting the program..." << endl;
			return 0;
		}

		else														//if the user inputs something different from "1","2","3","4","5","6"
		{
			cout << "This is not a valid option!" << endl;	
			cout << "---" << endl;
		}

		menu();
	}
	return 0;
}