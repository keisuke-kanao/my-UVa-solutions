
/*
	UVa 784 - Maze Exploration

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_784_Maze_Exploration.cpp
*/

#include <cstdio>
#include <cstdlib>

const int nr_chars_per_line_max = 80, nr_lines_max = 30;

int get_start(const char* s)
{
	bool separation_line = true;
	for (const char* p = s; *p; p++) {
		if (*p == '*')
			return p - s;
		else if (*p != '_')
			separation_line = false;
	}
	return (separation_line) ? -1 : 0;
}

void explore_maze(int i, int j, char maze[nr_lines_max + 1][nr_chars_per_line_max + 1])
{
	maze[i][j] = '#';
	if (maze[i - 1][j] == ' ') // upper
		explore_maze(i - 1, j, maze);
	if (maze[i][j - 1] == ' ') // left
		explore_maze(i, j - 1, maze);
	if (maze[i][j + 1] == ' ') // right
		explore_maze(i, j + 1, maze);
	if (maze[i + 1][j] == ' ') // lower
		explore_maze(i + 1, j, maze);
}

int main()
{
	char maze[nr_lines_max + 1][nr_chars_per_line_max + 1];
	gets(maze[0]);
	int nr_mazes = atoi(maze[0]);
	int start_i, start_j;
	while (nr_mazes--) {
		int nr_lines = 0;
		while (true) {
			gets(maze[nr_lines]);
			int j = get_start(maze[nr_lines]);
			if (j > 0) {
				start_i = nr_lines; start_j = j;
			}
			nr_lines++;
			if (j == -1) // reach at a separation line
				break;
		}
		explore_maze(start_i, start_j, maze);
		for (int i = 0; i < nr_lines; i++)
			puts(maze[i]);
	}
	return 0;
}

