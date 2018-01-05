
/*
	UVa 11039 - Building designing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11039_Building_designing.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int nr_floors_max = 500000;
int floors[nr_floors_max];

bool compare_floor(int i, int j)
{
	return abs(i) < abs(j);
}

int main()
{
	int p;
	cin >> p;
	while (p--) {
		int nr_floors;
		cin >> nr_floors;
		for (int i = 0; i < nr_floors; i++)
			cin >> floors[i];
		int nr = 0;
		if (nr_floors) {
			sort(floors, floors + nr_floors, compare_floor);
			nr++;
			for (int i = 0; i < nr_floors - 1; i++)
				if (floors[i] > 0 && floors[i + 1] < 0 || floors[i] < 0 && floors[i + 1] > 0)
					nr++;
		}
		cout << nr << endl;
	}
	return 0;
}

