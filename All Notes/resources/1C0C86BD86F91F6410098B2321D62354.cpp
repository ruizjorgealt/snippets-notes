/*Define a structure called Stock with symbol (string), price 
(double) and quantity (int) as its  members.
Write an add function which takes a pointer (first) and 
dynamically creates a Stock linking it to an existing linked 
list and assigning first to the newly allocated node and 
reading from the user the stock information.
Write a display function which takes the first pointer and 
displays all Stock symbols, their prices and the quantity owned.
Write a delete function which takes the first pointer and a 
stock symbol and deletes it from the list.
Write a total_value function which takes the first pointer and 
returns the total value of all stocks owned (sum of the 
quantity x price for all stocks)

In main, have the user add as many stocks as desired, ask if 
any is to be deleted and then display all stocks followed by 
the total value of all stocks owned.
*/
#include <iostream>
#include <string>
//#include <conio>
using namespace std;

struct Stock
{
	string symbol;
	double price;
	int quantity;
	Stock* next;
};
void add(Stock**);
void display(Stock*);
void erase(Stock**, string);
double get_total(Stock*);
int main()
{
	Stock* first = 0;
	char reply;
	string symbol;

	cout << "Add a stock? [y/n]: ";
	cin >> reply;
	while(reply == 'y' || reply == 'Y')
	{
		add(&first);
		cout << "Add a stock? [y/n]: ";
		cin >> reply;
	}
	display(first);

	cout << "\nEnter a stock symbol to delete or hit Enter if "
		 << "none is to be deleted.";
	cin.ignore();
	getline(cin, symbol);
	if(symbol != "")
		erase(&first, symbol);
	display(first); 
	cout << "\nTotal value is " << get_total(first);
	cout << "\nPress any key to continue.";
	_getch();
	return 0;
}
void add(Stock**pfirst)
{
	Stock* p;
	if(*pfirst == 0)
	{
		*pfirst = new Stock;
		(*pfirst)->next = 0;
	}
	else
	{
		p = new Stock;
		p->next = *pfirst;
		*pfirst = p;
	}
	cout << "\nEnter symbol: ";
	cin >> (*pfirst)->symbol;
	cout << "\nEnter price: ";
	cin >> (*pfirst)->price;
	cout << "\nEnter quantity: ";
	cin >> (*pfirst)->quantity;

}
void display(Stock* first)
{
	do
	{
		cout << first->symbol << ' '
			 << '$' << first->price << ' '
			 << first->quantity << endl;
		first = first->next;
	}while(first);
}
void erase(Stock** pfirst, string sym)
{
	Stock *tmp, *p;

	if(sym == (*pfirst)->symbol) //if first is to be deleted
	{
		tmp = (*pfirst)->next;
		delete *pfirst;
		*pfirst = tmp;
	}
	else if(sym == (*pfirst)->next->symbol) //if second is to be deleted
	{
		tmp = (*pfirst)->next;
		(*pfirst)->next = tmp->next;
		delete tmp;
	}
	else
	{   //advance to correct position
		for(p = *pfirst; p->next->next != 0 && sym != p->next->symbol; p = p->next) 
			;
		
		if(sym == p->next->symbol)
		{
			tmp = p->next;
			p->next = tmp->next;
			delete tmp;
		}
	}
}
double get_total(Stock* first)
{
	double total = 0;
	for(Stock* p = first; p != 0; p = p->next)
		total += p->price * p->quantity;
	return total;
}