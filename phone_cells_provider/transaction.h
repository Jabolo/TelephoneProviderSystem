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
	void createConnection(int, int, int, int, int cellNum);
	int checkCredentials(string userNam, string psw); //zwróci id pasuj¹cego usera
	void listCalls(int id);
	static int hash(string const& s);
	user* getUser(int id); //zwraca uchwyt na usera
	~transaction();

private:
	MYSQL *db_conn;
};

