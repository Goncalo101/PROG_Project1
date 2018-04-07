#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void greetUser(ifstream &input, string &inputFileName, vector<string> &wordList)
{
	string greeting = "PLAYING WITH WORDS";
	string word;

	cout << greeting << endl;
	cout << string(greeting.length(), '=') << endl << endl;

	//Unsure if this is the right aproach
	cout << "Insert the name of the file containing the word list: ";

	cin >> inputFileName;

	input.open(inputFileName);

	if (!input.is_open()) {
		cerr << "Opening of input file failed. Does it exist?" << endl;
		exit(1);
	}

	cout << "Extracting words from " << inputFileName << endl;

	while (getline(input, word)) {
		wordList.push_back(word);
	}
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

void capitalize(string &word)
{
    //STL way: transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );

    for (char &c : word) {
        c = static_cast<u_char>(toupper(c));
    }
}

///////////////////////////////////////////////////////////////////////////////////
bool exists(vector<string>& wordList, string word) {
	bool result = false;

    // Program needs to be case insensitive so, make sure that the word is capitalized before searching for it
    capitalize(word);

	int pos = searchVector(wordList, word, 0, wordList.size() - 1);
	if (pos != -1) {
		result = true;
	}
	return result;
}
///////////////////////////////////////////////////////////////////////////////////
void firstGame(vector<string> &wordList)
{
	
	string word;

	cout << "Insert a word: ";
	cin >> word;

	cout << "Searching for " << word << endl;
	bool valueExists = exists(wordList, word);

	if (valueExists) {
		cout << "The word " << word << " belongs to the Word List" << endl;
	}
	else {
		cout << "The word " << word << " does not belong to the Word List" << endl;
	}
}

void showMenu(vector<string> wordList)
{
    bool start = true;
    u_int option;

    // Should we allow the player to keep playing after an option is selected? If yes, this works.
    while (start) {
        // The option names will be improved in future versions of this program
        cout << "1: Check if a word belongs to the word list" << endl;
        cout << "2: Guess a word" << endl;
        cout << "3: Build words" << endl;
        cout << "4: Build Words 2" << endl;
        cout << "5: Show words" << endl;
        cout << "6: Exit" << endl;
        cout << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1:
                firstGame(wordList);
                cout << endl;
            case 2:
                // secondGame(wordList);
                continue;
            case 6:
                exit(0);
            default:
                cout << "Please insert a valid option" << endl;
        }

    }
}

int main()
{
	vector<string> wordList;
	ifstream infile;
	string inputFileName;

	srand(static_cast<unsigned int>(time(NULL)));

	greetUser(infile, inputFileName, wordList);

	showMenu(wordList);

	return 0;
}