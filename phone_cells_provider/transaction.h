#pragma once
#include "pch.h"

class user; //deklaracja zeby moc wykorzystac usera

class transaction
{
public:
	transaction();
	void createUser(user*);
	void eraseUser(int id);
	user* getUser(int id);
	~transaction();

private:
	MYSQL *db_conn;
};

