#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]){
	string sql;
	try{
		connection C("dbname=gis");
		if (C.is_open()) {
			cout << "Opened database successfully: " << C.dbname() << endl;
			cout << " - - - - - - " << endl;
		} else {
			cout << "Can't open database" << endl;
			return 1;
		}
		/* Create SQL statement */
		sql = "(SELECT id FROM planet_osm_nodes WHERE lat BETWEEN -15585000 AND -15584000) UNION ALL (SELECT id FROM planet_osm_nodes WHERE lon BETWEEN -53974000 AND -53972000)";

		/* Create a non-transactional object. */
		nontransaction N(C);
      
		/* Execute SQL query */
		result R( N.exec( sql ));

		/* List down all the records */
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			cout << "ID = " << c[0].as<int>() << endl;
		}
		cout << " - - - - - - " << endl;
		cout << "Operation done successfully" << endl;

		C.disconnect ();
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
		return 1;
	}
}

// "(SELECT id FROM planet_osm_nodes WHERE lat BETWEEN -15585000 AND -15584000) UNION ALL (SELECT id FROM planet_osm_nodes WHERE lon BETWEEN -53974000 AND -53972000)"