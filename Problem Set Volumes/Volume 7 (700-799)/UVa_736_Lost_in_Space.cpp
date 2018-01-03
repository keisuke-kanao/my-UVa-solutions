
/*
	UVa 736 - Lost in Space

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_736_Lost_in_Space.cpp
*/

#include <cstdio>

const int nr_dirs = 8, N_max = 50;

const struct dir {
	const char* s_;
	int r_, c_;
} dirs[nr_dirs] = {
	{"N", -1, 0}, {"NE", -1, 1}, {"E", 0, 1}, {"SE", 1, 1},
	{"S", 1, 0}, {"SW", 1, -1}, {"W", 0, -1}, {"NW", -1, -1}
};

bool appear(int N, const char strings[N_max][N_max + 1], const char s[N_max + 1], int r, int c, int dr, int dc)
{
	for (int i = 1; s[i]; i++) {
		do {
			r += dr, c += dc;
			if (r < 0 || r >= N || c < 0 || c >= N)
				return false;
		} while (strings[r][c] == ' ');
		if (strings[r][c] != s[i])
			return false;
	}
	return true;
}

int main()
{
	int ds;
	scanf("%d", &ds);
	while (ds--) {
		int N;
		scanf("%d", &N);
		getchar();
		char strings[N_max][N_max + 1];
		for (int r = 0; r < N; r++)
			gets(strings[r]);
		while (true) {
			char s[N_max + 1];
			if (!gets(s) || !s[0])
				break;
			printf("\n%s\n", s);
			bool found = false;
			for (int r = 0; r < N; r++)
				for (int c = 0; c < N; c++)
					if (strings[r][c] == s[0])
						for (int d = 0; d < nr_dirs; d++)
							if (appear(N, strings, s, r, c, dirs[d].r_, dirs[d].c_)) {
								found = true;
								printf("(%d,%d) - %s\n", r + 1, c + 1, dirs[d].s_);
							}
			if (!found)
				puts("not found");
		}
		if (ds)
			putchar('\n');
	}
	return 0;
}

