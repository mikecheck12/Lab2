#include<iostream>
#include<set>
#include<fstream>
#include<algorithm>
#include<string>
#include<sstream>
#include<map>
#include<vector>

using namespace std;

void makeLower(string& word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void cleanLine(string& line) {

	for (int i = 0; i <= line.length(); i++) {
		if (isalpha(line[i]) == 0) {
			line[i] = ' ';
		}
	}
}

void spellCheck(string& line, set<string> dictionary, map<string, vector<int>>& misspelledWords, int lineNum) {

	stringstream ss;
	string temp;

	ss << line;
	while (ss >> temp) {
		if (dictionary.count(temp) == 0) {
			misspelledWords[temp].push_back(lineNum);
		}
	}
}

void printIndex(map<string, vector<int>> misspelledWords, char* argv[]) {

    ofstream out;
    out.open(argv[3]);

	for (auto it = misspelledWords.begin(); it != misspelledWords.end(); it++)
	{
                out << it->first << ":";

		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                        out << " "<< *it2;
		}
                out << endl;
	}
        out.close();
}

int main(int argc, char* argv[]){

	set<string> dictionary;
	vector<int> listLine;
	map<string, vector<int>> misspelledWords;
	string word;
	string line;
	
	int lineNum = 0;

	//Open and retrieve dictionary info
	ifstream in;
        in.open(argv[1]);

	while (in >> word){
		makeLower(word);
		dictionary.insert(word);
	}

	in.close();

	//cerr << dictionary.size() << endl;
	//cerr << dictionary.count("bugs") << endl;

	//Open and retrieve document info
        in.open(argv[2]);

	/*
	if (in.is_open()) {
		cerr << "open" << endl;
	}	
	*/

	while (getline(in, line)) {
		lineNum++;
		makeLower(line);
		cleanLine(line);
		//cerr << line << endl;
		spellCheck(line, dictionary, misspelledWords, lineNum);
	}

	in.close();

        //output misspelled words

        printIndex(misspelledWords, argv);

	//cerr << misspelledWords.size() << endl;


	return 0;

}
