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
//Searches in 'wordList' for 'word' and returns true if 'word' is found
//Uses a Binary Search method
bool searchVector(vector<string> wordList, string word, int left, int right)
{
	if (left <= right) {
		int posMid = left + (right - left) / 2;
		string mid = wordList[posMid];
		if (word == mid)
			return true;
		if (word < mid)
			return searchVector(wordList, word, left, posMid - 1);
		if (word > mid)
			return searchVector(wordList, word, posMid + 1, right);
	}
	return false; //if the word does not exist in the wordList vector, the function returns false
}

//Takes a string and puts all its characters in uppercase
void capitalize(string &word)
{
	//STL way: transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );
	for (char &c : word) {
		c = static_cast<unsigned char>(toupper(c));
	}
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

	capitalize(word);

	cout << "Searching for " << word << endl;

	if (searchVector(wordList, word, 0, wordList.size() - 1)) {
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

	while (!vector.empty()) {
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

//Searches for 'letter' in 'word'. If found, returns its index. Otherwise, returns '-1'
size_t searchWord(string word, char letter) {
	for (size_t i = 0; i < word.length(); i++) {
		if (word[i] == letter) { return i; }
	}
	return -1;
}

//Returns true if 'currentWord' and 'letters' match. 
//This occurs if both strings have the same number of characters and the same characters but distributed diferently thorugh out the string
bool wordMatch(string currentWord, string letters) {
	int len = letters.length();
	size_t pos;

	if (currentWord.length() == len) {
		while (letters.length()) {
			pos = searchWord(currentWord,letters[0]);
			if (pos == -1) {
				return false;
			}
			else {
				letters.erase(letters.begin());
				currentWord.erase(currentWord.begin() + pos);
			}
		}
		return true;
	}
	return false;
}

//returns a vector of strings with all valid words possible to form with 'letters'
vector<string> wordsConstructor(vector<string> wordList, string letters) {
	vector<string> validWords;
	string currentWord;
	char currentLetter;

	for (size_t i = 0; i < wordList.size(); i++) {
		currentWord = wordList[i];
		
		if (wordMatch(currentWord, letters)) {
			validWords.push_back(currentWord);
		}
	}
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

// Calculates the total number of ocurrences of all letters in the wordList
vector<int> getOcurrences(vector<string> wordList)
{
	vector<int> ocurrences(26);

	for (int i : ocurrences)
		i = 0;

	for (string s : wordList) {
		for (char c : s) {
			++ocurrences[c - 65];
		}
	}

	return ocurrences;
}

string getLongestWord(vector<string> wordList)
{
    string max = wordList[0];

    for (int i = 1; i < wordList.size(); ++i) {
        if (wordList[i].length() > max.length())
            max = wordList[i];
    }

    return max;
}

void createSet(vector<string> wordList)
{
	// Initialization
	vector<char> letterVector;
	static vector<int> ocurrences = getOcurrences(wordList);
	int offset = rand() % 26 + 65; // Pick a random letter
	auto firstLetter = char(offset);

	string word;
    // Use in STL-version
	// max_element has the following prototype: ForwardIt max_element( ForwardIt first, ForwardIt last, Compare comp );
    // If no argument of type compare is given, max_element will compare with a function that compares strings (in this case)
    // and checks which is the "greatest". However, we want to change max_element to return the longest word, not the greatest
    // which requires us to implement our own Compare function.
    // static string longestWord = *(max_element(wordList.begin(), wordList.end(), [] (const string& s1, const string& s2) {
    //                                    return s1.length() < s2.length(); }));
    static string longestWord = getLongestWord(wordList);
	unsigned long stringLength = rand() % longestWord.length();
	
	letterVector.push_back(firstLetter);
	letterVector.push_back(firstLetter);

	for (int i = 0; i < stringLength; ++i) {
		auto letter = rand() % 26;

		if (letter == (offset - 65)) continue; // Checks if the random letter is the first letter, continues if it is, to keep the set as random as possible

        int numberOfWordsAdded = ocurrences[letter] /  ocurrences[offset - 65];
        i += numberOfWordsAdded;

		for (; numberOfWordsAdded > 0; --numberOfWordsAdded) {
            letterVector.push_back(char(letter + 65));
        }
	}

	word = scramble(letterVector);

	cout << "Your set of letters: ";
	for (char c : word) {
		cout << c;
	}

	cout << endl << "Build a valid with some or all letters: ";
	cin >> word;

	searchWithWildcard(wordList, word) ? cout << "Word found" : cout << "Word not found";
//	if (searchWithWildcard(wordList, word)) {
//		cout << "Word found";
//	} else {
//		cout << "Word not found";
//	}
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
		cout << "4: Build Words from set" << endl;
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