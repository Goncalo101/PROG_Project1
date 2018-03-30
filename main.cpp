#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
//returns a vector with each element being a line from the input file
vector<string> namesToVector(ifstream &infile)
{
	string personName;
	vector<string> names;
	while (getline(infile, personName))
	{
		names.push_back(personName);
	}
	return names;
}

////////////////////////////////////////////////////////////////////////////
//swaps two string strings in a vector with indexes X and Y
//used to sort vector with the names
void swapElements(vector<string> &names, int x, int y)
{
	string temp = names[x];
	names[x] = names[y];
	names[y] = temp;
}

/////////////////////////////////////////////////////////////////////////////
//sorts the vector with the names in alphabetic order - quick sort method used
void sortVector(vector<string> &names, int left, int right)
{
	int i = left; //left index
	int j = right; //right index
	string pivot = names[(left + right) / 2]; //middle element of vector chosen as pivot

	while (i <= j)
	{
		while (names[i] < pivot)
			i++;
		while (names[j] > pivot)
			j--;
		if (i <= j)
		{
			swapElements(names, i, j);
			i++;
			j--;
		}
	}
	if (left < j)
		sortVector(names, left, j);
	if (i < right)
		sortVector(names, i, right);
	return;
}

/////////////////////////////////////////////////////////////////////////////
//writes the names from the sorted vector to the output file
void writeNames(vector<string> names, ofstream& outfile)
{
	for (size_t i = 0; i < names.size(); i++)
	{
		outfile << names[i] << endl;
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////
int main()
{
	vector<string> names;
	string fileName;
	cout << "Enter the file name that contains people\'s names: ";
	cin >> fileName;

	ifstream infile;
	ofstream outfile;
	infile.open(fileName);
	if (infile.fail())
	{
		cerr << "Error opening " << fileName << endl;
		exit(1);
	}
	size_t pos = fileName.find('.');
	string outFileName = fileName.substr(0, pos) + "_sorted.txt";

	outfile.open(outFileName);
	if (outfile.fail())
	{
		cerr << "Output file opening failed " << endl;
		exit(2);
	}

	names = namesToVector(infile);
	sortVector(names, 0, names.size() - 1);
	writeNames(names, outfile);

	infile.close();
	outfile.close();
	return 0;
}
