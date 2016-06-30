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
	transform(word.begin(), word.end(), word.begin(), tolower);
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

void printIndex(map<string, vector<int>> misspelledWords) {
	for (auto it = misspelledWords.begin(); it != misspelledWords.end(); it++)
	{
		cout << it->first << " : ";

		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}

int main()
{
	set<string> dictionary;
	vector<int> listLine;
	map<string, vector<int>> misspelledWords;
	string word;
	string line;
	
	int lineNum = 0;

	//Open and retrieve dictionary info
	ifstream in;
	in.open("in20a.txt");

	while (in >> word){
		makeLower(word);
		dictionary.insert(word);
	}

	in.close();

	//cerr << dictionary.size() << endl;
	//cerr << dictionary.count("bugs") << endl;

	//Open and retrieve document info
	in.open("in20b.txt");

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

	printIndex(misspelledWords);

	//cerr << misspelledWords.size() << endl;


	system("pause");
	return 0;

}