
/*
	UVa 12673 - Football

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12673_Football.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 100000, G_max = 1000000;

int loses[N_max];

int main()
{
	int N, G;
	while (scanf("%d %d", &N, &G) != EOF) {
		int nr_draws = 0, nr_loses = 0, points = 0;
		while (N--) {
			int S, R;
			scanf("%d %d", &S, &R);
			if (S > R)
				points += 3;
			else if (S == R)
				nr_draws++;
			else
				loses[nr_loses++] = R - S;
		}
		sort(loses, loses + nr_loses);
		if (G > nr_draws) {
			points += nr_draws * 3;
			G -= nr_draws, nr_draws = 0;
		}
		else {
			points += G * 3;
			nr_draws -= G, G = 0;
			points += nr_draws;
		}
		for (int i = 0; i < nr_loses; i++) {
			if (G < loses[i])
				break;
			if (G > loses[i]) {
				points += 3;
				G -= loses[i] + 1;
			}
			else {
				points++;
				G -= loses[i];
			}
		}
		printf("%d\n", points);
	}
	return 0;
}

