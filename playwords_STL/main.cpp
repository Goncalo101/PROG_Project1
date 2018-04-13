#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include "Game.h"

using namespace std;

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
