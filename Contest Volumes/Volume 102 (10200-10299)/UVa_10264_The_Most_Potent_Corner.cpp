
/*
	UVa 10264 - The Most Potent Corner

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10264_The_Most_Potent_Corner.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int N_max = 14, nr_corners_max = 1 << N_max;
int corners[nr_corners_max], potencies[nr_corners_max];

int main()
{
	int N;
	while (cin >> N) {
		int nr_corners = 1 << N;
		for (int i = 0; i < nr_corners; i++)
			cin >> corners[i];
		for (int i = 0; i < nr_corners; i++) {
			potencies[i] = 0;
			for (int j = 0, b = 1; j < N; j++, b <<= 1) {
				potencies[i] += corners[i ^ b];
			}
		}
		int max_sum = 0;
		for (int i = 0; i < nr_corners; i++)
			for (int j = 0, b = 1; j < N; j++, b <<= 1)
				max_sum = max(max_sum, potencies[i] + potencies[i ^ b]);
		cout << max_sum << endl;
	}
	return 0;
}

