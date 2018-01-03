
/*
	UVa 613 - Numbers That Count

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_613_Numbers_That_Count.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstring>
using namespace std;

const int nr_digits = '9' - '0' + 1, iterations_max = 15;

int main()
{
	while (true) {
		string inventory;
		cin >> inventory;
		if (inventory == "-1")
			break;
		string ps = inventory;
		map<string, int> inventories;
		int iterations;
		for (iterations = 0; iterations < iterations_max; iterations++) {
			int freqs[nr_digits];
			memset(freqs, 0, sizeof(freqs));
			for (const char* p = ps.c_str(); *p; p++)
				freqs[*p - '0']++;
			ostringstream oss;
			for (int i = 0; i < nr_digits; i++)
				if (freqs[i])
					oss << freqs[i] << i;
			string s = oss.str();
#ifdef DEBUG
			cout << iterations << ": " << s << endl;
#endif
			if (s == ps) {
				if (iterations)
					cout << inventory << " is self-inventorying after " << iterations << " steps\n";
				else
					cout << inventory << " is self-inventorying\n";
				break;
			}
			pair<map<string, int>::iterator, bool> result = inventories.insert(make_pair(s, iterations));
			if (!result.second) {
				cout << inventory << " enters an inventory loop of length " << iterations - result.first->second << endl;
				break;
			}
			ps = s;
		}
		if (iterations == iterations_max)
			cout << inventory << " can not be classified after 15 iterations\n";
	}
	return 0;
}

