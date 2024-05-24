#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

class DB {
private:
	sql::mysql::MySQL_Driver *driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;

	void connectDB(sql::mysql::MySQL_Driver*, sql::Connection*);

	void noteScore(int, std::string, sql::Statement*, sql::ResultSet*);
};

