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
		cout << "New user created !\n\n";
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
		cout << "User deleted\n\n";
	else
		cout << "Error when erasing user\n";
}

void transaction::createConnection(int fr, int t, int stat, int dur, int cellNum)
{
	MYSQL_RES *idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql;
	int from = fr, to = t;
	if (cellNum == 2) //cellNumbers method of passing
	{
		//getting if of "from"usr
		sql << "SELECT id_user FROM user WHERE cellNumber = '"
			<< from << "'";
		if (!mysql_query(db_conn, sql.str().c_str()))
		{
			idZapytania = mysql_use_result(db_conn);
			if ((wiersz = mysql_fetch_row(idZapytania)) != nullptr)
			{
				from = atoi(wiersz[0]);
				mysql_free_result(idZapytania);
			}
		}
		sql.str("");

		//getting id of "to"usr
		sql << "SELECT id_user FROM user WHERE cellNumber = '"
			<< to << "'";
		if (!mysql_query(db_conn, sql.str().c_str()))
		{
			idZapytania = mysql_use_result(db_conn);
			if ((wiersz = mysql_fetch_row(idZapytania)) != nullptr)
			{
				to = atoi(wiersz[0]);
				mysql_free_result(idZapytania);
			}
		}
		sql.str("");
	}
	transaction *x = new transaction();
	user* usr1 = x->getUser(from);
	user* usr2 = x->getUser(to);
	//cout << "FROM " << usr1->getUserName() << " TO " << usr2->getUserName() << endl;
	//checking if these guys exist
	if (usr1->getUserName() != "" and usr2->getUserName() != "")
	{
		//adding new call
		sql << "INSERT INTO connection(id_from, id_to, status, duration)"
			"values ('"
			<< from << "', '"
			<< to << "', '"
			<< stat << "', '"
			<< dur << "')";
		if (!mysql_query(db_conn, sql.str().c_str()))
			cout << "Connection created !\n\n";
		else
		{
			cout << "Error! Connection hasnt been created !\n" << mysql_error(db_conn) << endl << endl;;
		}
	}
	else
	{
		cout << "Error! At least 1 user with such a credentials does not exist !\n\n";
	}
	delete x;
}

int transaction::checkCredentials(string userNam, string psw)
{
	MYSQL_RES *idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql, hashedPsswrd;
	string xxx;

	hashedPsswrd << hex << hash(psw);
	xxx = hashedPsswrd.str();
	sql << "SELECT id_user FROM user WHERE username = '"
		<< userNam << "' and psswrd = '"
		<< xxx << "'";
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

void transaction::listCalls(int id)
{
	MYSQL_RES *idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql;
	sql << "SELECT * FROM connection WHERE id_from =" << id << " or id_to =" << id;
	if (!mysql_query(db_conn, sql.str().c_str()))
	{
		transaction *x = new transaction();
		
		idZapytania = mysql_use_result(db_conn);
		cout << setw(11) << "sndr_cell" << setw(11) << "rcvr_cell"<< setw(11) << "status" << setw(11) << "duration" << endl;
		while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		{
				int id_fr = atoi(wiersz[1]), id_t = atoi(wiersz[2]);
				string s;
				if (atoi(wiersz[3]) == 1) s += "recieved";
				else
					s += "missd call";
				user* usr1 = x->getUser(id_fr);
				user* usr2 = x->getUser(id_t);
				cout << setw(11) << usr1->getCellNumber() << setw(11) << usr2->getCellNumber() << setw(11) << s << setw(11) << wiersz[4];
			cout << endl;
		}
		cout << endl;
		mysql_free_result(idZapytania);
		delete x;
	}
}

int transaction::hash(string const & s)
{
	unsigned long hash = 5381;
	for (auto c : s) {
		hash = (hash << 5) + hash + c; /* hash * 33 + c */
	}
	return hash;
}


user* transaction::getUser(int id)
{
	user *x = nullptr;
	MYSQL_RES* idZapytania;
	MYSQL_ROW wiersz;
	stringstream sql;
	sql << "SELECT * FROM user where id_user =" << id << endl;

	if (!mysql_query(db_conn, sql.str().c_str()))
	{
		x = new user();
		idZapytania = mysql_use_result(db_conn);
		if ((wiersz = mysql_fetch_row(idZapytania)) != nullptr)
		{
			x->setIdUser(atoi(wiersz[0]));
			x->setCellNumber(atoi(wiersz[1]));
			x->setUserName(wiersz[2]);
			x->setPsswrd(wiersz[3]);
			x->setPrivileges(atoi(wiersz[4]));
			mysql_free_result(idZapytania);
		}
		return x;
	}
	else
	{
		cout << "Error, update failed:" << mysql_errno(db_conn) << endl;
	}
	delete x;
}

transaction::~transaction()
{
	mysql_close(db_conn);
}
