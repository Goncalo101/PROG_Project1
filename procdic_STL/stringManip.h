#ifndef PROG_PROJECT1_STRINGMANIP_H
#define PROG_PROJECT1_STRINGMANIP_H


#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

vector<string> split(string line);
size_t parseLine(string line, set<string> &wordSet);
size_t findNextSemiColon(size_t i, string line);

#endif //PROG_PROJECT1_STRINGMANIP_H
