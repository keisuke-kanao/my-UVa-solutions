
/*
	UVa 105 - The Skyline Problem

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_105_The_Skyline_Problem.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int max_coordinate = 10000;
int x_coordinates[max_coordinate + 1];

int main()
{
	int l, h, r;
	int max_x_coordinate = 0;
	while (cin >> l >> h >> r) {
		max_x_coordinate = max(max_x_coordinate, r);
		for (int i = l; i < r; i++)
			x_coordinates[i] = max(x_coordinates[i], h);
	}
	h = 0;
	bool printed = false;
	for (int i = 0; i <= max_x_coordinate; i++)
		if (x_coordinates[i] != h) {
			h = x_coordinates[i];
			if (printed)
				cout << ' ';
			else
				printed = true;
			cout << i << ' ' << h;
		}
	cout << endl;
	return 0;
}

