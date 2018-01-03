
/*
	UVa 810 - A Dicey Problem

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_810_A_Dicey_Problem.cpp
*/

/*
	A cumbersome DFS problem.
	I wrote the solution while watching a real die in hand.
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const int nr_sides = 6, nr_chars_max = 20, R_max = 10, C_max = 10;

enum {start, up, down, left, right};

int R, C, sr, sc, maze[R_max][C_max];

struct state {
	int dir_, t_, f_; // direction, top, face
} states[R_max][C_max][nr_sides + 1][nr_sides + 1];
	// states[r][c][t][f].t_ is non-zero if postion (r, c) has been visited with the die of top t and face f

const struct {
	int l_, r_;
} next_tops[nr_sides + 1][nr_sides + 1] = // next_tops[t][f]
{
	{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
	{{0, 0}, {0, 0}, {3, 4}, {5, 2}, {2, 5}, {4, 3}, {0, 0}},
	{{0, 0}, {4, 3}, {0, 0}, {1, 6}, {6, 1}, {0, 0}, {3, 4}},
	{{0, 0}, {2, 5}, {6, 1}, {0, 0}, {0, 0}, {1, 6}, {5, 2}},
	{{0, 0}, {5, 2}, {1, 6}, {0, 0}, {0, 0}, {6, 1}, {2, 5}},
	{{0, 0}, {3, 4}, {0, 0}, {6, 1}, {1, 6}, {0, 0}, {4, 3}},
	{{0, 0}, {0, 0}, {4, 3}, {2, 5}, {5, 2}, {3, 4}, {0, 0}}
};

int nr_paths;
struct {
	int r_, c_;
} paths[R_max * C_max * nr_sides * nr_sides];

int movable(int r, int c, int t)
{
	if (r < 0 || r >= R || c < 0 || c >= C)
		return -1;
	if (maze[r][c] == -1 || maze[r][c] == t)
		return (r == sr && c == sc) ? 1 : 0;
	else
		return -1;
}

void print_path()
{
	printf("  ");
	for (int count = 9; nr_paths; ) {
		printf("(%d,%d)", paths[nr_paths - 1].r_ + 1, paths[nr_paths - 1].c_ + 1);
		if (!--nr_paths)
			putchar('\n');
		else {
			putchar(',');
			if (!--count) {
				printf("\n  ");
				count = 9;
			}
		}
	}
}

bool trace_back_path(int r, int c, int t, int f, int dir)
{
	paths[nr_paths].r_ = r, paths[nr_paths].c_ = c;
	nr_paths++;
	int pr, pc, pt, pf;
	switch (dir) {
	case start:
		print_path();
		return true;
	case up:
		pr = r + 1, pc = c, pt = abs(nr_sides + 1 - f), pf = t;
		break;
	case down:
		pr = r - 1, pc = c, pt = f, pf = abs(nr_sides + 1 - t);
		break;
	case left:
		pr = r, pc = c + 1, pt = next_tops[t][f].r_, pf = f;
		break;
	case right:
		pr = r, pc = c - 1, pt = next_tops[t][f].l_, pf = f;
		break;
	}
	return trace_back_path(pr, pc, pt, pf, states[pr][pc][pt][pf].dir_);
}

bool dfs(int r, int c, int t, int f, int dir)
{
	state& s = states[r][c][t][f];
	if (s.t_)
		return false;
	s.dir_ = dir, s.t_ = t, s.f_ = f;
	int m;
	if ((m = movable(r - 1, c, t)) >= 0) { // up
		if (m)
			return trace_back_path(r - 1, c, f, abs(nr_sides + 1 - t), up);
		if (dfs(r - 1, c, f, abs(nr_sides + 1 - t), up))
			return true;
	}
	if ((m = movable(r + 1, c, t)) >= 0) { // down
		if (m)
			return trace_back_path(r + 1, c, abs(nr_sides + 1 - f), t, down);
		if (dfs(r + 1, c, abs(nr_sides + 1 - f), t, down))
			return true;
	}
	if ((m = movable(r, c - 1, t)) >= 0) { // left
		if (m)
			return trace_back_path(r, c - 1, next_tops[t][f].l_, f, left);
		if (dfs(r, c - 1, next_tops[t][f].l_, f, left))
			return true;
	}
	if ((m = movable(r, c + 1, t)) >= 0) { // right
		if (m)
			return trace_back_path(r, c + 1, next_tops[t][f].r_, f, right);
		if (dfs(r, c + 1, next_tops[t][f].r_, f, right))
			return true;
	}
	return false;
}

int main()
{
	while (true) {
		char name[nr_chars_max + 1];
		scanf("%s", name);
		if (!strcmp(name, "END"))
			break;
		int t, f;
		scanf("%d %d %d %d %d %d", &R, &C, &sr, &sc, &t, &f);
		sr--, sc--;
		for (int r = 0; r < R; r++)
			for (int c = 0; c < C; c++)
				scanf("%d", &maze[r][c]);
		memset(states, 0, sizeof(states));
		nr_paths = 0;
		printf("%s\n", name);
		if (dfs(sr, sc, t, f, start))
			;
		else
			puts("  No Solution Possible");
	}
	return 0;
}

