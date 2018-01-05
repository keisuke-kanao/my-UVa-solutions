
/*
	UVa 11140 - Little Ali's Little Brother!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11140_Little_Alis_Little_Brother.cpp

	This problem is similar to UVa 12291 - Polyomino Composer.
*/

#include <cstdio>

const int N_max = 50, M_max = 50;
char piece[N_max][M_max + 1], board[N_max][M_max + 1];

bool can_be_placed(int N, int M, int n, int m, int psi, int psj)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == '*') {
				bool possible = true;
				for (int pi = 0, bi = i - psi; pi < n && possible; pi++, bi++)
					for (int pj = 0, bj = j - psj; pj < m && possible; pj++, bj++)
						if (piece[pi][pj] == '*') {
							if (bi < 0 || bi >= N || bj < 0 || bj >= M || board[bi][bj] != '*')
								possible = false;
						}
				if (possible)
					return true;
			}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, S;
		scanf("%d %d %d", &N, &M, &S);
		for (int i = 0; i < N; i++)
			scanf("%s", board[i]);
		while (S--) {
			int n, m;
			scanf("%d %d", &n, &m);
			for (int i = 0; i < n; i++)
				scanf("%s", piece[i]);
			int psi = -1, psj;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++)
					if (piece[i][j] == '*') {
						psi = i, psj = j;
						break;
					}
				if (psi != -1)
					break;
			}
			puts((psi == -1 || can_be_placed(N, M, n, m, psi, psj)) ? "Yes" : "No");
		}
		putchar('\n');
	}
	return 0;
}

/*
Sample Input

2
5 5 2
....*
...**
..***
...**
....*
3 2
**
**
**
1 6
******

3 3 1
***
*.*
***
3 2
**
.*
**


Sample Output

Yes
No

Yes

*/

