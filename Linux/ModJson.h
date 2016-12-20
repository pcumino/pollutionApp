#ifndef MODJSON_H
#define MODJSON_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class ModJson{
private:
	string fileName;
	string fileData;
	vector<string> splitToVector(string, char);
	vector< vector<string> > list;
	void jsonToList();
	string replaceSubs(string, string, string);
public:
	ModJson();
	~ModJson();
	
	void setFile(string name);
	string getFileName();
	void openFile();
	string getFileData();

	vector< vector<string> > getVecList();
	void printList(vector< vector<string> >);
	void printList();
};
#endif