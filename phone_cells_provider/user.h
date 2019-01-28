#pragma once
#include "pch.h"
#include "transaction.h"
using namespace std;
class transaction;

class user
{
public:

	friend int transaction::hash(string const& s);
	friend ostream & operator <<(ostream &out, const user &y);
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

