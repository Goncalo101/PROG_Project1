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

void capitalize(string &word)
{
	//STL way: transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );

	for (char &c : word) {
		c = static_cast<unsigned char>(toupper(c));
	}
}

///////////////////////////////////////////////////////////////////////////////////
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

void guessWord(vector<string> wordList)
{
	bool won = false;
	int tries = 3;
	string answer;

	cout << "Picking random word..." << endl;
	string word = wordList[rand() % wordList.size()];

	cout << "Scrambling..." << endl;
	string scrambledWord = scramble(split(word));

	cout << word << endl;

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
//Reads the a set of letters inputed by the user
vector<char> readSet()
{
	vector<char> letterVector;
	char letter;
	bool anotherLetter = true;

	cout << "Please insert a set of letters, separated by 'space' (Insert '0' to end set): " << endl;
	while (anotherLetter) {
		cin >> letter;
		if (letter == '0') {
			anotherLetter = false;
		}
		else {
			letterVector.push_back(letter);
		}
	}

	return letterVector;
}


string join(vector<char> letterVector)
{
	string word = "";
	for (size_t i = 0; i < letterVector.size(); i++) {
		word += letterVector[i];
	}
	return word;
}

////////////////////////////////////////////////////////////////////////////
//swaps two chars in a vector with indexes X and Y
void swapElements(string &letterVector, int x, int y)
{
	char temp = letterVector[x];
	letterVector[x] = letterVector[y];
	letterVector[y] = temp;
}

/////////////////////////////////////////////////////////////////////////////
//Updated 'wordList' so that each 'word' appears only once
void removeDuplicates(vector<string> &wordList)
{
	wordList.erase(unique(wordList.begin(), wordList.end()), wordList.end());
}

vector<string> possibleConstructions(vector<char> letterVector) {
	vector<string> possibleConstructionsVector;
	string word = join(letterVector);
	capitalize(word);

	int length = letterVector.size();

	for (int j = 1; j <= length; j++) {
		for (int i = 0; i < length - 1; i++) {
			swapElements(word, i, i + 1);
			possibleConstructionsVector.push_back(word);
		}
	}

	removeDuplicates(possibleConstructionsVector);
	return possibleConstructionsVector;
}

vector<string> validWords(vector<string> wordList, vector<string> wordsVector) {
	vector<string> validWordsVector;
	string possibleWord;
	
	for (size_t i = 0; i < wordsVector.size(); i++) {
		possibleWord = wordsVector[i];
		if (exists(wordList, possibleWord)) {
			validWordsVector.push_back(possibleWord);
		}
	}
	return validWordsVector;
}

void buildWords(vector<string> wordList)
{
	vector<char> letterVector = readSet();
	string letters = join(letterVector);

	cout << "Building word possibilities..." << endl;
	vector<string> possibleConstructionsVector = possibleConstructions(letterVector);

	for (size_t i = 0; i < possibleConstructionsVector.size(); i++) {
		cout << possibleConstructionsVector[i] << endl;
	}

	cout << "Verifying valid words..." << endl;
	vector<string> validWordsVector = validWords(wordList, possibleConstructionsVector);

	if (validWordsVector.size()) {
		cout << "Valid words you can form with the letters " << letters << ": " << endl;
		for (size_t i = 0; i < validWordsVector.size(); i++) {
			cout << validWordsVector[i] << endl;
		}
	}
	else {
		cout << "You can not form any valid word with the letters: " << letters << endl;
	}
}

void showMenu(vector<string> wordList)
{
	int option = 0;

	// Should we allow the player to keep playing after an option is selected? If yes, this works.
	while (true) {
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
		case 1:
			checkWordInVector(wordList);
			cout << endl;
			break;

		case 2:
			guessWord(wordList);
			cout << endl;
			break;
		case 3:
			buildWords(wordList);
			cout << endl;
			break;
		case 5:
			searchWithWildcard(wordList);
			cout << endl;
			break;

		case 6:
			exit(0);

		default:
			cout << "Please insert a valid option" << endl;
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