
/*
	UVa 10944 - Nuts for nuts..

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10944_Nuts_for_nuts.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int x_max = 20, y_max = 20, nr_nuts_max = 15;
char area[x_max][y_max + 1];
struct place {
	int r_, c_;
} places[nr_nuts_max + 1];

int distances[nr_nuts_max + 1][nr_nuts_max + 1];
	// distances[i][j] is the distance between the nuts of i and j
int bitmasks[1 << (nr_nuts_max + 1)][nr_nuts_max + 1];

int tsp(int nr_nuts, int places, int p) // travelling salesman problem
{
	if (places == (1 << p))
		return distances[p][0]; // distance from L to the nut of p
	int& d = bitmasks[places][p];
	if (d >= 0)
		return d;
	d = numeric_limits<int>::max();
	for (int i = 0; i < nr_nuts; i++)
		if (i != p && (places & (1 << i)))
			d = min(d, distances[p][i] + tsp(nr_nuts, places & ~(1 << p), i));
	return d;
}

int main()
{
	int x, y;
	while (scanf("%d %d", &x, &y) != EOF) {
		for (int i = 0; i < x; i++)
			scanf("%s", area[i]);
		int nr_nuts = 1;
		for (int r = 0; r < x; r++)
			for(int c = 0; c < y; c++) {
				if (area[r][c] == 'L') {
					places[0].r_ = r; places[0].c_ = c;
				}
				else if (area[r][c] == '#') {
					places[nr_nuts].r_ = r; places[nr_nuts].c_ = c;
					nr_nuts++;
				}
			}
		for (int i = 0; i < nr_nuts; i++)
			for (int j = 0; j < nr_nuts; j++)
				distances[i][j] = max(abs(places[i].r_ - places[j].r_), abs(places[i].c_ - places[j].c_));
		memset(bitmasks, -1, sizeof(bitmasks));
		printf("%d\n", tsp(nr_nuts, (1 << nr_nuts) - 1, 0));
	}
	return 0;
}

