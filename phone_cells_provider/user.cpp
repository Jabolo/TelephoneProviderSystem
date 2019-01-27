#include "pch.h"
#include "user.h"

user::user(int num, string name, string psw, int prv)
	: cellNumber(num), userName(name), psswrd(psw), privileges(prv)
{
}

void user::setIdUser(int x)
{
	this->idUser = x;
}

void user::setCellNumber(int x)
{
	this->cellNumber = x;
}

void user::setUserName(string x)
{
	this->userName = x;
}

void user::setPsswrd(string x)
{
	this->psswrd = x;
}

void user::setPrivileges(int x)
{
	this->privileges = x;
}

int user::getIdUser() const
{
	return idUser;
}

int user::getCellNumber() const
{
	return cellNumber;
}

string user::getUserName() const
{
	return userName;
}

string user::getPsswrd() const
{
	return psswrd;
}

int user::getPrivileges() const
{
	return privileges;
}

user::~user()
{
}

