
/*
	UVa 11835 - Formula 1

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11835_Formula_1.cpp
*/

#include <cstdio>

const int G_max = 100, P_max = 100;

int grand_prix[G_max][P_max + 1];
	// grand_prix[i][j] is the order of arrival of j-th pilot (j >= 1) at the i-th Grand Pifx (i >= 0)
int scores[P_max + 1];
	// scores[i] is the number of points assgined to j-th place (j >= 1)
int points[P_max + 1];
	// points[i] is the points of i-th pilot (i >= 1)
int main()
{
	while (true) {
		int G, P;
		scanf("%d %d", &G, &P);
		if (!G && !P)
			break;
		for (int i = 0; i < G; i++)
			for (int j = 1; j <= P; j++)
				scanf("%d", &grand_prix[i][j]);
		int S;
		scanf("%d", &S);
		while (S--) {
			int K;
			scanf("%d", &K);
			for (int i = 1; i <= K; i++)
				scanf("%d", &scores[i]);
			for (int i = K + 1; i <= P; i++)
				scores[i] = 0;

			for (int i = 1; i <= P; i++)
				points[i] = 0;
			for (int i = 0; i < G; i++)
				for (int j = 1; j <= P; j++)
					points[j] += scores[grand_prix[i][j]];
			int point_max = 0;
			for (int i = 1; i <= P; i++)
				if (points[i] > point_max)
					point_max = points[i];
			bool printed = false;
			for (int i = 1; i <= P; i++)
				if (points[i] == point_max) {
					if (printed)
						putchar(' ');
					else
						printed = true;
					printf("%d", i);
				}
			putchar('\n');
		}
	}
	return 0;
}

