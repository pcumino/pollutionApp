#include "DbManager.h"
using namespace std;

DbManager::DbManager(){}

void DbManager::setDatabase(string val){database = val;}
void DbManager::setTable(string val){table = val;}
string DbManager::getDatabase(){return database;}
string DbManager::getTable(){return table;}

void DbManager::setQuery(string val){
	sql = val;
}

vector<int> DbManager::getResponse(){
	vector<int> i;
	return i;
}

void DbManager::run(){
	try{
		connection C("dbname="+database);
		if (C.is_open()) {
			cout << "Opened database successfully: " << C.dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
			return 1;
		}
		/* Create SQL statement */
		// sql = "(SELECT id FROM planet_osm_nodes WHERE lat BETWEEN -15585000 AND -15584000) UNION ALL (SELECT id FROM planet_osm_nodes WHERE lon BETWEEN -53974000 AND -53972000)";
		/* Create a non-transactional object. */
		nontransaction N(C);
		/* Execute SQL query */
		result R( N.exec( sql ));

		/* List down all the records */
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			cout << "ID = " << c[0].as<int>() << endl;
		}
		cout << "Operation done successfully" << endl;

		C.disconnect ();
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
		return 1;
	}
}