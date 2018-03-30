#include <iostream>
#include <fstream>
#include <vector>

// Namespaces are bad practice, but we're not using more than this namespace so it's ok
using namespace std;

void greetUser(ifstream &input, ofstream &output, string &fileName)
{
    string greeting = "EXTRACTION OF WORD LIST FROM DICTIONARY";
    string outFileName;

    cout << greeting << endl;
    cout << string(greeting.length(), '=') << endl << endl;

    cout << "Insert dictionary input name: ";
    input.open("input.txt");
    // Commented for debug purposes
    // cin >> fileName;
    //
    // input.open(fileName);

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
unsigned long findNextSemiColon(unsigned long i, string line)
{
    for (unsigned long j = i; j < line.length(); j++) {
        if (line[j] == ';') return j - 1;
    }

    return line.length();
}

// Each element of the line will be made an element of a vector.
// Example:
// Considering string line = "ABA; ABB; ABC", split(line) should return a vector<string>
// like this: {"ABA", "ABB", "ABC"}
vector<string> split(string line)
{
    vector<string> wordList;
    string word;

    for (unsigned long i = 0; i < line.length(); i++) {
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

void parseLine(string line, vector<string> &wordList)
{
    // Ignore all lines containing lower case characters, asterisks, dashes and/or apostrophes.
    for (char c : line) {
        if (islower(c) || c == '*' || c == '\'' || c == '.')
            return;
    }

    // If the line doesn't qualify for being ignored, a split will be attempted.
    vector<string> properLine = split(line);

    // Add the newly split string (do not forget it's actually a vector) to the end of the existing wordList.
    // No vector shall be concatenated to wordList if split(line) returns an empty vector. Potentially unnecessary.
    if (!properLine.empty()) {
        wordList.insert(wordList.end(), properLine.begin(), properLine.end());
    }
}

vector<string> extractWords(ifstream &input, ofstream &output, const string &fileName)
{
    vector<string> wordList;
    string line;
    cout << "Extracting words from " << fileName << endl;


    // Doing while (!input.eof()) without reading first can bring problems on Windows.
    getline(input, line);
    parseLine(line, wordList);

    while (!input.eof()) {
        getline(input, line);
        parseLine(line, wordList);
    }

    return wordList;
}

int main()
{
    // The following code implements a greet-extract strategy
    ifstream input;
    ofstream output;
    string inputFileName;

    greetUser(input, output, inputFileName);

    for (string s : extractWords(input, output, inputFileName))
        cout << s << endl;
//    extractWords(input, output, inputFileName);

    return 0;
}
