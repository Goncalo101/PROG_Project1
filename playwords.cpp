#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

void greetUser(ifstream &input, string &inputFileName, vector<string> &wordList)
{
	string greeting = "PLAYING WITH WORDS";
	string word;

	//Title
	cout << string(greeting.length(), '=') << endl;
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
//Searches in 'wordList' for 'word' and returns its index if 'word' is found
//If there's more than one 'word' in 'wordList' the function returns the index of the last ocurrency
//Uses a Binary Search method
int searchVector(vector<string> wordList, string word, int left, int right)
{
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

//Takes a string and puts all its character in uppercase
void capitalize(string &word)
{
	//STL way: transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );
	for (char &c : word) {
		c = static_cast<unsigned char>(toupper(c));
	}
}

///////////////////////////////////////////////////////////////////////////////////
//Returns true if 'word' is present in 'wordList'
//Uses searchVector function to get the index of the word being searched
bool exists(vector<string> &wordList, string word)
{
	bool result = false;

	// Program needs to be case insensitive so, make sure that the word is capitalized before searching for it
	capitalize(word);

	int pos = searchVector(wordList, word, 0, wordList.size() - 1);

	if (pos != -1) {
		result = true;
	}
	return result;
}

void showVector(vector<string> wordsVector) {
	for (size_t i = 0; i < wordsVector.size(); i++) {
		cout << wordsVector[i] << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////
void checkWordInVector(vector<string> &wordList)
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

//////////////////////////////////////////////////////////////////////////
// WildcardMatch
// str - Input string to match
// strWild - Match mask that may contain wildcards like ? and *
//
// A ? sign matches any character, except an empty string.
// A * sign matches any string inclusive an empty string.
// Characters are compared caseless.
//
// ADAPTED FROM:
// https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function
bool wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild) {
		// Single wildcard character
		if (*strWild == '?') {
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*') {
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else {
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}

void searchWithWildcard(vector<string> vector)
{
	string sequence;

	cout << "Insert a string with wildcards: ";
	cin >> sequence;

	for (string s : vector) {
		if (wildcardMatch(s.c_str(), sequence.c_str()))
			cout << s << endl;
	}
}

bool searchWithWildcard(vector<string> vector, string word)
{
	for (string s : vector) {
		if (wildcardMatch(s.c_str(), word.c_str())) {
			return true;
		}
	}

	return false;
}


// Creates a vector of chars of a given word, each element is a char
vector<char> split(string word)
{
	vector<char> charVector;

	for (char c : word) {
		charVector.push_back(c);
	}

	return charVector;
}

// Scrambles the word taking into account the vector of split words produced by split
string scramble(vector<char> vector)
{
	string newWord;

	while (vector.size()) {
		unsigned long index = rand() % vector.size();

		newWord.push_back(vector[index]);
		vector.erase(vector.begin() + index);
	}

	return newWord;
}

//Second Game
void guessWord(vector<string> wordList)
{
	bool won = false;
	int tries = 3;
	string answer;

	cout << "Picking random word..." << endl;
	string word = wordList[rand() % wordList.size()];

	cout << "Scrambling..." << endl;
	string scrambledWord = scramble(split(word));

	while (tries) {
		cout << "Your word is: " << scrambledWord << endl;
		cout << "Guess the right word (you have " << tries << " more tries): ";
		cin >> answer;
		cout << endl;

		capitalize(answer);

		if (answer == word) {
			cout << "You won!" << endl;
			won = true;
			break;

		}
		else {
			--tries;
		}
	}

	if (!won) {
		cout << "You lost! The word was: " << word << endl;
	}
}

////////////////////////////////////////////////////////////////////////////
//GAME: BUILD WORDS
////////////////////////////////////////////////////////////////////////////
//Reads a set of letters inputed by the user
bool validInput(string letters)
{
	for (char &c : letters) {
		if (!isalpha(c)) {
			return false;
		}
	}
	return true;
}

string readSet()
{
	string letters;
	cin >> letters;
	capitalize(letters);

	if (!validInput(letters)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input. Please insert only alphabetic letters" << endl;
		letters = readSet();
	}

	return letters;
}

//returns a vector of strings with all possible combinations of the set of letters in 'letterVector'
vector<string> wordsConstructor(vector<string> wordList, string letters) {
	vector<string> validWords;

	//STL WAY
	sort(letters.begin(), letters.end());
	do
	{
		if (binary_search(wordList.begin(),wordList.end(),letters))
			validWords.push_back(letters);

	} while (next_permutation(letters.begin(), letters.end()));

	return validWords;
}

//Third game
void buildWords(vector<string> wordList)
{
	cout << "Please insert a set of letters (Press ENTER to end set): " << endl;
	string letters = readSet();

	cout << "Building word possibilities and verifying them..." << endl;
	vector<string> validWords = wordsConstructor(wordList, letters);

	if (validWords.size()) {
		cout << "Valid words you can form with the letters " << letters << ": " << endl;
		showVector(validWords);
	}
	else {
		cout << "You can not form any valid word with the letters: " << letters << endl;
	}
}

void createSet(vector<string> wordList)
{
	vector<char> letterVector;
	string word;
	string max_element = *(minmax_element(wordList.begin(), wordList.end()).second);

	for (int i = 0; i < max_element.length(); ++i) {
		letterVector.push_back(char(rand() % 25 + 65));
	}

	for (char c : letterVector) {
		cout << c;
	}

	cout << endl << "Build a valid word: ";
	cin >> word;

	if (searchWithWildcard(wordList, word)) {
		cout << "Word found" << endl;

	}
	else {
		cout << "Word not found" << endl;
	}

}

void showMenu(vector<string> wordList)
{
	unsigned char option = '0';

	// Should we allow the player to keep playing after an option is selected? If yes, this works.
	while (true) {
		cout << endl;
		cout << string(8, '-') << endl;
		cout << "| MENU |" << endl;
		cout << string(8, '-') << endl;
		// The option names will be improved in future versions of this program
		cout << "1: Check if a word belongs to the word list" << endl;
		cout << "2: Guess a word" << endl;
		cout << "3: Build words" << endl;
		cout << "4: Build Words 2" << endl;
		cout << "5: Show words with wildcard" << endl;
		cout << "6: Exit" << endl;
		cout << "Select an option: " << flush;
		cin >> option;

		switch (option) {
		case '1':
			checkWordInVector(wordList);
			cout << endl;
			break;

		case '2':
			guessWord(wordList);
			cout << endl;
			break;

		case '4':
			createSet(wordList);
			cout << endl;
			break;

		case '3':
			buildWords(wordList);
			cout << endl;
			break;

		case '5':
			searchWithWildcard(wordList);
			cout << endl;
			break;

		case '6':
			exit(0);

		default:
			cout << "Please insert a valid option!" << endl;
			cin.clear();
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