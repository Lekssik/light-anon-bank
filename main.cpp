#include "class_bank.h"
#include "class_admin.h"


int main() 
{
	cout << "Enter to continue...";
	string fl;
	cin >> fl;
	if (fl == "admin")
	{
		admin ex;
	}
	else
	{
		bank ex;
	}
}
