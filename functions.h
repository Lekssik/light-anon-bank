#include <iostream>
#include <fstream>
#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

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

void greeting()
{
	for (int i = 0; i < 30; i++)
		cout << "=";
	cout << endl;
	for (int i = 0; i < 11; i++)
		cout << " ";
	cout << "Welcome!" << endl;
	cout << endl;
}

string int_to_str(int tem)
{
	ofstream temp;
	temp.open("bin1.txt");
	temp << tem;
	temp.close();
	ifstream temp1;
	temp1.open("bin1.txt");
	string a;
	temp1 >> a;
	temp1.close();
	return a;
}

string md5(string pass)
{
	ofstream f;
	f.open("bin2.txt");
	f << pass;
	f.close();
	system("C:\\Python3\\python.exe md5.py");
	ifstream ff;
	ff.open("bin2.txt");
	string psw;
	ff >> psw;
	ff.close();
	return psw;
}

#endif
