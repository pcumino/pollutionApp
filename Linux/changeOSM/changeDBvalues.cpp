#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]){
}

// "(SELECT id FROM planet_osm_nodes WHERE lat BETWEEN -15585000 AND -15584000) UNION ALL (SELECT id FROM planet_osm_nodes WHERE lon BETWEEN -53974000 AND -53972000)"