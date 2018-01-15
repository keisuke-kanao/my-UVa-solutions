
/*
	1.6.1 The 3n + 1 Problem
	PC/UVa IDs: 110101/100, Popularity: A, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_100_The_3n_plus_1_Problem.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int cycle_length(long long n) // calculate the cycle length of n
{
	int cl;
	for (cl = 1; n > 1; cl++) {
		if (n & 1) // n is odd
			n = n * 3 + 1;
		else
			n /= 2;
	}
	return cl;
}

int max_cycle_length(int i, int j)
{
	if (i > j)
		swap(i, j);
	int max_cl = 0;
	for ( ; i <= j; i++)
		max_cl = max(max_cl, cycle_length(i));
	return max_cl;
}

int main(int /* argc */, char** /* argv */)
{
	unsigned int i, j;
	while (cin >> i >> j)
		cout << i << ' ' << j << ' ' << max_cycle_length(i, j) << endl;
	return 0;
}

