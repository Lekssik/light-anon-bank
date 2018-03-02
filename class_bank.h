#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "functions.h"
#include "class_guest.h"

#ifndef CLASS_BANK.H
#define CLASS_BANK.H

using namespace std;



class bank
{
	protected:
		int balance, id;
		string email, password;
	
	public:
		
	bank()
	{
		greeting();
		string fl;
		cout << "	login|register|feedback|exit" << endl << ">> ";
		cin >> fl;
		if (fl == "login")
		{
			login_user();
		}
		else if (fl == "register")
		{
			register_user();
		}
		
		else if (fl == "exit")
		{
			cout << "		Goodbye!" << endl;
			system("exit");	
		}
		
		else if (fl == "feedback")
		{
			guest();
		}
		
		else
		{
			cout_error();
			bank();
		}
	}
	
	void login_user()
	{
		make_space();
		int t_id;
		string t_pass;
		cout << "	Log in" << endl;
		cout << "Enter id: ";
		cin >> t_id;
		cout << "Enter password: ";
		cin >> t_pass;
		string str;
		ifstream table;
		table.open("users.csv");
		for (int i = 1; i <= t_id; i++)
			getline(table, str);
			
		if (str == md5(t_pass))
		{
			cout << "	Succes!" << endl;
			system("pause");
			system("cls");
			this->id = t_id;
			send_email(1, this->id, this->id, 0);
			load_data(this->id);
		}
		else
		{
			cout << "Inccorect password!" << endl;
			bank();
		}
	}
	
	void register_user()
	{
		string n_email, n_pass;
		make_space();
		cout << "		Registration" << endl;
		cout << "Enter email: ";
		cin >> n_email;
		cout << "Enter password: ";
		cin >> n_pass;
		ofstream emails;
		emails.open("emails.csv", ios::app);
		emails << n_email << endl;
		emails.close();
		ofstream users;
		users.open("users.csv", ios::app);
		users << md5(n_pass) << endl;
		users.close();
		ifstream bin;
		bin.open("bin.txt");
		int mount_users;
		bin >> mount_users;
		bin.close();
		ofstream bin_a;
		bin_a.open("bin.txt");
		bin_a << mount_users + 1;
		bin_a.close();
		ofstream us;
		string filename = int_to_str(mount_users);
		filename.insert(filename.length(), ".txt");
		us.open(filename.c_str());
		us << 0;
		us.close();
		string sys_com = "move ";
		sys_com.insert(sys_com.length(), filename);
		sys_com.insert(sys_com.length(), " users");
		system(sys_com.c_str());
		cout << "Your id: " << mount_users << ". Remember it!" << endl;
		cout << "		New user succesfully created!" << endl;
		system("pause");
		system("cls");
		bank();
	}
	
	void load_data(int t_id)
	{
		string filename = " ";
		
		//itoa(t_id, filename.c_str(), 10);
		filename = int_to_str(t_id);
		filename.insert(0, "users\\");
		filename.insert(filename.length(), ".txt");
		ifstream file;
		file.open(filename.c_str());
		file >> this->balance;
		file.close();
		ifstream emails;
		emails.open("emails.csv");
		for (int i = 0; i <= this->id; i++)
			getline(emails, this->email);
		emails.close();
		show_menu();
	}
	
	void show_menu()
	{
		string fl;
		cout << "	balance|pay|logout" << endl << ">> ";
		cin >> fl;
		if (fl == "balance")
		{
			show_balance();
		}
		
		else if (fl == "pay")
		{
			pay();
		}
	
		else if (fl == "logout")
		{
			bank();	
		}
		
		else if (fl == "check")
		{
			int a_t;
			cout << "Enter an id: ";
			cin >> a_t;
			cout << user_email_by_id(a_t);
			make_space();
			show_menu();
		}
		
		else
		{
			cout_error();
			show_menu();
		}
	}
	
	void show_balance()
	{
		make_space();
		cout << "	Balance of user " << this->id << ":" << endl << this->balance;
		make_space();
		show_menu();
	}
	
