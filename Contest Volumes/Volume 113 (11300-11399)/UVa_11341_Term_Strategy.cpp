
/*
	UVa 11341 - Term Strategy

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11341_Term_Strategy.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 10, M_max = 100, min_grade = 5;
int table[N_max + 1][M_max + 1];
int grades[N_max + 1][M_max + 1];
	// grades[i][j] is max. of the total grade up to i-th courses with j hours spent for preparation

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, m = 0;
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++)
			for (int j = 1, k = 1; j <= M; j++) {
				scanf("%d", &table[i][k]);
				if (table[i][k] >= min_grade)
					k++;
				else
					m++;
			}
		M -= m;
		if (M < N) {
			puts("Peter, you shouldn't have played billiard that much.");
			continue;
		}
		for (int j = 1; j <= M; j++)
			grades[1][j] = table[1][j];
		for (int i = 2; i <= N; i++)
			for (int j = i; j <= M; j++) {
				int g = 0;
				for (int k = 1; k < j; k++)
					g = max(g, grades[i - 1][k] + table[i][j - k]);
				grades[i][j] = g;
			}
		printf("Maximal possible average mark - %.2lf.\n", static_cast<double>(grades[N][M]) / N + 1.0e-9);
			// Without 1.0e-9, you will receive the verdict Wrong Answer.
	}
	return 0;
}

