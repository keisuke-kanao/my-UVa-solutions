
/*
	UVa 154 - Recycling

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_154_Recycling.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int nr_colors = 5, nr_cities_max = 100;
char allocations[nr_cities_max][nr_colors];

int main()
{
	while (true) {
		string s;
		cin >> s;
		if (s[0] == '#')
			break;
		int nr_cities = 0;
		do {
			for (int i = 0; i < 4 * nr_colors; i += 4) {
				switch (s[i]) {
				case 'r':
					allocations[nr_cities][0] = s[i + 2]; break;
				case 'o':
					allocations[nr_cities][1] = s[i + 2]; break;
				case 'y':
					allocations[nr_cities][2] = s[i + 2]; break;
				case 'g':
					allocations[nr_cities][3] = s[i + 2]; break;
				case 'b':
					allocations[nr_cities][4] = s[i + 2]; break;
				}
			}
			nr_cities++;
			cin >> s;
		} while (s[0] != 'e');
		int min_nr_changes = nr_cities * nr_colors, ic = 0;
		for (int i = 0; i < nr_cities; i++) {
			int nr_changes = 0;
			for (int j = 0; j < nr_cities; j++)
				if (i != j) {
					for (int k = 0; k < nr_colors; k++)
						if (allocations[i][k] != allocations[j][k])
							nr_changes++;
				}
			if (nr_changes < min_nr_changes) {
				ic = i;
				min_nr_changes = nr_changes;
			}
		}
		cout << ic + 1 << endl;
	}
	return 0;
}

