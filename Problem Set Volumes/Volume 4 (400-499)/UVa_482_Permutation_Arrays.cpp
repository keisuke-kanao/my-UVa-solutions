
/*
	UVa 482 - Permutation Arrays

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_482_Permutation_Arrays.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int t;
	iss >> t;
	iss.clear();
	while (t--) {
		getline(cin, line); // skip a blank line
		getline(cin, line); // read an index array
		iss.str(line);
		int pi;
		vector<int> indices;
		while (iss >> pi)
			indices.push_back(pi - 1);
		iss.clear();
		getline(cin, line); // read a list of numbers
		iss.str(line);
		size_t n = indices.size();
		vector<string> numbers(n);
		for (size_t i = 0; i < n; i++)
			iss >> numbers[indices[i]];
		iss.clear();
		for (size_t i = 0; i < n; i++)
			cout << numbers[i] << endl;
		if (t)
			cout << endl;
	}
	return 0;
}

