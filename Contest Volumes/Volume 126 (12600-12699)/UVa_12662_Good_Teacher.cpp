
/*
	UVa 12662 - Good Teacher

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12662_Good_Teacher.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100, nr_chars_max = 3;

int positions[n_max];
char names[n_max][nr_chars_max + 1];

int main()
{
	int n;
	scanf("%d", &n);
	int nr_positions = 0;
	for (int p = 1; p <= n; p++) {
		scanf("%s", names[nr_positions]);
		if (names[nr_positions][0] != '?')
			positions[nr_positions++] = p;
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int p;
		scanf("%d", &p);
		int pi = lower_bound(positions, positions + nr_positions, p) - positions, l, r;
		if (pi == nr_positions) {
			for (r = p - positions[pi - 1]; r; r--)
				printf("right of ");
			printf("%s\n", names[pi - 1]);
		}
		else if (positions[pi] == p)
			printf("%s\n", names[pi]);
		else if (!pi) {
			for (l = positions[pi] - p; l; l--)
				printf("left of ");
			printf("%s\n", names[pi]);
		}
		else {
			r = p - positions[pi - 1], l = positions[pi] - p;
			if (r > l) {
				for ( ; l; l--)
					printf("left of ");
				printf("%s\n", names[pi]);
			}
			else if (r < l) {
				for ( ; r; r--)
					printf("right of ");
				printf("%s\n", names[pi - 1]);
			}
			else
				printf("middle of %s and %s\n", names[pi - 1], names[pi]);
		}
	}
	return 0;
}

