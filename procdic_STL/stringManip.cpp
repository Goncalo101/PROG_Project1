#include "stringManip.h"

using namespace std;

// This function returns the index of the next semicolon if it exists.
// Returns the length of the line if no semicolon is found.
size_t findNextSemiColon(size_t i, string line)
{
    for (size_t j = i; j < line.length(); j++) {
        if (line[j] == ';') return j - 1;
    }

    return line.length();
}

// Works similarly to Python's split() function.
// Each element of the line will be made an element of a vector (ignores elements that have hyphens or whitespaces).
// Example:
// Considering string line = "ABA; ABB; ABC; AB-D; AB E", split(line) returns a vector<string>
// like this: {"ABA", "ABB", "ABC"}
vector<string> split(string line)
{
    vector<string> wordList;
    string word;

    for (size_t i = 0; i < line.length(); i++) {
        if ((line[i] == ' ' && line[i + 1] != ';') || line[i] == '-' || line[i] == '\'' || line[i] == '*' || line[i] == '.') {
            word.clear();

            i = findNextSemiColon(i, line);

        } else if ((line[i] == ';') || (line[i] == ' ' && line[i + 1] == ';')) {
            if (!word.empty()) {
                wordList.push_back(word);
            }

            word.clear();
            ++i;

            continue;

        } else if (isalpha((unsigned char) line[i])) {
            word.push_back(line[i]);

        }
    }

    if (!word.empty() && (word != "CHO" && word != "PJC")) {
        wordList.push_back(word);
    }

    return wordList;
}

// Parses line in search of actual entries. Returns the number of words added to wordList.
size_t parseLine(string line, set<string> &wordSet)
{
    // Ignore all lines containing lower case characters
    for (char c : line) {
        if (islower((unsigned char) c))
            return 0;
    }

    // If the line doesn't qualify for being ignored, a split will be attempted.
    vector<string> properLine = split(line);

    // Add the newly split string (do not forget it's actually a vector) to the end of the existing wordSet.
    // No vector shall be concatenated to wordSet if split(line) returns an empty vector. Potentially unnecessary.
    if (!properLine.empty()) {
        for (const string &s : properLine)
            wordSet.insert(s);
    }

    return properLine.size();
}