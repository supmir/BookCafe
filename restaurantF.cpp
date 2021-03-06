#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <ctime>


using namespace std;

class MenuList{
	public:
		vector<MenuItem> itemList;
		// string scode;
		void newItem(string name, double price){
			// cout << name << price;
			MenuItem item;

			item.name = name;
			item.price = price;
			item.quantity = 0;
			itemList.push_back(item);
			
	}
		void listAll(){
			cout<< table();
			
			
		}
		string table(){
			string str = "|ID |Item                |Unit Price|\n";
			for (size_t i = 0; i < itemList.size(); i++)
			{	
				string line = "";
				MenuItem temp = itemList[i];
				string ID = to_string(i+1)+" ";
				string name = temp.name;
				double price = temp.price;
				
				stringstream ss;
				ss << fixed << setw(3) <<ID<<"|"<< setw(20) <<name<<"|"<< setw(10) <<setprecision(2)<< price<<"|";
				line ="|"+ss.str()+"\n";
				str+=line;
			}
			return str;
		}


		string report(){
			double total=0.00;
			string str = "|ID |Item                |Quantity|Unit Price|Sales|\n";
			for (size_t i = 0; i < itemList.size(); i++)
			{	
				
				string line = "";
				MenuItem temp = itemList[i];
				string ID = " "+to_string(i+1);
				string name = temp.name;
				int quantity = temp.quantity;
				double price = temp.price;
				double cur = quantity*price;
				
				stringstream ss;
				ss << fixed << setw(3) <<ID<<"|"<< setw(20) <<name<<"|"<< setw(8) <<quantity<<"|"<< setw(10) <<setprecision(2)<< price<<"|"<<setw(5)<<cur<<"|";
				line ="|"+ss.str()+"\n";
				
				total+= cur;
				str+=line;

			}
			str +="\nTotal : ";
			stringstream ss;
			ss << fixed<< setprecision(2)<<total;
			str +=ss.str()+"\n";
			return str;
		}



		MenuItem get(int x){
			return itemList[x];
		}

		
		bool exist(int x){
			
			return x>=0 && x<itemList.size();
		}
};


class OrderList{
	public:
		vector<OrderItem> itemList;
		double total = 0.00;
		string newItem(MenuItem temp, int q){
			OrderItem item;
			item.name = temp.name;
			item.price = temp.price;
			item.quantity = q;
			itemList.push_back(item);
			return to_string(q)+" " + item.name;
		}
		bool isNew(MenuItem temp){
			for (size_t i = 0; i < itemList.size(); i++)
			{
				if(temp.name == itemList[i].name &&	temp.price == itemList[i].price){
					return false;
				}
				
			}
			return true;
		}

		string changeQuantity(string name, double price, bool relative, int amount){
			for (size_t i = 0; i < itemList.size(); i++)
			{
				if(name == itemList[i].name &&	price == itemList[i].price){
					if(relative){
						itemList[i].quantity+=amount;
						return to_string(amount) + itemList[i].name;
					}else{
						itemList[i].quantity = amount;
						return "";
					}
				}
				
			}
			return "";
		}
		bool isEmpty(){
			return itemList.size() == 0;
		}
		OrderItem get(int x){
			return itemList[x];
		}

		void remove(int x){
			itemList.erase(itemList.begin()+x);
		}
		bool exist(int x){
			return (x>=0 && x<itemList.size());
		}
};



void pause(){
	cout<< "Press enter to continue\n";
	fflush(stdin);
	// cin.ignore();
	cin.get();
}

void menuCreator(vector<string>& menu){
	string line;
	ifstream infile("Menu.txt");
	if (infile.is_open()) {
		while(getline(infile,line)){
			menu.push_back((line+"0"));
		}
	}else{
		cout << "file does not exist\n";
		exit(1);
	}
}
void updateQuantity(string name,double price, int quantity,vector<string> menu){
	for (size_t i = 0; i < menu.size(); i++)
			{
				string key = name+to_string(price)
				size_t found = menu[i].find(key);

				if( == menu[i]){
					itemList[i].quantity+=q;

				}
				
			}
}
vector<string> orderTable(bool serious, vector<string> order,vector<string> menu){//0 is table, 1 is total
	double total = 0;
	string str = "|ID |Item                |Quantity|Unit Price|Price|\n";
	for (size_t i = 0; i < order.size(); i++){		
		string line = "";
		string ID = " "+to_string(i+1);
		stringstream ss(order[i]);
		string name;
		int quantity;
		double price;


		ss >> name >> price >> 	quantity;
		double cur = (quantity/1.0)*price;

				stringstream ss;
				ss << fixed << setw(3) <<ID<<"|"<< setw(20) <<name<<"|"<< setw(8) <<quantity<<"|"<< setw(10) <<setprecision(2)<< price<<"|"<<setw(5)<<cur<<"|";
				line ="|"+ss.str()+"\n";
				
				total+= cur;
				str+=line;

				if(serious){
					updateQuantity(name, price, quantity, menu);
				}
			}
			str +="\nTotal : ";
			stringstream ss;
			ss << fixed <<setprecision(2)<<total;
			str +=ss.str()+"\n";
			return str;
}
void showOrder (vector<string>& order,vector<string>& menu){
	if(order.size()==0){
		cout << "Please select your order first\n" << endl;
	}else{
		cout << orderTable(false,menu);
	}
	pause();

}

