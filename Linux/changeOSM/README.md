Compile program command:
g++ -I /usr/include/ [FILENAME].cpp -lpqxx -lpq

The osm file is exported to a Postgresql database.
	osm2pgsql --create --database [DATABASENAME] sample_cidadenova_belem.pbf

Then a C++ program modifies the values in the database. It selects the nodes which need to be updated and insert the pollution tag key and value.

After the update the database is imported to a .OSM file.