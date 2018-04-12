#include "extractor.h"

using namespace std;

int main()
{
    set<string> wordSet;
    string inputFileName;
    string outputFileName;
    ifstream infile;
    ofstream outfile;

    greetUser(infile, outfile, inputFileName, outputFileName);

    wordSet = extractWords(infile, outfile, inputFileName);

    // Ending sequence
    cout << endl << "Number of simple words = " << wordSet.size() << endl;

    cout << "Saving words to " << outputFileName << " ..." << endl;
    writeEntries(wordSet, outfile);

    cout << "Done" << endl;
    return 0;
}
