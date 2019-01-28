#include "pch.h"
#include "transaction.h"
#include "connection.h"
#include "user.h"

using namespace std;
void adminMenu(user *);
void userMenu(user *);

MYSQL db_name;
MYSQL_RES *idZapytania; //przechowalnia wskaźnika na zapytanie
MYSQL_ROW  wiersz; //przechowalnia pobranego wiersza
MYSQL* db_conn;

int main()
{

	db_conn = mysql_init(NULL);
	if (!db_conn)
		cout << "MySQL initialization failed! ";
	db_conn = mysql_real_connect(db_conn, "127.0.0.1", "root", "", "cellphoneprovider", 0, NULL, 0);
	if (!db_conn)
		cout << "Connection Error! ";
	else
		cout << "Connected\n\n";

	transaction *x = new transaction();
	bool isCorrect = true, tryAgain;
	string login, psswrd;
	int id;
	do {
		cout << "Login:\n";
		cin >> login;
		cout << "Password:\n";
		cin >> psswrd;
		if (id = x->checkCredentials(login, psswrd))
		{
			cout << "USER id = " << id << endl;
			user* smbdy = x->getUser(id);
			if (smbdy->getPrivileges() == 1)
				adminMenu(smbdy);
			else
				userMenu(smbdy);

			cout << "Wanna continue?\n0-NO\t1-YES\n";
				cin >> tryAgain;
		}
		else
		{
			cout << "Match not found.\nWanna try again?\n0-NO\t1-YES\n";
			cin >> tryAgain;
		}
	} while (tryAgain == 1);
	delete x;
	cout << "KONIEC PROGRAMU";
}


void adminMenu(user * userHandler)
{

	transaction *x = new transaction();
	int idUser;
	int cellNumber;
	string userName;
	string psswrd;
	int privileges;

	int idConnection;
	int from;
	int to;
	int status;
	int duration;

	cout << "WELCOME ADMIN !\n";
	int choice = 1;
	while (choice)
	{
		cout <<
			"1. Add new user\n"
			"2. Add new call\n"
			"3. Show my user menu\n"
			"4. Avg call duration - statistic\n"
			"0. Exit\n\n"
			"Your choice: ";

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			//add new user
			cout << "Enter cell phone: ";
			cin >> cellNumber;
			cout << "Enter name: ";
			cin >> userName;
			cout << "Enter password: ";
			cin >> psswrd;
			cout << "Enter privileges: ";
			cin >> privileges;
			x->createUser(new user(cellNumber, userName, psswrd, privileges));
			break;
		}
		case 2:
		{
			//add new call
			int opt; //opt = 1 pass id, opt 2= pass cellNembers
			do {
				cout << "Enter 1 when passing ID;\nEnter 2 when passing cellNumbers;\nYour choice: ";
				cin >> opt;
				if (opt == 1)
				{
					cout << "Enter id-from: ";
					cin >> from;
					cout << "Enter id-to: ";
					cin >> to;
				}
				else if (opt == 2)
				{
					cout << "Enter cellNumber-from: ";
					cin >> from;
					cout << "Enter cellNumber-to: ";
					cin >> to;
				}
			} while (opt != 1 and opt != 2);
			do {
				cout << "Enter 1 when call has been revceived;\nEnter 2 when call has been missed;\nYour choice: ";
				cin >> status;
			} while (status != 1 and status != 2);
			do {
				cout << "Enter duration of received call in seconds: ";
				cin >> duration;
			} while (duration < 0 );
			
			if(opt == 1 || opt == 2)
			x->createConnection(from, to, status, duration, opt);
			break;
		}
		case 3:
		{
			//my user menu
			userMenu(userHandler);
			break;
		}
		case 4:
		{
			//avg
			cout << "Average call duration ~=" << x->avgDuration() << endl;
			break;
		}
		}
	}
	delete x;
}

void userMenu(user * userHandler)
{
	cout << "WELCOME USER !\n";
	transaction *x = new transaction();
	int choice = 1;
	while (choice)
	{
		cout <<
			"1. Show my calls\n"
			"0. Exit\n\n"
			"Your choice: ";

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			//show my calls
			x->listCalls(userHandler->getIdUser());
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		}

	}
}