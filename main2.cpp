#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Namespaces are bad practice, but we're not using more than this namespace so it's ok
using namespace std;

//struct Dictionary {
//    string inputFileName;
//    string outputFileName;
//
//    vector<string> wordVector;
//};

void greetUser(ifstream &input, ofstream &output, string &fileName)
{
    string greeting = "EXTRACTION OF WORD LIST FROM DICTIONARY";
    string outFileName;

    cout << greeting << endl;
    cout << string(greeting.length(), '=') << endl << endl;

    cout << "Insert dictionary input name: ";
    input.open("29765-8.txt");

//     Commented for debug purposes
//     cin >> fileName;
//
//     input.open(fileName);

    if (!input.is_open()) {
        cerr << "Opening of input file failed. Does it exist?" << endl;
        exit(1);
    }

    cout << "Insert output file name: ";
    output.open("out.txt");
    // Commented for debug purposes
    // cin >> outFileName;
    //
    // output.open(outFileName);

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

        } else if (line[i] == ';') {
            if(!word.empty()) {
                wordList.push_back(word);
            }

            word.clear();

            i++;

            continue;

        } else if (isalpha(line[i])) {
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

    return wordVector;
}

int main()
{
    // The following code implements a greet-extract strategy
    ifstream input;
    ofstream output;

    string inputFileName;

    greetUser(input, output, inputFileName);

    extractWords(input, output, inputFileName);
    // Displays all words. For debugging purposes only.
    // for (string s : extractWords(input, output, inputFileName))
    // cout << s << endl;

    // wordVector = extractWords(input, output, inputFileName);
    // cout << "Number of words = " << wordVector.length() << endl;
    // cout << "Sorting..." << endl;
    // wordVector = quickSort(wordVector);
    // cout << "Removing duplicates..." << endl;
    // wordVector = removeDuplicates(wordVector);
    // cout << "Number of words without duplicates = " << wordVector.length() << endl;
    // saveWords(wordVector, outputFileName);


    return 0;
}
