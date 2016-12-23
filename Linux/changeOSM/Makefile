all:
	# g++ read_osm.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# g++ main.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# g++ osmium_change_tags.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# g++ osmium_pub_names.cpp -o a.out -std=c++11 -pthread -lz -lexpat;
	# ./a.out ../belem_metropole.osm.pbf;

	clear;
	g++ -c ModJson.cpp -o ModJson.o --std=c++11 -lpthread -lz -lexpat -lbz2;
	g++ -c osmHandler.cpp -o osmHandler.o --std=c++11 -lpthread -lz -lexpat -lbz2;
	g++ osmHandler.o ModJson.o -o updateOSM --std=c++11 -lpthread -lz -lexpat -lbz2;
	#./updateOSM sample_umarizal_belem.xml
