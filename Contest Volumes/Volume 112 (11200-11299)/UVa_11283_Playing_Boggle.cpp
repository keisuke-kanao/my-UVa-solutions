
/*
	UVa 11283 - Playing Boggle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11283_Playing_Boggle.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rows = 4, nr_columns = 4;
const int nr_letters_max = 16;
const int scores[] = {0, 0, 0, 1, 1, 2, 3, 5, 11, 11, 11, 11, 11, 11, 11, 11, 11};

char grid[nr_rows][nr_columns + 1];
bool visited[nr_rows][nr_columns];

bool boggle(int r, int c, int l, int wl, const char w[], int& score)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

	visited[r][c] = true;
	if (l == wl) {
		score += scores[wl];
		return true;
	}
	else if (l < wl) {
		for (int i = 0; i < nr_dirs; i++) {
			int nr = r + dirs[i][0], nc = c + dirs[i][1];
			if (nr >= 0 && nr < nr_rows && nc >= 0 && nc < nr_columns &&
				grid[nr][nc] == w[l] && !visited[nr][nc])
				if (boggle(nr, nc, l + 1, wl, w, score))
					return true;
		}
	}
	visited[r][c] = false;
	return false;
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int g = 1; g <= N; g++) {
		for (int r = 0; r < nr_rows; r++)
			scanf("%s", grid[r]);
		int M;
		scanf("%d", &M);
		char w[nr_letters_max + 1];
		int score = 0;
		while (M--) {
			scanf("%s", w);
			bool found = false;
			for (int r = 0; r < nr_rows; r++) {
				for (int c = 0; c < nr_columns; c++)
					if (grid[r][c] == w[0]) {
						memset(visited, 0, sizeof(visited));
						if (found = boggle(r, c, 1, strlen(w), w, score))
							break;
					}
				if (found)
					break;
			}
		}
		printf("Score for Boggle game #%d: %d\n", g, score);
	}
	return 0;
}

