
/*
	UVa 447 - Population Explosion

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_447_Population_Explosion.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_quarters = 20;

char quarters[2][nr_quarters][nr_quarters + 1];

void init_quarters(char q[nr_quarters][nr_quarters + 1])
{
	for (int i = 0; i < nr_quarters; i++)
		for (int j = 0; j < nr_quarters; j++)
			q[i][j] = ' ';
}

void print_quarters(char q[nr_quarters][nr_quarters + 1])
{
	puts("********************");
	for (int i = 0; i < nr_quarters; i++)
		puts(q[i]);
}

int main()
{
	const int nr_dirs = 8;
	int dirs[nr_dirs][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int nr_years;
		scanf("%d", &nr_years);
		while (getchar() != '\n')
			;
		char (*pq)[nr_quarters][nr_quarters + 1] = &quarters[0], (*cq)[nr_quarters][nr_quarters + 1] = &quarters[1];
		init_quarters(*pq);
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {
			ungetc(c, stdin);
			int i, j;
			scanf("%d %d", &i, &j);
			(*pq)[i - 1][j - 1] = 'O';
			while (getchar() != '\n')
				;
		}
		if (nr_years--)
			print_quarters(*pq);
		while (nr_years-- > 0) {
			init_quarters(*cq);
			for (int i = 0; i < nr_quarters; i++)
				for (int j = 0; j < nr_quarters; j++) {
					int n = 0;
					for (int k = 0; k < nr_dirs; k++) {
						int ci = i + dirs[k][0], cj = j + dirs[k][1];
						if (ci >= 0 && ci < nr_quarters && cj >= 0 && cj < nr_quarters && (*pq)[ci][cj] == 'O')
							n++;
					}
					if ((*pq)[i][j] == 'O') {
						if (n == 2 || n == 3)
							(*cq)[i][j] = 'O';
					}
					else {
						if (n == 3)
							(*cq)[i][j] = 'O';
					}
				}
			print_quarters(*cq);
			swap(pq, cq);
		}
		puts("********************");
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

