#include "ModJson.h"

ModJson::ModJson(){
	/*
	cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "=> new class 'ModJson' created" << endl;
	*/
}
ModJson::~ModJson(){
	/*
	cout << "=> a class 'ModJson' destroyed" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	*/
}
void ModJson::setFile(string name){
	// cout << "=> setFile" << endl;
	fileName = name;
	ModJson::openFile();
}
string ModJson::getFileName(){
	// cout << "=> getFileName" << endl;
	return fileName;
}
void ModJson::openFile(){
	//cout << "=> openFile" << endl;
	ifstream f(fileName.c_str());
	if(!f.good())
		cout << fileName << " doesn't exist" << endl;
	else{
		string contents((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

		fileData = contents;
		if(fileData.length() <= 0)
			cout << "Sorry, " << fileName << " is empty" << endl;
		else
			ModJson::jsonToList();
	}
}
string ModJson::getFileData(){
	// cout << "=> getFileData" << endl;
	if(fileData.length() <= 0)
		return "["+fileName+" is empty]";
	else
		return fileData;
}
void ModJson::jsonToList(){
	// cout << "=> jsonToList" << endl;
	string data = fileData;
	data.erase(remove(data.begin(), data.end(), '"'), data.end());
	data.erase(remove(data.begin(), data.end(), '{'), data.end());
	data.erase(remove(data.begin(), data.end(), '['), data.end());
	data.erase(remove(data.begin(), data.end(), ']'), data.end());
	data.erase(remove(data.begin(), data.end(), ':'), data.end());
	replace( data.begin(), data.end(), '}', '\n');

	for (int i = 0; i < data.length(); i++){
		if (data[i] == '\n' && data[i+1] == ','){
			data[i] = ' ';
			data[i+1] = '\n';
		}
	}

	data = ModJson::replaceSubs(data, "id", "");
	data = ModJson::replaceSubs(data, "values", "");
	data = ModJson::replaceSubs(data, " ", "");

	vector<string> line;

	line = ModJson::splitToVector(data, '\n');
	for (int i = 0; i < line.size(); ++i){
		vector<string> word = ModJson::splitToVector(line.at(i),',');
		list.push_back(word);
	}
}
vector< vector<string> > ModJson::getVecList(){
	// cout << "=> getVecList" << endl;
	return list;
}
string ModJson::replaceSubs(string target, string subs, string newVal){
	string::size_type n = 0;
	while ( ( n = target.find( subs, n ) ) != string::npos ){
		target.replace( n, subs.size(), newVal );
		// target.erase( n, subs.size(), subs );
		n += newVal.size();
	}
	return target;
}
vector<string> ModJson::splitToVector(string input, char delimiter){
	vector<string> output;
	istringstream ss(input);
	string token;

	while(getline(ss, token, delimiter)) {
		output.push_back(token);
	}

	return output;
}
void ModJson::printList(vector< vector<string> > text){
	// cout << "=> printList" << endl;
	for (int i = 0; i < text.size(); ++i){
		for(int j = 0; j < text.at(i).size(); j++){
			cout << text[i][j] << "\t";
		}
		cout << "\n";
	}
}
void ModJson::printList(){
	/*
	Same function as the previous 'printList(vector< vector<string> >)'.
	However this is used when there ar no parameter input
	*/
	// cout << "=> printList" << endl;
	cout << "Showing internal list: " << endl;
	for (int i = 0; i < list.size(); ++i){
		for(int j = 0; j < list.at(i).size(); j++){
			cout << ">" << list[i][j] << "\t";
		}
		cout << endl;
	}
}
