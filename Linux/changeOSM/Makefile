all:
	# g++ osmHandler.cpp --std=c++11 -lpthread -lz -lexpat -lbz2;
	# ./a.out input.osm

	# g++ -I/Library/PostgreSQL/9.5/include db.cpp -c -g -o db.o #OSX
	# g++ -L/Library/PostgreSQL/9.5/lib db.o -lpq -o db #OSX

	clear;
	g++ -I /usr/include/ changeDBvalues.cpp -lpqxx -lpq -o updateOSM #Linux
	./updateOSM