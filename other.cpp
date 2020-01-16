#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include<stdio.h>
#include<windows.h>
#include <fstream>
#include<conio.h>
using namespace std;
void showOrder(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice, double& totalPrice,vector<string>& dailyItem, vector<int>& dailyQty, vector<double>& dailyPrice);
void currentOrder(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice);
void changeQuantity(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice);
void removeAllItem(vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice);
void printReceipt(vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice,double& totalPrice);
void removeItem(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice);
int search(vector<string>w, string key);
void dailySales(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice, double& totalPrice, vector<string>& dailyItem, vector<int>& dailyQty, vector<double>& dailyPrice);


int main()
{
	vector<string>menuItem;
	vector<double>menuPrice;
	vector<int>sessionQuantity;

	vector<double>customerOrderPrice;
	vector<int>customerOrderQty;
	vector<string>customerOrderItem;
	vector<double>customerOrder_TotalPrice;

	vector<string>dailyItem;
	vector<int>dailyQty;
	vector<double>dailyPrice;

	double totalPrice ;

	ifstream infile("Menu.txt");
	if (!infile) {
		cout << "File does not exists\n";
		exit(1);
	}
	string food;
	double price;	
	while (!infile.eof()) {
		infile >> food >> price;
		menuItem.push_back(food);
		menuPrice.push_back(price);
		sessionQuantity.push_back(0);
	}
	infile.close();

	int choice = 2;
	cout<<("\n                       :::::::::::::::::::::::::::::::::::::");
	cout<<("\n                       ::                                 ::");
	cout<<("\n                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
	cout<<("\n                       ::     @                     @     ::");
	cout<<("\n                       ::     @       WELCOME       @     ::");
	cout<<("\n                       ::     @      Rainbow's      @     ::");
	cout<<("\n                       ::     @      Restaurant     @     ::");
	cout<<("\n                       ::     @                     @     ::");
	cout<<("\n                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
	cout<<("\n                       ::                                 ::");
	cout<<("\n                       :::::::::::::::::::::::::::::::::::::\n\n");

	while (choice != 8) {
		cout << "1. Current Order\n";
		cout << "2. Show Order\n";
		cout << "3. Change Quantity\n";
		cout << "4. Remove Item\n";
		cout << "5. Pay and Print Receipt\n";
		cout << "6. Remove All Item\n";
		cout << "7. Daily Sales\n";
		cout << "8. Exit\n\n";
		cout << "Please make your choice : ";
		cin >> choice;
		system("CLS");
		//if (choice = 1) {

		switch (choice) {
		case 1:
			currentOrder(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
			break;
		case 2:
			showOrder(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice,totalPrice,dailyItem,dailyQty,dailyPrice);
			system("CLS");
			break;
		case 3:
			changeQuantity(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
			break;
		case 4:
			removeItem(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
			break;
		case 5:
			printReceipt(customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice,totalPrice);
			break;
		case 6:
			removeAllItem(customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
			break;
		case 7:
			dailySales(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice, totalPrice, dailyItem, dailyQty, dailyPrice);
			break;
		case 8:
			return (0);
			break;
		default:
			cout << "Please enter suitable number" << endl;
			break;
		}
	}
}

void showOrder(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice, double& totalPrice, vector<string>& dailyItem, vector<int>& dailyQty, vector<double>& dailyPrice)
{
	cout << setw(21) << "Menu" << setw(16) << "Price" << endl;

	for (int i = 0; i < menuItem.size(); i++) {
		cout << i + 1 << setw(20) << menuItem[i] << fixed << setprecision(2) << setw(15) << menuPrice[i] << endl;
	}
	cout << endl;

	int choose;
	int quantity;
	double totalSesaje;
	char ogy = 'g';
	cout << "\n\nPlease choose your meal: ";
	cin >> choose;
	cout << menuItem[choose - 1] << setw(15) << menuPrice[choose - 1];
	cout << "\nEnter your quantity : ";
	cin >> quantity;
	totalPrice = menuPrice[choose - 1] * quantity;
	string currentItem = menuItem.at(choose - 1);
	double currentItemPrice = menuPrice.at(choose - 1);
	double currentItemtotalPrice = currentItemPrice * quantity;

	customerOrderItem.push_back(currentItem);

	for (int i = 0; i < customerOrderItem.size(); i++) {
		int positionItem = search(customerOrderItem, currentItem);
		if (positionItem == -1) {
			customerOrderQty[i] = customerOrderQty.at(choose - 1) + quantity;
		}
		else
			customerOrderQty.push_back(quantity);
		break;
	}

	customerOrderPrice.push_back(currentItemPrice);
	customerOrder_TotalPrice.push_back(currentItemtotalPrice);

	int newOrder, newQuantity;
	cout << "\nDo you want to add something ? Y/N ";
	cin >> ogy;
	while (ogy != 'N') {
		if (ogy == 'y' || ogy == 'Y') {
			cout << "What you want to add? ";
			cin >> newOrder;
			cout << menuItem[newOrder - 1] << setw(15) << menuPrice[newOrder - 1];
			cout << "\nEnter your quantity : ";
			cin >> newQuantity;
			double rt;
			double newPrice;
			double currentItemPrice = menuPrice.at(newOrder - 1);
			double currentItemtotalPrice = currentItemPrice * newQuantity;

			rt = newQuantity * menuPrice[newOrder - 1];
			totalPrice = rt + totalPrice;

			string itemNewOrder = menuItem.at(newOrder - 1);
			double itemNewPrice = menuPrice.at(newOrder - 1);

			customerOrderItem.push_back(itemNewOrder);
			customerOrderPrice.push_back(currentItemPrice);
			customerOrder_TotalPrice.push_back(currentItemtotalPrice);

			for (int i = 0; i < customerOrderQty.size(); i++) {
				int positionItem = search(customerOrderItem, itemNewOrder);
				if (positionItem == 0) {
					customerOrderQty[i] = quantity + newQuantity;
				}
				else
					customerOrderQty.push_back(newQuantity);
				break;
			}

			cout << "\nDo you want to add something ? Y/N ";
			cin >> ogy;
		}
		else {
			cout << "You entered wrong code !" << endl;
			cout << "Please enter Y or N " ;
			cin >> ogy;
		}
	}
	cout << "Total price =" << totalPrice << endl;
	for (int i = 0; i < customerOrderQty.size(); i++) {
		cout << customerOrder_TotalPrice[i]<<endl;
	}
}


void currentOrder(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice)
{
	if (customerOrderItem.empty()) {
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		cout << setw(21) << "Menu" << setw(16) << "Quantity" << setw(16) << fixed << setprecision(2) << "Price (RM)" << setw(16) << fixed << setprecision(2) << "Total Price" << endl;

		for (int i = 0; i < customerOrderQty.size(); i++) {
			cout << setw(21) << customerOrderItem[i] << setw(16) << customerOrderQty[i] << setw(16) << fixed << setprecision(2) << customerOrderPrice[i] << setw(16) << customerOrder_TotalPrice[i] << endl;
		}
		cout << endl;
		cout << endl;
		double sum=0;
		for (int i = 0; i < customerOrderQty.size(); i++) {
			sum = sum + customerOrder_TotalPrice[i];
		}
		cout << "Total Amount : RM " << sum << endl;
	}
}

void changeQuantity(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice) {
	if(customerOrderItem.empty()){
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		cout << "This is what you ordered " << endl;

		for (int i = 0; i < customerOrderQty.size(); i++) {
			cout << i + 1 << setw(21) << customerOrderItem[i] << setw(16) << customerOrderQty[i] << setw(16) << fixed << setprecision(2) << customerOrderPrice[i] << endl;
		}
		cout << "Please choose what you want to change : ";
		int chooseNew;
		cin >> chooseNew;
		cout << "Please enter new quantity : ";
		int newQty;
		cin >> newQty;
		string orderChangeQty = customerOrderItem.at(chooseNew - 1);
		int positionItem;
		double abu = newQty * customerOrderPrice.at(chooseNew - 1);
		if (newQty == 0) {
			for (int i = 0; i < customerOrderQty.size(); i++) {
				int positionItem = search(customerOrderItem, orderChangeQty);
				if (positionItem != -1) {
					//customerOrderQty.at(chooseNew - 1) = newQty;
					customerOrderItem.erase(customerOrderItem.begin() + (chooseNew - 1));
					customerOrderQty.erase(customerOrderQty.begin() + (chooseNew - 1));
					customerOrderPrice.erase(customerOrderPrice.begin() + (chooseNew - 1));
					customerOrder_TotalPrice.erase(customerOrder_TotalPrice.begin() + (chooseNew - 1));
				}
			}
		}
		else {
			for (int i = 0; i < customerOrderQty.size(); i++) {
				positionItem = search(customerOrderItem, orderChangeQty);
				if (positionItem != -1) {
					customerOrderQty.at(chooseNew - 1) = newQty;
					customerOrder_TotalPrice.at(chooseNew - 1) = abu;
				}

			}
		}
		system("CLS");
		currentOrder(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
	}
}

void removeItem(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice)
{
	if (customerOrderItem.empty()) {
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		cout << "This is what you ordered " << endl;
		for (int i = 0; i < customerOrderQty.size(); i++)
		{
			cout << i + 1 << " " << setw(21) << customerOrderItem[i] << setw(16) << customerOrderQty[i] << setw(16) << fixed << setprecision(2) << customerOrderPrice[i] << endl;
		}
		cout << "Please choose what you want to remove " << endl;
		int chooseNew;
		cin >> chooseNew;
		string customerToChange = customerOrderItem.at(chooseNew - 1);
		cout << customerToChange << endl;
		for (int i = 0; i < customerOrderQty.size(); i++) {
			int positionItem = search(customerOrderItem, customerToChange);
			if (positionItem != -1) {
				//customerOrderQty.at(chooseNew - 1) = newQty;
				customerOrderItem.erase(customerOrderItem.begin() + (chooseNew - 1));
				customerOrderQty.erase(customerOrderQty.begin() + (chooseNew - 1));
				customerOrderPrice.erase(customerOrderPrice.begin() + (chooseNew - 1));
				customerOrder_TotalPrice.erase(customerOrder_TotalPrice.begin() + (chooseNew - 1));
			}
		}
		system("CLS");
		currentOrder(menuItem, menuPrice, customerOrderPrice, customerOrderQty, customerOrderItem, customerOrder_TotalPrice);
	}
}

void printReceipt(vector<string>& menuItem,vector<int>& sessionQuantity, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice,double& totalPrice) {
	if (customerOrderItem.empty()) {
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		ifstream infile("Order.txt", ofstream::in);
		if (!infile) {
			cout << "File does not exit";
			exit(1);
		}
		ofstream outfile("Order.txt", ofstream::out);
		if (!outfile) {
			cout << "File could not be open\n";
			exit(1);
		}
		ofstream outfile2("MultiOrder.txt", ofstream::out|ofstream::app);
		if (!outfile2) {
			cout << "File could not be open\n";
			exit(1);
		}
		cout << "\t\t	==========================================\n";
		cout << "\t\t\t|             Rainbow's Restaurant        |\n";
		cout << "\t\t\t|             No.Tel: 03-12345612         |\n";
		cout << "\t\t\t|                                         |\n";
		cout << "\t\t	==========================================\n\n";
		cout << "------------------------------------------------------\n";
		cout  <<setw(12)<<left<< "Quantity" << setw(25) << "Description" << setw(10) << "Price" << setw(10) << "Amount" << endl;
		cout << "------------------------------------------------------\n";
		for (int i = 0; i < customerOrderQty.size(); i++) {
			cout << setw(12) << left<< customerOrderQty[i] << setw(25) << customerOrderItem[i] << setw(10) << fixed << setprecision(2) << customerOrderPrice[i] << setw(10) << fixed << setprecision(2) << customerOrder_TotalPrice[i] << endl;
		}
		cout << endl;
		cout << "======================================================\n";
		outfile << setw(5) << "Quantity" << setw(25) << "Description" << setw(10) << "Price" << setw(10) << fixed << setprecision(2) << "Amount" << endl;
		outfile2 << setw(5) << "Quantity" << setw(25) << "Description" << setw(10) << "Price" << setw(10) << fixed << setprecision(2) << "Amount" << endl;
		for (int i = 0; i < customerOrderQty.size(); i++) {
			outfile << setw(5) << customerOrderQty[i] << setw(25) << customerOrderItem[i] << setw(10) << fixed << setprecision(2) << customerOrderPrice[i] << setw(10) << fixed << setprecision(2) << customerOrder_TotalPrice[i] << endl;
			outfile2 << setw(5) << customerOrderQty[i] << setw(25) << customerOrderItem[i] << setw(10) << fixed << setprecision(2) << customerOrderPrice[i] << setw(10) << fixed << setprecision(2) << customerOrder_TotalPrice[i] << endl;
			for (size_t j = 0; j < menuItem.size(); j++)
			{
				if(menuItem[j]==customerOrderItem[i]){
					sessionQuantity[j] +=customerOrderQty[i];
					break;
				}
			}
			
		};
		double sum = 0;
		for (int i = 0; i < customerOrderQty.size(); i++) {
			sum += customerOrder_TotalPrice[i];
		}
		outfile << "Total :" << sum << endl;
		outfile2 << "Total :" << sum << endl<< endl<< endl;
		cout << "Total : "  << "RM " << sum << endl;
		cout << "Enter total amount you want to pay: ";
		double pay;
		cin >> pay;
		while (pay < sum) {
			if (pay < sum) {
				cout << "Tak cukup bossku ." << endl;
				cout << "Please enter new amount : ";
				cin >> pay;
			}
		}
		cout << endl;
		cout << "Total : " << "RM " << sum << endl;
		cout << "Change : RM " << left << pay - sum << endl;

		cout << "\t\t	==========================================\n";
		cout << "\t\t\t|          Terima Kasih Daun Keladi       |\n";
		cout << "\t\t\t|          Kalau Sedap Datang Lagi        |\n";
		cout << "\t\t\t|                                         |\n";
		cout << "\t\t	==========================================\n\n";
		char pape;
		cout << "Enter anything to continue : ";
		cin >> pape;
		system ("CLS");
	}
}

void removeAllItem(vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice) {
	if (customerOrderItem.empty()) {
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		cout << "Are you sure you want to clear all your order ? " << endl;
		cout << "Please enter Y or N" << endl;
		char ss = 'w';
		cin >> ss;
		if (ss == 'Y' || ss == 'y') {
			customerOrderPrice.clear();
			customerOrderQty.clear();
			customerOrderItem.clear();
			customerOrder_TotalPrice.clear();
		}
	}
}

void dailySales(vector<string>& menuItem, vector<double>& menuPrice, vector<double>& customerOrderPrice, vector<int>& customerOrderQty, vector<string>& customerOrderItem, vector<double>& customerOrder_TotalPrice, double& totalPrice, vector<string>& dailyItem, vector<int>& dailyQty, vector<double>& dailyPrice)
{
	if (customerOrderItem.empty()) {
		cout << "You not order anything ." << endl;
		cout << "Please select your order first :) " << endl;
		cout << endl;
	}
	else {
		cout << setw(15) << "Item" << setw(10) << "Quantity" << setw(10) << fixed << setprecision(2) << "Price" << endl;
		for (int i = 0; i < customerOrderItem.size(); i++) {
			cout << i + 1 << ". " << setw(15) << customerOrderItem[i] << setw(10) << customerOrderQty[i] << setw(10) << fixed << setprecision(2) << customerOrderPrice[i] << endl;
		}
	}

}

int search(vector<string>w, string key) {
	for (size_t i = 0; i < w.size(); i++) {
		if (w.at(i).compare(key) == 0)
			return i;
	}
	return -1;
}