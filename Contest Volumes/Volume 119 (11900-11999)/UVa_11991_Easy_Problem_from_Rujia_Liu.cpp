
/*
	UVa 11991 - Easy Problem from Rujia Liu?

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11991_Easy_Problem_from_Rujia_Liu.cpp

	Rujia Liu's Present 3: A Data Structure Contest Celebrating the 100th Anniversary of Tsinghua University
	Special Thanks: Yiming Li
	Note: Please make sure to test your program with the gift I/O files before submitting!
*/

#include <iostream>
#include <map>
#include <cstring>
using namespace std;

const int n_max = 1000000;
int occurrences[n_max + 1]; // occurrences[i] is the number of occurrences of i

int main()
{
	int n, m;
	while (cin >> n >> m) {
		memset(occurrences, 0, sizeof(occurrences));
		map<pair<int, int>, int> locations;
		for (int l = 1; l <= n; l++) {
			int v;
			cin >> v;
			occurrences[v]++;
			locations[make_pair(occurrences[v], v)] = l;
		}
		while (m--) {
			int k, v;
			cin >> k >> v;
			map<pair<int, int>, int>::const_iterator i = locations.find(make_pair(k, v));
			cout << ((i != locations.end()) ? i->second : 0) << endl;
		}
	}
	return 0;
}

