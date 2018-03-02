#include <iostream>
#include <fstream>

using namespace std;

class guest
{
	public:
		
	guest()
	{
		flag:
		make_space();
		cout << "	Welcome" << endl;
		cout << "feedback|info" << endl << ">> "; 
		string fl;
		cin >> fl;
		if (fl == "feedback")
		{
			feedback();
		}
		
		else if (fl == "info")
		{
			info();
		}
		
		else
		{
			cout_error();
			guest();
		}
	}
	
	void info()
	{
		make_space();
		string str;
		ifstream info;
		info.open("info.txt");
		while(!info.eof())
		{
			getline(info, str);
			cout << str << endl;
		}
		info.close();
		make_space();
		guest();
	}
	
	void send_email(string email, string msg)
	{
		ofstream s_m;
		s_m.open("send_mail.py");
		cout << "Sending messege..." << endl;
		s_m << "import smtplib" << endl;
		s_m << "smtpObj = smtplib.SMTP('smtp.gmail.com', 587)" << endl;
		s_m << "smtpObj.starttls()" << endl;
		s_m << "fromm = \"ipt.fb74@gmail.com\"" << endl;
		s_m << "passs = \"ipt.fb74\"" << endl;
		s_m << "too = \"" << email << "\"" << endl;
		s_m <<  "msg = \"" << msg << "\"" << endl;
		s_m << "smtpObj.login(fromm,passs)" << endl;
		s_m << "smtpObj.sendmail(fromm,too,msg)" << endl;
		s_m << "smtpObj.quit()";
		s_m.close();
		system("C:\\Python3\\python.exe send_mail.py");
	}

	void feedback()
	{
		string email, msg;
		cout << "We are happy to get feedback from you" << endl;
		cout << ">>Enter your messege: " << endl << endl;
		cin >> msg;
		cout << endl << "Enter your email (we will send you an answer): " << endl << endl;
		cin >> email;
		msg.insert(msg.length(), "  from ");
		msg.insert(msg.length(), email);
		send_email("04sabsas@gmail.com", msg);
		cout << "Thanks for your comment! Have a nice day";
		system("pause");
		system("cls");
	}

	void exit()
	{
		system("start main.exe");
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
};
