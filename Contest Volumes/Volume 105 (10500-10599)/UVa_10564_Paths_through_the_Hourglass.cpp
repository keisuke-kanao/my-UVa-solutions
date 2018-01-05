
/*
	UVa 10564 - Paths through the Hourglass

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10564_Paths_through_the_Hourglass.cpp
*/

#include <cstdio>
#include <cstring>

/*
Let cells[r][c] is the value of cell at r-th row, c-th column, and, 
nr_paths[r][c][s] is the number of paths that leads to cells[r][c] with the path value of s, then:
	nr_paths[r][c][s] = nr_paths[r - 1][left to c][s - cells[r][c]] + nr_paths[r - 1][right to c][s - cells[r][c]
*/

const int N_max = 20, S_max = 500;

int cells[N_max * 2 - 1][N_max];
long long nr_paths[N_max * 2 - 1][N_max][S_max];

#ifdef DEBUG
void print_s(int N, int S, int r)
{
	printf("%d\n", r);
	for (int c = 0; c < N; c++)
		for (int s = 0; s <= S; s++)
			printf("%3lld%c", nr_paths[r][c][s], ((s < S) ? ' ' : '\n'));
	putchar('\n');
}
#endif

/*
6 41			r		cs
6 7 2 3 6 8		0		0
  1 8 0 7 1		1		1
    2 6 5 7		2		2
      3 1 0		3		3
        7 6		4		4
          8		5		5
        8 8		6		4
      6 5 3		7		3
    9 5 9 5		8		2
  6 4 4 1 3		9		1
2 6 9 4 3 8		10		0
*/

void follow_paths(int N, int S)
{
	for (int c = 0; c < N; c++)
		for (int s = 0; s <= S; s++)
			nr_paths[2 * (N - 1)][c][s] = (s == cells[2 * (N - 1)][c]) ? 1 : 0;
#ifdef DEBUG
	print_s(N, S, 2 * (N - 1));
#endif
	for (int r = 2 * (N - 1) - 1, ci = 1; r >= 0; r--, ((r >= N - 1) ? ci++ : ci--)) {
		for (int c = ci; c < N; c++) {
			int cs = cells[r][c];
			for (int s = 0; s <= S; s++) {
				if (s < cs)
					nr_paths[r][c][s] = 0;
				else {
					long long np_left, np_right;
					if (r >= N - 1) {
						np_left = nr_paths[r + 1][c - 1][s - cs]; // from lower left
						np_right = nr_paths[r + 1][c][s - cs]; // from lower right
					}
					else {
						np_left = (c > ci) ? nr_paths[r + 1][c][s - cs] : 0; // from lower left
						np_right = (c < N - 1) ? nr_paths[r + 1][c + 1][s - cs] : 0; // from lower right
					}
					nr_paths[r][c][s] = np_left + np_right;
				}
			}
		}
#ifdef DEBUG
		print_s(N, S, r);
#endif
	}
}

void trace_path(int N, int r, int c, int s, char* path)
{
	int cs;
	if (r < N - 1) {
		cs = cells[r][c];
		if (c > r && nr_paths[r + 1][c][s - cs]) { // to lower left
			path[r] = 'L';
			trace_path(N, r + 1, c, s - cs, path);
		}
		else { // to lower right
			path[r] = 'R';
			trace_path(N, r + 1, c + 1, s - cs, path);
		}
	}
	else if (r < 2 * (N - 1)) {
		cs = cells[r][c];
		if (nr_paths[r + 1][c - 1][s - cs]) { // to lower left
			path[r] = 'L';
			trace_path(N, r + 1, c - 1, s - cs, path);
		}
		else { // to lower right
			path[r] = 'R';
			trace_path(N, r + 1, c, s - cs, path);
		}
	}
}

int main()
{
	while (true) {
		int N, S;
		scanf("%d %d", &N, &S);
		if (!N && !S)
			break;
		for (int r = 0, ci = 0; r < 2 * N - 1; r++, ((r < N) ? ci++ : ci--))
			for (int c = ci; c < N; c++)
				scanf("%d", &cells[r][c]);
		follow_paths(N, S);
		int first_c = -1;
		long long nr = 0;
		for (int c = 0; c < N; c++)
			if (nr_paths[0][c][S]) {
				if (first_c == -1)
					first_c = c;
				nr += nr_paths[0][c][S];
			}
		printf("%lld\n", nr);
		if (first_c != -1) {
			char path[N_max * 2 - 1];
			trace_path(N, 0, first_c, S, path);
			path[2 * (N - 1)] = '\0';
			printf("%d %s\n", first_c, path);
		}
		else
			putchar('\n');
	}
	return 0;
}


