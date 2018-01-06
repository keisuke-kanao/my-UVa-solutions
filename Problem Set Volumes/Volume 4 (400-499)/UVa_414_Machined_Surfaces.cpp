
/*
	UVa 414 - Machined Surfaces

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_414_Machined_Surfaces.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int nr_column_max = 25;

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		string line;
		getline(cin, line);
		istringstream iss(line);
		int n; // number of rows
		iss >> n;
		if (!n)
			break;
		int nr_total_spaces = 0; // total number of spaces
		int nr_spaces_min = nr_column_max;
		for (int i = 0; i < n; i++) {
			int nr_spaces = 0; // number of spaces for this row
			getline(cin, line);
			for (int j = 0; j < nr_column_max; j++)
				if (line[j] == ' ')
					nr_spaces++;
			nr_total_spaces += nr_spaces;
			nr_spaces_min = min(nr_spaces_min, nr_spaces);
		}
		cout << nr_total_spaces - nr_spaces_min * n << endl;
	}
	return 0;
}

