#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

void intro();
void options();
void currentOrder();
void menu();
void changeQuantity();
void removeItem();
void payPrintReceipt();
void removeAllItems();
void exit();
void dailySales();
char option;
int main()
{
	intro();

	options();
}

void intro()
{
	cout << "\t************************\t" << endl;
	cout << "\t* Welcome to Book Cafe *\t" << endl;
	cout << "\t************************\t" << endl;

	/*char customerName[200];
	cout << "\n\n";
	cout << "Enter customer's name : ";
	cin >> customerName;
	cout << endl;*/
}

void options()
{

	{
		cout << "\t************************\t" << endl;
		cout << "\t* Welcome to Book Cafe *\t" << endl;
		cout << "\t************************\t" << endl;
		int option;
		cout << "\t [1] Show the current order\n ";
		cout << "\t [2] Show the restaurant's menu\n ";
		cout << "\t [3] Change the quantity\n ";
		cout << "\t [4] Remove an item from order\n ";
		cout << "\t [5] Pay and print receipt\n ";
		cout << "\t [6] Remove all item\n ";
		cout << "\t [7] Exit programme\n ";
		cout << "\t [8] Show the daily sales\n ";
		cout << "\n\t Enter option : ";
		cin >> option;
		cout << option;
		cout << endl;

		switch (option) {
		case 0:
			break;
		case 1:
			currentOrder();
			break;
		case 2:
			cout << "here";
			menu();
			break;
		case 3:
			changeQuantity();
			break;
		case 4:
			removeItem();
			break;
		case 5:
			payPrintReceipt();
			break;
		case 6:
			removeAllItems();
			break;
		case 7:
			cout << "\n\t Thank You And Come Again \n";
			break;
		case 8:
			dailySales();
			break;

		}
		//else
		//{
		//cout << "\n\t Invalid code \n";
		//}
	}
	/*else {
		(option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8);
	}*/
}

void currentOrder()
{
	cout << " Place your order first ";
}

void menu()
{
	cout << "here";
	string line;
	ifstream infile("Menu.txt");
	
	if (infile.is_open()) {
		while(getline(infile,line)){

			
			cout << line << '\n';
			
		}
		
	}else{
		
		cout << "file does not exist\n";
		exit(1);
	}
	double price;
	string str;
	infile >> str >> price;
	cout << "Please choose your order" << endl;
	cout << "Menu:" << endl;
	cout << str << "\t" << price << endl;

}

void changeQuantity()
{

}

void removeItem()
{

}

void payPrintReceipt()
{

}

void removeAllItems()
{

}

void dailySales()
{

}



