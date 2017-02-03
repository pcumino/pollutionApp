all:
	clear;
	# g++ read_osm.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	g++ osmHandler.cpp -o a.out --std=c++11 -lpthread -lz -lexpat -lbz2;
	# g++ osmium_change_tags.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# g++ osmium_pub_names.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# ./a.out ../belem_metropole.osm.pbf;
	# ./a.out ../routing_services/OSRM/osrm-backend-5.4.0/build/sample2_belem_pollution.pbf