void showMenu(MenuList& menu, OrderList& order,string s){
	
	int temp;
	ORDERSELECTION:
	menu.listAll();
	if(s!=""){
		cout << s << " has been added to your order" << endl;
	}
	cout << "Select your order (input 0 to return to menu) \n>> ";
	cin >> temp;
	
	if(temp==0){
		system("CLS");
		return;
	}
	if(!menu.exist(temp-1)){
		cout << "Invalid option\n";
		goto ORDERSELECTION;
	}
	int q;
	
	QUANTITY:cout << "Input quantity >> ";
	cin >> q;
	if(q<0){
		cout << "Invalid quantity\n";
		goto QUANTITY;
	}
	system("CLS");

	string name;
	bool added = false;
	if(order.isNew(menu.get(temp-1))){
		name = order.newItem(menu.get(temp-1),q);
		added= true;
	}else{
		name = order.changeQuantity(menu.get(temp-1).name,menu.get(temp-1).price,true,q);
		added = true;
	}
	showMenu(menu,order,name);
}

void changeQuantity(OrderList& order, MenuList& menu){
	if(!order.listAll(menu)){
		return;
	}
	int temp, amt;
	ALTER:cout << "Which item would you like to alter (enter 0 to return to menu)?\n>> ";
	
	cin >> temp;


	if(temp==0){
		return;
	}
	
	if(!order.exist(temp-1)){
		cout << "Invalid option\n";
		goto ALTER;
	}


	cout << "Enter new amount (0 to cancel)"<<endl<< ">> ";
	cin >> amt;
	if(amt==0){
		return;
	}
		system("CLS");

	order.changeQuantity(order.get(temp-1).name,order.get(temp-1).price,false,amt);
}

void removeItem(OrderList& order, MenuList& menu){
	if(!order.listAll(menu)){
		return;
	}
	int temp;
	REMOVE:cout << "Which item would you like to remove (enter 0 to return to menu)? \n>> ";
	cin >> temp;
	if(temp==0){
		return;
	}
	if(!order.exist(temp-1)){
		cout << "Invalid option\n";
		goto REMOVE;
	}
	order.remove(temp-1);
	cout << "Item removed.\n";
	pause();
}

void removeAllItems(OrderList& order, MenuList& menu, bool silent){
	if(order.isEmpty()){
		cout << "Please select your order first\n";
	}
	else{
		string x;
		if(!silent){
			cout << "Are you sure you want to remove all items (enter yes to confirm)?\n>> ";
			cin >> x;
		}
		if(x=="yes"||silent){
			OrderList fresh;
			order = fresh;
		}

	}
}
void pay(OrderList& order, MenuList& menu){
	string table = order.table(true, menu);
	cout << table;
	double total = order.total, payment=0.00, change=0.00;
	PAY:cout << "Please enter payment amount"<<endl<<"\n>> ";
	cin >> payment;
	change = payment-total;
	if(change<0){
		cout << "Insufficient amount. \n>> ";
		goto PAY;
	}
	cout << "Your change is "<< fixed<< setprecision(2)<<change<<endl;
	
	stringstream ss;
	ss << time(0); //get current time
	string filename = "RECEIPT"+ ss.str() +".txt",scode = "MasterReceipt"+ menu.scode +".txt"; //concatenate time with ".txt"
	ofstream receipt (filename),master(scode,ofstream::app);//create and open both files
	if (receipt.is_open()) //write to individual receipt
	{
		receipt << table;
		receipt << "Payment : " << fixed << setprecision(2) << payment << "\nChange : " << change <<"\n\n\n";
		receipt.close();
	}
	else cout << "Unable to open file\n";
	if (master.is_open()) //write to master receipt
	{
		master << "RECEIPT " << ss.str() << endl;
		master << table;
		master << "Payment : " << fixed <<setprecision(2)<< payment << "\nChange : " << change <<"\n\n\n";
		master.close();
	}
	else cout << "Unable to open file\n";
	removeAllItems(order,menu,true);
}


void dailyReport(OrderList& order, MenuList& menu){
	string table = menu.report();

	stringstream ss;
	ss << time(0);
	string filename = "REPORT"+ ss.str() +".txt";
	ofstream receipt (filename);
	if (receipt.is_open())
	{
		receipt << table;
		receipt.close();
	}
	else cout << "Unable to open file\n";
	cout << table;
}

void intro(vector<string>& menu, vector<string>& order, string scode){
		system("CLS");
		int option;
		cout << "\t [1] Show the current order\n ";
		cout << "\t [2] Show the restaurant's menu\n ";
		cout << "\t [3] Change the quantity\n ";
		cout << "\t [4] Remove an item from order\n ";
		cout << "\t [5] Pay and print receipt\n ";
		cout << "\t [6] Remove all items\n ";
		cout << "\t [7] Exit programme\n ";
		cout << "\t [8] Show the daily sales\n ";
		cout << "\n\t Enter option : ";
		cin >> option;
		system("CLS");

		cout << endl;
	
		switch (option) {
		case 1:
			showOrder(order,menu);
			break;
		case 2:
			showMenu(menu,order,"");
			break;
		case 3:
			changeQuantity(order, menu);
			break;
		case 4:
			removeItem(order, menu);
			break;
		case 5:
			pay(order, menu);
			break;
		case 6:
			removeAllItems(order,menu,false);
			break;
		case 8:
			dailyReport(order, menu,scode);
		case 7:
			cout << "\n\t Thank You And Come Again \n";
			return;
		default:
			cout << "Invalid option\n";
		}
		intro(menu,order);
	
}

int main(){
	system("CLS");
	stringstream ss;
	ss << time(0); //get current time;
	string scode = ss.str();
	
	vector<string> menu,order;
	menuCreator(menu);
	cout << "\t************************\t\n\t* Welcome to Book Cafe *\t\n\t************************\t" << endl;
	system("color 80");//color BF (B- background, F - font)
	/*
	0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple*/
	pause();
	intro(menu, order, scode);	
}