#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void greetUser(ifstream &input, ofstream &output, string &inputFileName, string &outputFileName)
{
	string greeting = "EXTRACTION OF WORD LIST FROM DICTIONARY";

	cout << greeting << endl;
	cout << string(greeting.length(), '=') << endl << endl;

	cout << "Insert dictionary input name: ";

	cin >> inputFileName;

	input.open(inputFileName);

	if (!input.is_open()) {
		cerr << "Opening of input file failed. Does it exist?" << endl;
		exit(1);
	}

	cout << "Insert output file name: ";
	cin >> outputFileName;

	output.open(outputFileName);

	cout << endl;
}

// This function returns the index of the next semicolon if it exists.
// Returns the length of the line if no semicolon is found.
size_t findNextSemiColon(size_t i, string line)
{
	for (size_t j = i; j < line.length(); j++) {
		if (line[j] == ';') return j - 1;
	}

	return line.length();
}

// Each element of the line will be made an element of a vector (ignores elements that have hyphens or whitespaces).
// Example:
// Considering string line = "ABA; ABB; ABC; AB-D; AB E", split(line) should return a vector<string>
// like this: {"ABA", "ABB", "ABC"}
vector<string> split(string line)
{
	vector<string> wordList;
	string word;

	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == ' ' || line[i] == '-') {
			word.clear();

			i = findNextSemiColon(i, line);

		}
		else if (line[i] == ';') {
			if (!word.empty()) {
				wordList.push_back(word);
			}

			word.clear();

			i++;

			continue;

		}
		else if (isalpha(line[i])) {
			word.push_back(line[i]);

		}
	}

	if (!word.empty()) {
		wordList.push_back(word);
	}

	return wordList;
}

// Parses line in search of actual entries. Returns the number of words added to wordList.
size_t parseLine(string line, vector<string> &wordList)
{
	// Ignore all lines containing lower case characters, asterisks, dashes and/or apostrophes.
	for (char c : line) {
		if (islower(c) || c == '*' || c == '.' || line == "\r")
			return 0;
	}

	// If the line doesn't qualify for being ignored, a split will be attempted.
	vector<string> properLine = split(line);

	// Add the newly split string (do not forget it's actually a vector) to the end of the existing wordList.
	// No vector shall be concatenated to wordList if split(line) returns an empty vector. Potentially unnecessary.
	if (!properLine.empty()) {
		wordList.insert(wordList.end(), properLine.begin(), properLine.end());
	}

	return properLine.size();
}

vector<string> extractWords(ifstream &input, ofstream &output, string fileName)
{
	vector<string> wordVector;
	string line;

	char currentLetter = '\0';
	int i = 1;

	cout << "Extracting words from " << fileName << endl;

	while (getline(input, line)) {
		size_t numberOfElementsAdded = parseLine(line, wordVector);

		if (i % 100 == 0) {
			cout << ".";
		}

		if (numberOfElementsAdded) {
			char temp = line[0];


			// The input file contains a phrase called CONSOLATION RACE, which is split between two lines.
			// This causes the program to consider CONSOLATION and RACE two different words and will thus, print
			// R and then carry on with all the Cs. Is it really necessary to make an exception for this phrase?
			if (currentLetter != temp && (isalpha(temp) || line.substr(0, line.find_first_of('\r')).length() == 1)) {
				currentLetter = temp;
				i = 1;

				cout << endl << currentLetter << endl;
			}

			i += numberOfElementsAdded;
		}
	}

	input.close();
	return wordVector;
}
/////////////////////////////////////////////////////////////////////////////
//searches in 'wordList' for 'word' and returns its index if 'word' is found
//if there's more than one 'word' in 'wordList' the function returns the index of the last ocurrency
//Uses a Binary Search method
int searchVector(vector<string> wordList, string word, size_t left, size_t right) {
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
	return -1; //if the word does not exist in the wordList vector, the function returns -1;
}

/////////////////////////////////////////////////////////////////////////////
//Uses 'searchVector' funtion to search for words equal to the element of 'wordList' in the position 'index'
//If 'searchVector' returns -1, it means that 'wordList' only has one word equal to the element in the position 'index'
//so 'index' is incremented so that 'searchVector' evaluates the next element of 'wordList'
void removeDuplicates(vector<string> &wordList)
{
//    size_t index = 0;
//	while (index < wordList.size()) {
//        string word = wordList[index];
//        int posWord = searchVector(wordList, word, index + 1, wordList.size() - 1);
//        if (posWord != -1) //true if searchVector found a duplicate of 'word' in 'wordList'
//            wordList.erase(wordList.begin() + posWord);
//        else index++;
//
//        if (index % 1000 == 0) cout << index << endl;
// }

    wordList.erase(unique(wordList.begin(), wordList.end()), wordList.end());
}

/////////////////////////////////////////////////////////////////////////////
//returns a vector with each element being a line from the input file
vector<string> wordsToVector(ifstream &infile)
{
	string word;
	vector<string> wordList;
	while (getline(infile, word)) {
		wordList.push_back(word);
	}
	return wordList;
}

////////////////////////////////////////////////////////////////////////////
//swaps two string strings in a vector with indexes X and Y
//used to sort vector with the names
void swapElements(vector<string> &wordList, int x, int y)
{
	string temp = wordList[x];
	wordList[x] = wordList[y];
	wordList[y] = temp;
}

/////////////////////////////////////////////////////////////////////////////
//sorts the vector with the names in alphabetic order - quick sort method used
void sortVector(vector<string> &wordList, int left, int right)
{
	int i = left; //left index
	int j = right; //right index
	string pivot = wordList[(left + right) / 2]; //middle element of vector chosen as pivot

	while (i <= j) {
		while (wordList[i] < pivot)
			i++;
		while (wordList[j] > pivot)
			j--;
		if (i <= j) {
			swapElements(wordList, i, j);
			i++;
			j--;
		}
	}
	if (left < j)
		sortVector(wordList, left, j);
	if (i < right)
		sortVector(wordList, i, right);
}

/////////////////////////////////////////////////////////////////////////////
//writes the words from the sorted vector to the output file
void writeEntries(vector<string> wordList, ofstream &outfile)
{
	for (size_t i = 0; i < wordList.size(); i++) {
		outfile << wordList[i] << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
int main()
{
	vector<string> wordList;
	string inputFileName;
	string outputFileName;
	ifstream infile;
	ofstream outfile;

	greetUser(infile, outfile, inputFileName, outputFileName);

	wordList = extractWords(infile, outfile, inputFileName);
	auto length = static_cast<int>(wordList.size());

        // Ending sequence
        cout << endl << "Number of simple words = " << length << endl;

        cout << "Sorting words..." << endl;
        sortVector(wordList, 0, length - 1);

        cout << "Removing duplicates..." << endl;
        removeDuplicates(wordList);

        cout << "Number of words without duplicates = " << wordList.size() << endl;

        cout << "Saving words to " << outputFileName << " ..." << endl;
        writeEntries(wordList, outfile);

        cout << "Done" << endl;
	return 0;
}
