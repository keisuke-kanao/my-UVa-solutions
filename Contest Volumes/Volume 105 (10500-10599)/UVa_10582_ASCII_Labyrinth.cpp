
/*
	UVa 10582 - ASCII Labyrinth

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10582_ASCII_Labyrinth.cpp

	An accepted solution
*/

#include <cstdio>

enum {space, line, corner};
enum {up_down, left_right};

const int mn_max = 64, nr_chars_max = 64 * 4 + 1;
int n, m, ctr, board[mn_max][mn_max];
bool visited[mn_max][mn_max];

void dfs(int x, int y, int d)
{
	if (x == m - 1 && y == n - 1) {
        ctr++;
        return;
    }
    visited[x][y] = true;
    if (d == up_down) {
        if (x - 1 < 0 || visited[x - 1][y] || board[x - 1][y] == space)
			;
        else { // up
            if (board[x - 1][y] == line)
                dfs(x - 1, y, up_down);
            else
                dfs(x - 1, y, left_right);
        }
        if (x + 1 >= m || visited[x + 1][y] || board[x + 1][y] == space)
			;
        else { // down
            if (board[x + 1][y] == line)
                dfs(x + 1, y, up_down);
            else
                dfs(x + 1, y, left_right);
        }
    }
	else {
        if (y - 1 < 0 || visited[x][y - 1] || board[x][y - 1] == space)
			;
        else { // left
            if (board[x][y - 1] == line)
                dfs(x, y - 1, left_right);
            else
                dfs(x, y - 1, up_down);
        }
        if (y + 1 >= n || visited[x][y + 1] || board[x][y + 1] == space)
			;
        else { // right
            if (board[x][y + 1] == line)
                dfs(x, y + 1, left_right);
            else
                dfs(x, y + 1, up_down);
        }
    }
    visited[x][y] = false;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		scanf("%d %d", &m, &n);
		while (getchar() != '\n')
			;
		char s[nr_chars_max + 1];
		gets(s); // skip the top line of the board
		for (int i = 0; i < m; i++) {
			gets(s);
			gets(s);
			for (int j = 0; j < n; j++)
				board[i][j] = (s[j * 4 + 1] == '*') ?
					((s[j * 4 + 3] == '*') ? line : corner) : space;
			gets(s);
			gets(s);
		}
#ifdef DEBUG
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				printf("%3d%c", board[i][j], ((j < n - 1) ? ' ' : '\n'));
#endif
		ctr = 0;
        dfs(0, 0, up_down);
        dfs(0, 0, left_right);
		printf("Number of solutions: %d\n", ctr);
	}
	return 0;
}

/*
Sample input

1
4 6
+---+---+---+---+---+---+
|   |   |   |   |   |   |
|***|***|** |** |** |***|
|   |   | * | * | * |   |
+---+---+---+---+---+---+
|   |   |   |   |   |   |
|   |** |** |***|** |** |
|   | * | * |   | * | * |
+---+---+---+---+---+---+
|   |   |   |   |   |   |
|***|** |***|***|***|** |
|   | * |   |   |   | * |
+---+---+---+---+---+---+
|   |   |   |   |   |   |
|** |   |***|   |** |** |
| * |   |   |   | * | * |
+---+---+---+---+---+---+

Output for sample input

Number of solutions: 2

*/

