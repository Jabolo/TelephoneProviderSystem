

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
void adminMenu();
void userMenu();
int main()
{
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
	cout << "WELCOME ADMIN !\n";
	//Transaction *x = new Transaction();
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
			break;
		}
		case 2:
		{
			//add new call
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