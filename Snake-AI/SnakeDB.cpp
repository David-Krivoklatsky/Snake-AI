#include "SnakeDB.hpp"

void DB::connectDB(sql::mysql::MySQL_Driver* driver, sql::Connection* con){
	driver = sql::mysql::get_driver_instance(); 
	con = driver->connect("tcp://127.0.0.1:3306", "root", "snake");

	con->setSchema("snakedb");
}

void DB::noteScore(int score, std::string nick, sql::Statement* stmt, sql::ResultSet* res){
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
}
