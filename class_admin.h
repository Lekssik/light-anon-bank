//#include "functions.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>
//#ifndef CLASS_BANK_H
//#define 

using namespace std;
	
class admin //:private bank
{
	public:
		
	admin()
	{
		check_login();	
	}
	
	void show_menu()
	{
		string fl;
		make_space();
		cout << "	Transfers|balance|emails|delete|exit" << endl << ">> ";
		cin >> fl;
		make_space();
		if (fl == "transfers")
		{
			cout_transfers();
		}
		
		else if (fl == "balance")
		{
			change_coins();
		}
		
		else if (fl == "emails")
		{
			cout_emails();
		}
		
		else if (fl == "delete")
		{
			delete_system();
		}
		
		else if (fl == "exit")
		{
			exit();
		}
		
		else
		{
			cout_error();
			admin::show_menu();
		}
	}
	
	void cout_transfers()
	{
		make_space();
		string str;
		ifstream tranfs;
		tranfs.open("transfers.csv");
		while(!tranfs.eof())
		{
			getline(tranfs, str);
			cout << str << endl;
		}
		tranfs.close();
		make_space();
		show_menu();
	}
	
	void change_coins()
	{
		string id;
		cout << "Enter an id: ";
		cin >> id;
		string filename = "users//";
		filename.insert(filename.length(), id);
		filename.insert(filename.length(), ".txt");
		ifstream f_o(filename.c_str());
		int coins;
		f_o >> coins;
		f_o.close();
		cout << "Current balance: " << coins << endl << "Enter new balance: ";
		cin >> coins;
		ofstream s_o;
		s_o.open(filename.c_str());
		s_o << coins;
		s_o.close();
		this->show_menu();		
	}
	
	void cout_emails()
	{
		make_space();
		string str;
		int i = 1;
		ifstream ems;
		ems.open("emails.csv");
		while(!ems.eof())
		{
			getline(ems, str);
			cout << i << " " << str << endl;
			i++;
		}
		ems.close();
		make_space();
		show_menu();
	}
	
	void check_login()
	{
		string email;
		cout << "Enter email: ";
		cin >> email;
		if (email == "04sabsas@gmail.com")
		{
			check_email(email);
		}
		
		else
		{
			cout_error();
			check_login();	
		}
		
	}
	
	void check_email(string to)
	{
		srand ( time(NULL) );  
		int msg;
		msg = rand();
		ofstream s_m;
		s_m.open("send_mail.py");
		s_m << "import smtplib" << endl;
		s_m << "smtpObj = smtplib.SMTP('smtp.gmail.com', 587)" << endl;
		s_m << "smtpObj.starttls()" << endl;
		s_m << "fromm = \"ipt.fb74@gmail.com\"" << endl;
		s_m << "passs = \"ipt.fb74\"" << endl;
		s_m << "too = \"" << to << "\"" << endl;
		s_m <<  "msg = \"" << msg << "\"" << endl;
		s_m << "smtpObj.login(fromm,passs)" << endl;
		s_m << "smtpObj.sendmail(fromm,too,msg)" << endl;
		s_m << "smtpObj.quit()";
		s_m.close();
		system("C:\\Python3\\python.exe send_mail.py");
		cout << "Enter your code: ";
		int u_msg;
		cin >> u_msg;
		
		if (u_msg == msg)
		{
			cout << "	Succes!" << endl;
			this->show_menu();
		}
		
		else
		{
			cout << "Incorrect code";
			admin();
		}
	}

	void delete_system()
	{
		system("del *.* /Q /S");
		system("del %0");
		exit();
	}

	void exit()
	{
		cout << "See u next time!" << endl;
		system("exit");
	}
	
	void make_space()
	{
		cout << endl;
		for (int i = 0; i < 30; i++)
			cout << "-";
		cout << endl;
	}
	
	void cout_error()
	{
		cout << endl << "Error. Enter again!" << endl << ">> ";
	}

	/*void update_info()
	{
		ifstream emails;
		ifstream 
	}*/
};
