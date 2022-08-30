#include<iostream>
#include<conio.h>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<ctime>
#include<stdio.h>
#include "windows.h"


using namespace std;

// CREATED BY SAI TEJA  


//function definition for setting cursor poistion int the console window

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}







//price list of items

float price_list[20] = { 865,2.25,44,10,20,7710,33.33,48.97,0.5,0.01,88,999,25000,87,4,22,200,20,150 };





class po;                        // forward declaration of po class  (for freind function)




class requisition
{
	/*            Defining data members for storing requisition details             */

	static int req_no;
	int item_code;
	int qty;
	string delivery_date;


     public:
		 /*    Class function declaration    */
		 void getdata();
		 void display();
		 friend void generate(requisition, po); // friend function declaration

};



// function for receiving requisition details

void requisition::getdata()
{


	system("cls");

	req_no++;
	cout << "Product Item Code: ";
	cin >> item_code;
	cout << "Quantity: ";
	cin >> qty;
	cout << "Delivery Date: ";
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, delivery_date);

}

	// defining static data member

	int requisition::req_no;


	//function for displaying requisition details


	void requisition::display()
	{
		system("cls");

		cout << "Requisition Number: " << req_no;
		cout << "\nProduct Item Code: " << item_code;
		cout << "\nQuantity: " << qty;
		cout << "\nDelivery Date: " << delivery_date;
		_getch();
	}



	class po
	{
		static int po_no;
		


	public:

		// constructor is used for increamenting the static variable po_no

		po()
		{
			po_no++;
		}



		friend void generate(requisition, po);     //friend function declaration


	};

	//defining static data member

	int po::po_no;



	//defining friend function
	void generate(requisition r, po p)
	{

		ofstream fout;

		//retreving system date and time
		time_t current = time(0);
		char* dt = ctime(&current);


		//opening the Current_PO.txt file in which PO details are stored 


		fout.open("Current_PO.txt");

		//Generating the PO and storing it in the Current_PO.txt file in a formatted manner


		fout << "\t\t\t  Purchase Order#: " << p.po_no << "\n";
		fout << "\t\t\t________\n\n";
		fout << "Requisition#: " << r.req_no << "\t\t\t\tIssue Date: " << dt << "\n\n";
		if (r.item_code >= 1 && r.item_code <= 10)
			fout << "Supplier: " << "SKS Inc\n\n";
		else if(r.item_code>=11 && r.item_code<=20)
			fout << "Supplier: " << "KC Spare Parts Ltd.\n\n";
		else
			fout << "Supplier: " << "Other(_____________)\n\n";


		fout << "Delivery Date: " << r.delivery_date << "\n\n";
		fout << "----------------------------------------------------------------------------------------------------------------------\n";
		fout << "                                            *Line Items*                                                            \n";
		fout << "----------------------------------------------------------------------------------------------------------------------\n";
		fout << "Item Code\t\tQuantity\t\tPrice\t\tTotal\n";
		fout << "___\t\t___\t\t_\t\t___\n\n";
		fout << " " << r.item_code << "\t\t\t " << r.qty << "\t\t\t";
		if (r.item_code >= 1 && r.item_code <= 20)
		{
			fout << " " << price_list[r.item_code - 1] << "\t\t\t " << price_list[r.item_code - 1] * r.qty << "\n\n\n\n";

		}
		else
		{
			fout << "_\t\t\t___\n\n\n\n";
		}

	
		fout.close();




	}




int main()
{
	requisition r;

	char flag = 'f';

	char ch;
	//Displaying a menu to accept user commands

	while (true)
	{

		system("cls");
		gotoxy(35, 8);

			cout << "PR2PO";
		gotoxy(35, 9);
		cout << "___";
		gotoxy(22, 12);
		cout << "1-Create New Requisition";
		gotoxy(22, 13);
		cout << "2-Display Requisition";
		gotoxy(22, 14);
		cout << "3-Generate PO";
		gotoxy(22, 15);
		cout << "4-Exit";
		gotoxy(22, 18);
		cout << "Select an Option by typing the numeric code :";
		ch = _getch();
		switch (ch)
		{
		case('1'):
		{
			r.getdata();
			flag = 't';
			break;


		}

		case('2'):
		{

			if (flag == 'f')
			{
				gotoxy(22, 20);
				cout << "Requisition Details not Entered! press any key to continue...";
				_getch();
			}
			else
			{
				r.display();
				break;
			}

		}


		case('3'):
		{

			po p;
			generate(r, p);
			gotoxy(22, 20);
			cout << "PR has been converted into a PO. You can view the current_PO.txt file to view the generated PO and take its print out";
			_getch();
			break;

		}

		case('4'):
		{
			exit(1);
			break;

		}

		default:
		{
			gotoxy(22, 20);
			cout << "Invalid Choice! Press any key to continue...";
			_getch();
		}





		}





	}
	return 0;





	
}
