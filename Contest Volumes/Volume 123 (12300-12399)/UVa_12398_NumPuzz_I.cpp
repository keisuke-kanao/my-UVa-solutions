
/*
	UVa 12398 - NumPuzz I

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12398_NumPuzz_I.cpp
*/

#include <cstdio>
#include <cstring>


int main()
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	const int nr_squares = 3;
	int puzzle[nr_squares][nr_squares];
	const int nr_chars_max = 200;
	char s[nr_chars_max + 1];
	for (int case_nr = 1; gets(s); case_nr++) {
		memset(puzzle, 0, sizeof(puzzle));
		for (int i = strlen(s) - 1; i >= 0; i--) {
			int j = s[i] - 'a';
			int r = j / nr_squares, c = j % nr_squares;
			puzzle[r][c] = (puzzle[r][c] + 1) % 10;
			for (int k = 0; k < nr_dirs; k++) {
				int nr = r + dirs[k][0], nc = c + dirs[k][1];
				if (nr >= 0 && nr < nr_squares && nc >= 0 && nc < nr_squares)
					puzzle[nr][nc] = (puzzle[nr][nc] + 1) % 10;
			}
		}
		printf("Case #%d:\n", case_nr);
		for (int i = 0; i < nr_squares; i++)
			for (int j = 0; j < nr_squares; j++)
				printf("%d%c", puzzle[i][j], ((j < nr_squares - 1) ? ' ' : '\n'));
	}
	return 0;
}

