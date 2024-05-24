#include "SnakeDB.hpp"

void DB::connectDB(sql::mysql::MySQL_Driver* driver) {
	driver = sql::mysql::get_driver_instance();
	this->con = driver->connect("sql7.freesqldatabase.com", "sql7709024", "DJurJFGeSa");
	//this->con = driver->connect("tcp://127.0.0.1:3306", "root", "snake");
	this->con->setSchema("sql7709024");
}


void DB::noteScore(int score, const std::string& nick) {
	stmt = con->createStatement();
	std::string query = "INSERT INTO scoreboard (Nick, Score) VALUES ('" + nick + "', " + std::to_string(score) + ")";
	std::cout << query << std::endl;
	try {
		stmt->execute(query);
		// SQL operation
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Exception: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
		// Handle the exception
	}
}