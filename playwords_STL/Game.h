#ifndef PROG_PROJECT1_GAME_H
#define PROG_PROJECT1_GAME_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

void greetUser(ifstream &input, string &inputFileName, vector<string> &wordList);
void checkWordInVector(vector<string> &wordList);
void showMenu(vector<string> wordList);
void showVector(vector<string> wordsVector);
bool validInput(string letters);
string readSet();
bool wordMatch(string currentWord, string letters);
vector<string> wordsConstructor(vector<string> wordList, string letters);
void buildWords(vector<string> wordList);
vector<int> getOcurrences(vector<string> wordList);
string getLongestWord(vector<string> wordList);
void createSet(vector<string> wordList);
void guessWord(vector<string> wordList);
bool wildcardMatch(const char *str, const char *strWild);
void searchWithWildcard(vector<string> vector);



#endif //PROG_PROJECT1_GAME_H
