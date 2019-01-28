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

int transaction::checkCredentials(string userNam, string psw)
{
	MYSQL_RES *idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql;
	sql << "SELECT id_user FROM user WHERE username = '"
		<< userNam << "' and psswrd = '"
		<< psw << "'";
	if (!mysql_query(db_conn, sql.str().c_str()))
		{
			idZapytania = mysql_use_result(db_conn);
			if ((wiersz = mysql_fetch_row(idZapytania)) != nullptr)
			{
				int id = atoi(wiersz[0]);
				mysql_free_result(idZapytania);
				return id;
			}
			else return 0;
		}
		//[](MYSQL_RES *idZapytania, MYSQL_ROW wiersz, MYSQL *db_conn)->int {idZapytania = mysql_use_result(db_conn); wiersz = mysql_fetch_row(idZapytania); return atoi(wiersz[0]);}(nullptr,nullptr,db_conn);
	else
	{
		cout << mysql_error(db_conn) << endl;
		return 0;
	}
}


user* transaction::getUser(int id)
{
	user *x = nullptr;
	MYSQL_RES* idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql;
	sql << "SELECT * FROM user where id_user =" << 10 << endl;

	if (!mysql_query(db_conn, sql.str().c_str()))
	{
		x = new user();
		idZapytania = mysql_use_result(db_conn);
		wiersz = mysql_fetch_row(idZapytania);
		x->setIdUser(atoi(wiersz[0]));
		x->setCellNumber(atoi(wiersz[1]));
		x->setUserName(wiersz[2]);
		x->setPsswrd(wiersz[3]);
		x->setPrivileges(atoi(wiersz[4]));
		mysql_free_result(idZapytania);

		return x;
	}
	else
	{
		cout << "Error, update failed:" << mysql_errno(db_conn) << endl;
	}
}

transaction::~transaction()
{
	mysql_close(db_conn);
}
