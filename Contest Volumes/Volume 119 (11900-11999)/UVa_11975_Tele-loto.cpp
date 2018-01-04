
/*
	UVa 11975 - Tele-loto

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11975_Tele-loto.cpp
*/

#include <cstdio>

const int nr_balls_max = 75, nr_values = 4, nr_rows = 5, nr_columns = 5;
int balls[nr_balls_max], values[nr_values], ticket[nr_rows][nr_columns], findings[nr_rows][nr_columns];

bool corners(int n)
{
	return n >= 4 && findings[0][0] < 35 && findings[0][nr_columns - 1] < 35 &&
		findings[nr_rows - 1][0] < 35 && findings[nr_rows - 1][nr_columns - 1] < 35;
}

bool mid_line(int n)
{
	if (n < nr_columns)
		return false;
	for (int i = 0; i < nr_columns; i++)
		if (findings[2][i] >= 40)
			return false;
	return true;
}

bool diagonals(int n)
{
	return n >= 9 && findings[0][0] < 45 && findings[0][nr_columns - 1] < 45 &&
		findings[1][1] < 45 && findings[1][3] < 45 && findings[2][2] < 45 &&
		findings[3][1] < 45 && findings[3][3] < 45 &&
		findings[nr_rows - 1][0] < 45 && findings[nr_rows - 1][nr_columns - 1] < 45;
}

bool table(int n)
{
	if (n < nr_rows * nr_columns)
		return false;
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++)
			if (findings[i][j] == nr_balls_max)
				return false;
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, L;
		scanf("%d %d", &N, &L);
		for (int i = 0; i < N; i++)
			scanf("%d", &balls[i]);
		for (int i = 0; i < nr_values; i++)
			scanf("%d", &values[i]);
		printf("Case %d:\n", t);
		while (L--) {
			for (int i = 0; i < nr_rows; i++)
				for (int j = 0; j < nr_columns; j++) {
					scanf("%d", &ticket[i][j]);
					findings[i][j] = nr_balls_max;
				}
			for (int i = 0; i < N; i++) {
				int c = (balls[i] - 1) / 15;
				for (int r = 0; r < nr_rows; r++)
					if (ticket[r][c] == balls[i]) {
						findings[r][c] = i; break;
					}
			}
			int value = 0;
			if (corners(N))
				value += values[0];
			if (mid_line(N))
				value += values[1];
			if (diagonals(N))
				value += values[2];
			if (table(N))
				value += values[3];
			printf("%d\n", value);
		}
		if (t < T)
			putchar('\n');
	}
	return 0;
}

