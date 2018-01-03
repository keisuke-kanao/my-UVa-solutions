
/*
	UVa 900 - Brick Wall Patterns

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_900_Brick_Wall_Patterns.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int length_max = 50;
	long long nr_patterns[length_max + 1]; // nr_patterns[i] is the number of patterns for the length of i
	nr_patterns[1] = 1; nr_patterns[2] = 2;
	for (int i = 3; i <= length_max; i++)
		nr_patterns[i] = nr_patterns[i - 1] + nr_patterns[i - 2];
	while (true) {
		int l;
		cin >> l;
		if (!l)
			break;
		cout <<nr_patterns[l] << endl;
	}
	return 0;
}

