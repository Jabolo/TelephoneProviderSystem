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
		<< x->getCellNumber() << "', '"
		<< x->getUserName() << "', '"
		<< x->getPsswrd() << "', '"
		<< x->getPrivileges() << "')";
	if (!mysql_query(db_conn, sql.str().c_str()))
		cout << "New user created !\n";
	else
	{
		cout << "Error! User hasn't been created!\n" << mysql_error(db_conn)<< endl;
	}
}

void transaction::eraseUser(int id)
{
	stringstream sql;
	sql << "DELETE FROM user WHERE id_user = " << id;
	if (!mysql_query(db_conn, sql.str().c_str()))
		cout << "User deleted\n";
	else
		cout << "Error when erasing user\n";
}

void transaction::createConnection(int fr, int t, int stat, int dur)
{
	stringstream sql;
	sql << "INSERT INTO connection(id_from, id_to, status, duration)"
		"values ('"
		<< fr << "', '"
		<< t << "', '"
		<< stat << "', '"
		<< dur << "')";
	if (!mysql_query(db_conn, sql.str().c_str()))
		cout << "Connection created !\n";
	else
	{
		cout << "Error! Connection hasnt been created !\n" << mysql_error(db_conn) << endl;
	}
}


user * transaction::getUser(int id)
{
	//user *x = nullptr;
	//MYSQL_RES* idZapytania;
	//MYSQL_ROW wiersz;
	//stringstream sql;
	//sql << "SELECT * FROM user where id_user =" << id;

	//if (!mysql_query(db_conn, sql.str().c_str()))
	//{
	//	x = new user();
	//	idZapytania = mysql_use_result(db_conn);
	//	wiersz = mysql_fetch_row(idZapytania);
	//	x->setId_Account(atoi(wiersz[0]));
	//	x->setName_Account(wiersz[1]);
	//	x->setName_Client(wiersz[2]);
	//	x->setSurname_Client(wiersz[3]);
	//	x->setMoney(atof(wiersz[4]));

	//}
	//return x;
}

transaction::~transaction()
{
	mysql_close(db_conn);
}
