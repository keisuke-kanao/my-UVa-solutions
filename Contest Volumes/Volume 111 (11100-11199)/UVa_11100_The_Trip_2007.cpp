
/*
	UVa 11100 - The Trip, 2007

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11100_The_Trip_2007.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int nr_bags_max = 10000;
int bags[nr_bags_max];

int main()
{
	bool first = true;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (first)
			first = false;
		else
			cout << endl;
		for (int i = 0; i < n; i++)
			cin >> bags[i];
		sort(bags, bags + n);
		int nr_duplicated = 1; // number of duplicated occurences of a same number
		int nr_pieces = 1; // max. number of duplicated occurences of a same number
		for (int i = 1, b = bags[0]; i < n; i++) {
			if (bags[i] == b)
				nr_duplicated++;
			else {
				nr_pieces = max(nr_duplicated, nr_pieces);
				b = bags[i]; nr_duplicated = 1;
			}
		}
		nr_pieces = max(nr_duplicated, nr_pieces);
		vector< vector<int> > packed_bags(nr_pieces);
		for (int i = 0; i < n; i++)
			packed_bags[i % nr_pieces].push_back(bags[i]);
		cout << nr_pieces << endl;
		for (int i = 0; i < nr_pieces; i++) {
			for (int j = 0, je = packed_bags[i].size(); j < je; j++) {
				if (j)
					cout << ' ';
				cout << packed_bags[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}

