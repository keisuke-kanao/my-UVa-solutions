
/*
	UVa 12673 - Football

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12673_Football.cpp

	This solution has not been submitted yet, but if it is, it is likely that it is verdicted as TLE.
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 100000, G_max = 1000000;

int max_points[2][G_max + 1]; // max_points[n % 2][g] is the max. points for the n-th game with additional g goals

int main()
{
	int N, G;
	while (scanf("%d %d", &N, &G) != EOF) {
		int (*pp)[G_max + 1], (*cp)[G_max + 1];
	    cp = &max_points[0];
		(*cp)[0] = 0;
		for (int g = 1; g <= G; g++)
			(*cp)[g] = -1;
		for (int n = 1; n <= N; n++) {
			int S, R;
			scanf("%d %d", &S, &R);
			pp = &max_points[(n - 1) % 2], cp = &max_points[n % 2];
			if (S > R) {
				for (int g = 0; g <= G; g++)
					(*cp)[g] = ((*pp)[g] != -1) ? (*pp)[g] + 3 : -1;
			}
			else {
				int d = R - S;
				for (int g = 0; g < d; g++)
					(*cp)[g] = (*pp)[g];
				for (int g = d; g <= G; g++) {
					int mp = (*pp)[g];
					if (g > d) {
						if ((*pp)[g - d - 1] != -1)
							mp = max(mp, (*pp)[g - d - 1] + 3);
						else
							mp = max(mp, 3);
					}
					if ((*pp)[g - d] != -1)
						mp = max(mp, (*pp)[g - d] + 1);
					else
						mp = max(mp, 1);
					(*cp)[g] = mp;
				}
			}
#ifdef DEBUG
			for (int g = 0; g <= G; g++)
				if ((*cp)[g] != -1)
					printf("[%d][%d]:%d ", n, g, (*cp)[g]);
			putchar('\n');
#endif
		}
		int max_point = -1;
		cp = &max_points[N % 2];
		for (int g = 0; g <= G; g++)
			if ((*cp)[g] != -1)
				max_point = max(max_point, (*cp)[g]);
		printf("%d\n", max_point);
	}
	return 0;
}

