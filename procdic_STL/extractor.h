#ifndef PROG_PROJECT1_EXTRACTOR_H
#define PROG_PROJECT1_EXTRACTOR_H


#include <iostream>
#include <set>
#include <fstream>
#include <string>

using namespace std;

void greetUser(ifstream &input, ofstream &output, string &inputFileName, string &outputFileName);
set<string> extractWords(ifstream &input, ofstream &output, const string &fileName);
void writeEntries(const set<string> &wordSet, ofstream &outfile);

#endif //PROG_PROJECT1_EXTRACTOR_H