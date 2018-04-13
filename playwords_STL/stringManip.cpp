#include <iostream>
#include <algorithm>
#include "stringManip.h"

using namespace std;
//Takes a string and puts all its characters in uppercase
void capitalize(string &word)
{
    transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );
}

// Scrambles the word taking into account the vector of split words produced by split
string scramble(string word)
{
    string newWord;

    while (!word.empty()) {
        unsigned long index = rand() % word.length();

        newWord.push_back(word[index]);
        word.erase(word.begin() + index);
    }

    return newWord;
}
