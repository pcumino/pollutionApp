#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <iostream>
#include <string>
#include <pqxx/pqxx> 
#include <vector>
using namespace std;

class DbManager{
private:
	string user;
	string passwd;

	string database;
	string table;
	string sql;
	vector<int> responseTable;
public:
	DbManager();
	void setDatabase(string);
	void setTable(string);

	string getDatabase();
	string getTable();

	void setQuery(string);
	vector<int> getResponse();

	void run();
};

#endif
