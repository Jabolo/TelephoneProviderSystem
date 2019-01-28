#pragma once
#include "pch.h"

using namespace std;
class user; //deklaracja zeby moc wykorzystac usera

class transaction
{
public:
	transaction();
	void createUser(user*);
	void eraseUser(int id);
	void createConnection(int, int, int, int);
	int checkCredentials(string userNam, string psw); //zwróci id pasuj¹cego usera
	user* getUser(int id); //zwraca uchwyt na usera
	~transaction();

private:
	MYSQL *db_conn;
};

