#include "pch.h"
#include "transaction.h"
#include "connection.h"
#include "user.h"

using namespace std;
void adminMenu();
void userMenu();

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


	bool isCorrect = true, tryAgain;
	string login, psswrd;
	do {
		cout << "Login:\n";
		cin >> login;
		cout << "Password:\n";
		cin >> psswrd;

		if (isCorrect)
			adminMenu();
		else
			userMenu();

		cout << "Brak dopasowania. Wanna try again?\n 0-NO\t1-YES";
		cin >> tryAgain;
	} while (tryAgain = 1);

	cout << "KONIEC PROGRAMU";
}


void adminMenu()
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
			cout << "Enter id-from: ";
			cin >> from;
			cout << "Enter id-to: ";
			cin >> to;
			cout << "Enter status: ";
			cin >> status;
			cout << "Enter duration: ";
			cin >> duration;
			x->createConnection(from, to, status, duration);
			break;
		}
		case 3:
		{
			//my suer menu
			userMenu();
			break;
		}
		}
	}
}

void userMenu()
{
	cout << "WELCOME USER !\n";
	//Transaction *x = new Transaction();
	int choice = 1;
	while (choice)
	{
		cout <<
			"1. Show my calls\n"
			//"2. Add new call\n"
			//"3. Show my user menu\n"
			"0. Exit\n\n"
			"Your choice: ";

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			//show my calls
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