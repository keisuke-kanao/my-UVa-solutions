
/*
	UVa 11831 - Sticker Collector Robot

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11831_Sticker_Collector_Robot.cpp
*/

#include <cstdio>
#include <cctype>

const int n_max = 100, m_max = 100, s_max = 50000;

char arena[n_max][m_max + 1];
char instructions[s_max + 1];

enum {north, south, east, west};

int turn(int dir, bool right)
{
	switch (dir) {
	case north:
		dir = (right) ? east : west; break;
	case south:
		dir = (right) ? west : east; break;
	case east:
		dir = (right) ? south : north; break;
	case west:
		dir = (right) ? north : south; break;
	}
	return dir;
}

int main()
{
	while (true) {
		int n, m, s;
		scanf("%d %d %d", &n, &m, &s);
		if (!n && !m && !s)
			break;
		int r, c, sr = -1, sc, dir;
		for (r = 0; r < n; r++) {
			scanf("%s", arena[r]);
			if (sr == -1) {
				for (c = 0; c < m; c++)
					if (isalpha(arena[r][c])) {
						sr = r; sc = c;
						switch (arena[r][c]) {
						case 'N':
							dir = north; break;
						case 'S':
							dir = south; break;
						case 'L':
							dir = east; break;
						case 'O':
							dir = west; break;
						}
					}
			}
		}
		scanf("%s", instructions);
		int stickers = 0;
		for (const char* pi = instructions; *pi; pi++) {
			switch (*pi) {
			case 'D':
				dir = turn(dir, true);
				break;
			case 'E':
				dir = turn(dir, false);
				break;
			case 'F':
				switch (dir) {
				case north:
					r = sr - 1; c = sc; break;
				case south:
					r = sr + 1; c = sc; break;
				case east:
					r = sr; c = sc + 1; break;
				case west:
					r = sr; c = sc - 1; break;
				}
				if (r >= 0 && r < n && c >= 0 && c < m && arena[r][c] != '#') {
					if (arena[r][c] == '*') {
						arena[r][c] = '.';
						stickers++;
					}
					sr = r; sc = c;
				}
				break;
			}
		}
		printf("%d\n", stickers);
	}
	return 0;
}

