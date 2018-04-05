#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void greetUser(ifstream &input, string &inputFileName, vector<string> wordList)
{
	string greeting = "PLAYING WITH WORDS";
	string word;

	cout << greeting << endl;
	cout << string(greeting.length(), '=') << endl << endl;

	//Unsure if this is the right aproach
	cout << "Insert the name of the file containing the word list ";

	cin >> inputFileName;

	input.open(inputFileName);

	if (!input.is_open()) {
		cerr << "Opening of input file failed. Does it exist?" << endl;
		exit(1);
	}

	while (getline(input, word)) {
		for (size_t i = 0; i < wordList.size(); i++)
			wordList[i] = word;
	}
		

	return;
}

///////////////////////////////////////////////////////////////////////////////////
//searches in 'wordList' for 'word' and returns its index if 'word' is found
//if there's more than one 'word' in 'wordList' the function returns the index of the last ocurrency
//Uses a Binary Search method
int searchVector(vector<string> wordList, string word, int left, int right) {
	if (left <= right) {
		int posMid = left + (right - left) / 2;
		string mid = wordList[posMid];
		if (word == mid)
			return posMid;
		if (word < mid)
			return searchVector(wordList, word, left, posMid - 1);
		if (word > mid)
			return searchVector(wordList, word, posMid + 1, right);
	}
	return -1; //if the word does not exist in the wordList vector, the function returns -1
}

///////////////////////////////////////////////////////////////////////////////////
bool exists(vector<string> wordList, string word) {
	int pos = searchVector(wordList, word, 0, wordList.size() - 1);
	if (pos != -1)
		return true;
	else return false;
}
///////////////////////////////////////////////////////////////////////////////////
void firstGame(vector<string> wordList) {
	
	string word;

	cout << "Insert a word:" << endl;
	cin >> word;

	bool valueExists = exists(wordList, word);

	if (valueExists)
		cout << "The word " << word << " belongs to the Word List" << endl;
	else
		cout << "The word " << word << " does not belong to the Word List" << endl;
	
	return;
}
int main()
{
	vector<string> wordList;
	ifstream infile;
	string inputFileName;

	greetUser(infile, inputFileName, wordList);
	firstGame(wordList);

	return 0;
}