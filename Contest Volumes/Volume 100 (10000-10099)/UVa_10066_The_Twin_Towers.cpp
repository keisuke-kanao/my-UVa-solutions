
/*
	UVa 10066 - The Twin Towers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10066_The_Twin_Towers.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_tiles_max = 100;
int tile_radii1[nr_tiles_max], tile_radii2[nr_tiles_max];
int lcs_c[2][nr_tiles_max + 1];

int lcs(int n1, int n2)
{
	memset(lcs_c[0], 0, sizeof(int) * (n2 + 1));
	memset(lcs_c[1], 0, sizeof(int) * (n2 + 1));
	for (int i = 1; i <= n1; i++) {
		int ci = i % 2, pi = (i - 1) % 2;
		for (int j = 1; j <= n2; j++) {
			if (tile_radii1[i - 1] == tile_radii2[j - 1])
				lcs_c[ci][j] = lcs_c[pi][j - 1] + 1;
			else
				lcs_c[ci][j] = max(lcs_c[ci][j - 1], lcs_c[pi][j]);
		}
	}
	return lcs_c[n1 % 2][n2];
}

int main()
{
	for (int nr = 1; ; nr++) {
		int n1, n2;
		cin >> n1 >> n2;
		if (!n1 && !n2)
			break;
		for (int i = 0; i < n1; i++)
			cin >> tile_radii1[i];
		for (int i = 0; i < n2; i++)
			cin >> tile_radii2[i];
		int nr_tiles = lcs(n1, n2);
		cout << "Twin Towers #" << nr << endl;
		cout << "Number of Tiles : " << nr_tiles << endl << endl;
	}
	return 0;
}

