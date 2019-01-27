#include "pch.h"
#include "transaction.h"
#include "user.h"
using namespace std;

transaction::transaction()
{
	db_conn = mysql_init(NULL);
	if (!db_conn)
		cout << "MySQL initialization failed! ";
	db_conn = mysql_real_connect(db_conn, "127.0.0.1", "root", "", "cellphoneprovider", 0, NULL, 0);
	if (!db_conn)
		cout << "Connection Error! ";
	else
		cout << "Connected\n";
}

void transaction::createUser(user *x)
{
	stringstream sql;
	sql << "INSERT INTO user( cellNumber , username, psswrd, privileges) VALUES ('"
		//<< x->getIdUser() << "', '"
		<< x->getCellNumber() << "', '"
		<< x->getUserName() << "', '"
		<< x->getPsswrd() << "', '"
		<< x->getPrivileges() << "')";
	if (!mysql_query(db_conn, sql.str().c_str()))
		cout << "New user created !\n";
	else
	{
		cout << "Error! User hasnt been created!\n" << mysql_error(db_conn);
	}
}


transaction::~transaction()
{
	mysql_close(db_conn);
}
