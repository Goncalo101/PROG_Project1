#include <fstream>
#include "extractor.h"
#include "stringManip.h"

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

set<string> extractWords(ifstream &input, ofstream &output, const string &fileName)
{
    set<string> wordSet;
    string line;

    char currentLetter = '\0';
    int i = 1;

    cout << "Extracting words from " << fileName << endl;

    while (getline(input, line)) {
        size_t numberOfElementsAdded = parseLine(line, wordSet);

        if (i % 100 == 0) {
            cout << ".";
        }

        if (numberOfElementsAdded) {
            char temp = line[0];


            // The input file contains a phrase called CONSOLATION RACE, which is split between two lines.
            // This causes the program to consider CONSOLATION and RACE two different words and will thus, print
            // R and then carry on with all the Cs. Is it really necessary to make an exception for this phrase?
            if (currentLetter != temp && (isalpha(temp) || line.substr(0, line.find_first_of('\r')).length() == 1)) {
                if (!(temp == 'R' && i < 40000)) {
                    currentLetter = temp;

                    cout << endl << currentLetter << endl;
                }
            }

            i += numberOfElementsAdded;
        }
    }

    input.close();
    return wordSet;
}

/////////////////////////////////////////////////////////////////////////////
//writes the words from the sorted vector to the output file
void writeEntries(const set<string> &wordSet, ofstream &outfile)
{
    for (const auto &it : wordSet) {
       outfile << (string) it << endl;
    }
}