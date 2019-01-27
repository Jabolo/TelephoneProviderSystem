#pragma once
#include "pch.h"

using namespace std;
class user
{
public:
	user(int = 1000, string = "", string = "", int = 10000);
	void setIdUser(int);
	void setCellNumber(int);
	void setUserName(string);
	void setPsswrd(string);
	void setPrivileges(int);

	int getIdUser() const;
	int getCellNumber()const;
	string getUserName() const;
	string getPsswrd() const;
	int getPrivileges() const;

	~user();

private:
	int idUser;
	int cellNumber;
	string userName;
	string psswrd;
	int privileges;

};

