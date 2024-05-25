#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

class DB {
public:
    void connectDB(sql::mysql::MySQL_Driver* driver);
    void noteScore(int score, const std::string& , std::string&);
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
};