	void pay()
	{
		int r_id, sum;
		cout << "Enter an id of reciever: ";
		cin >> r_id;
		cout << "Enter a sum: ";
		cin >> sum;
		if (check_user(r_id) == true)
		{
			if (((this->balance - sum) < 0) or (sum < 0))
			{
				cout << "Inncorect sum" << endl;
				show_balance();
				show_menu();
			}
			else
			{
				string r_id_str, my_id_str;
				r_id_str = int_to_str(r_id);
				//itoa(r_id, r_id_str, 10);
				my_id_str = int_to_str(this->id);
				//itoa(this->id, my_id_str, 10);
				string h_f = r_id_str;
				h_f.insert(0, "users\\");
				h_f.insert(h_f.length(), ".txt");
				ifstream his;
				his.open(h_f.c_str());
				int h_b;
				his >> h_b;
				cout <<"His bal before: " << h_b << endl;
				his.close();
				h_b = h_b + sum;
				ofstream his2;
				his2.open(h_f.c_str());
				his2 << h_b;
				his2.close();
				string m_f = my_id_str;
				m_f.insert(0, "users\\");
				m_f.insert(m_f.length(), ".txt");
				ofstream my;
				my.open(m_f.c_str());
				this->balance = this->balance - sum;
				my << this->balance;
				my.close();
				send_email(3, this->id, r_id, sum);
				send_email(2, r_id, this->id, sum);
				cout << "Succes!" << endl;
				make_space();
				save_transfer(this->id, r_id, sum);
				system("pause");
				system("cls");
				show_menu();
				
			}
		}
		else
		{
			cout << "User didn't found" << endl;
			show_menu();
		}
	}
	
	void send_email(int mode, int from, int to, int mount)
	{
		string from_email, to_email;
		from_email = user_email_by_id(from);
		to_email = user_email_by_id(to);
		string from_str, to_str, mount_str, too;
		mount_str = int_to_str(mount);
		//itoa(mount, mount_str, 10);
		//itoa(from, from_str, 10);
		from_str = int_to_str(from);
		to_str = int_to_str(to + 1);
		//itoa(to, to_str, 10);
		string msg;
		if (mode == 1)
			msg = "New connection set";
		else if (mode == 2)
		{
			msg = "Sent ";
			msg.insert(msg.length(), mount_str);
			msg.insert(msg.length(), " to user ");
			msg.insert(msg.length(), to_str);
			too = this->email;
		}
		else if (mode == 3)
		{
			msg = "User ";
			msg.insert(msg.length(), from_str);//c_str()
			msg.insert(msg.length(), " sent you ");
			msg.insert(msg.length(), mount_str);
			
		}
		ofstream s_m;
		s_m.open("send_mail.py");
		cout << "Sending messege..." << endl;
		s_m << "import smtplib" << endl;
		s_m << "smtpObj = smtplib.SMTP('smtp.gmail.com', 587)" << endl;
		s_m << "smtpObj.starttls()" << endl;
		s_m << "fromm = \"ipt.fb74@gmail.com\"" << endl;
		s_m << "passs = \"ipt.fb74\"" << endl;
		s_m << "too = \"" << to_email << "\"" << endl;
		s_m <<  "msg = \"" << msg << "\"" << endl;
		s_m << "smtpObj.login(fromm,passs)" << endl;
		s_m << "smtpObj.sendmail(fromm,too,msg)" << endl;
		s_m << "smtpObj.quit()";
		s_m.close();
		system("C:\\Python3\\python.exe send_mail.py");
	}
	
	bool check_user(int id)
	{
		int c_id;
		ifstream bin;
		bin.open("bin.txt");
		bin >> c_id;
		if (c_id > id)
			return true;
		else 
			return false;
		bin.close();
	}
	
	string user_email_by_id(int id)
	{
		string str;
		ifstream emailss;
		emailss.open("emails.csv");
		int i = 0;
		while (i != id)
		{
			getline(emailss, str);
			i++;
		}
		emailss.close();
		return str;
	}
	
	void save_transfer(int from, int to, int mount)
	{
		ofstream transfers;
		transfers.open("transfers.csv", ios::app);
		transfers << from << ";" << to << ";" << mount << endl;
		transfers.close();
	}
};

class unused:private bank
{
	public:
		cout_balance()
		{
			cout << bank::balance << endl;
		}
		cout_email()
		{
			cout << bank::email << endl;
		}
		cout_id()
		{
			cout << bank::email << endl;
		}
};
#endif
