#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

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

// Functionality similar to that of above but searches numbers
int searchVector(vector<int> numberList, int number, int left, int right)
{
    if (left <= right) {
        int posMid = left + (right - left) / 2;
        int mid = numberList[posMid];
        if (number == mid)
            return posMid;
        if (number < mid)
            return searchVector(numberList, number, left, posMid - 1);
        if (number > mid)
            return searchVector(numberList, number, posMid + 1, right);
    }
    return -1; //if the number does not exist in the wordList vector, the function returns -1
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
    } else {
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
        } else if (*strWild == '*') {
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
        } else {
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

string scramble(string word)
{
    string newWord;

    while (!word.empty()) {
        unsigned long index = rand() % word.size();

        newWord.push_back(word[index]);
        word.erase(word.begin() + index);
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
        cout << "Guess the right word: ";
        cin >> answer;
        cout << endl;

        capitalize(answer);

        if (answer == word) {
            cout << "You won!" << endl;
            won = true;
            break;

        } else {
            --tries;
        }
    }

    if (!won) {
        cout << "You lost! The word was: " << word << endl;
    }
}

// Calculates the total number of ocurrences of all letters in the wordList
vector<int> computeNumberOfOcurrences(vector<string> wordList)
{
    vector<int> ocurrences(26);

    for (int i : ocurrences)
        i = 0;

    for (string s : wordList) {
        for (char c : s) {
            ocurrences[c % 26] = ocurrences[c % 26] + 1;
        }
    }

    return ocurrences;
}

void createSet(vector<string> wordList)
{
    string letters;
    vector<int> ocurrences = computeNumberOfOcurrences(wordList);

    string word;
    string longestWord = *(minmax_element(wordList.begin(), wordList.end()).second);

    int minNumberOfOcurrences = *(minmax_element(ocurrences.begin(), ocurrences.end()).first);

    for (int i = 0; i < longestWord.length(); ++i) {
        if (i == 0) {
            int minNumberPos = searchVector(ocurrences, minNumberOfOcurrences, 0, ocurrences.size() - 1) + 66;
            letters.push_back(char(minNumberPos));
            letters.push_back(char(minNumberPos));
        } else {
            // letters.push_back(char(ocurrences[rand() % ocurrences.size()] % 25 + 65));
            int offset = rand() % 26;
            letters += string(3, char(offset + 66));
            i += ocurrences[offset]/longestWord.length();
        }
    }
    scramble(letters);

    for (char c : letters) {
        cout << c;
    }

    cout << endl << "Build a valid word: ";
    cin >> word;

    if (searchWithWildcard(wordList, word)) {
        cout << "Word found" << endl;

    } else {
        cout << "Word not found" << endl;
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

            case 4:
                createSet(wordList);
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