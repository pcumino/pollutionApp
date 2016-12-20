#include "ModJson.h"

using namespace std;

int main(){
	ModJson jsontool;
	jsontool.setFile("sensorData.json");
	// jsontool.printList();
	vector< vector<string> > vec = jsontool.getVecList();
	//jsontool.printList(vec);
	cout << "changing OSM..." << endl;
}
