
/*
	UVa 1589 - Xiangqi

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1589_Xiangqi.cpp
*/

#include <utility>
#include <cstdio>
using namespace std;

const int N_max = 7, row_min = 1, row_max = 10, column_min = 1, column_max = 9;
const int bg_row_min = 1, bg_row_max = 3, bg_column_min = 4, bg_column_max = 6;
const int nr_g_dirs = 4;
int g_dirs[nr_g_dirs][2] = {
	{0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

int N;

struct piece {
	char t_; // type
	int r_, c_;
} bg, pieces[N_max];

bool captured_by_general(int pi, int r, int c)
{
	const piece& p = pieces[pi];
	if (p.c_ != c)
		return false;
	for (int i = 0; i < N; i++) {
		if (i == pi)
			continue;
 		if (pieces[i].c_ == c) {
			if (pieces[i].r_ == r)
				continue;
			else if (pieces[i].r_ < p.r_)
				return false;
		}
	}
#ifdef DEBUG
		printf("captured by %d-th general: (%d, %d)\n", pi, r, c);
#endif
	return true; // flying general
}

bool captured_by_chariot(int pi, int r, int c)
{
	const piece& p = pieces[pi];
	if (p.r_ == r && p.c_ == c)
		return false; // captured by the black general
	else if (p.r_ == r) {
		for (int i = 0; i < N; i++) {
			if (i == pi)
				continue;
 			if (pieces[i].r_ == r) {
				if (pieces[i].c_ == c)
					continue;
				else if (pieces[i].c_ > c && pieces[i].c_ < p.c_ || pieces[i].c_ > p.c_ && pieces[i].c_ < c)
					return false;
			}
		}
#ifdef DEBUG
		printf("captured by %d-th chariot: (%d, %d)\n", pi, r, c);
#endif
		return true;
	}
	else if (p.c_ == c) {
		for (int i = 0; i < N; i++) {
			if (i == pi)
				continue;
 			if (pieces[i].c_ == c) {
				if (pieces[i].r_ == r)
					continue;
				else if (pieces[i].r_ > r && pieces[i].r_ < p.r_ || pieces[i].r_ > p.r_ && pieces[i].r_ < r)
					return false;
			}
		}
#ifdef DEBUG
		printf("captured by %d-th chariot: (%d, %d)\n", pi, r, c);
#endif
		return true;
	}
	else
		return false;
}

bool captured_by_horse(int pi, int r, int c)
{
	const int nr_h_dirs = 8;
	const int h_dirs[nr_h_dirs][2] = {
		{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}
	};

	const piece& p = pieces[pi];
	if (p.r_ == r && p.c_ == c)
		return false; // captured by the black general
	for (int i = 0; i < nr_h_dirs; i++) {
		int hr = p.r_ + h_dirs[i][0], hc = p.c_ + h_dirs[i][1];
		if (hr < row_min || hr > row_max || hc < column_min || hc > column_max)
			continue;
		if (hr == r && hc == c) {
			int hhr = p.r_ + g_dirs[i / 2][0], hhc = p.c_ + g_dirs[i / 2][1];
			for (int j = 0; j < N; j++) {
				if (j == pi)
					continue;
				if (pieces[j].r_ == hhr && pieces[j].c_ == hhc) // hobbling the horse's leg
					return false;
			}
#ifdef DEBUG
			printf("captured by %d-th horse: (%d, %d)\n", pi, r, c);
#endif
			return true;
		}
	}
	return false;
}

bool captured_by_cannon(int pi, int r, int c)
{
	const piece& p = pieces[pi];
	if (p.r_ == r && p.c_ == c)
		return false; // captured by the black general
	else if (p.r_ == r) {
		bool once = false;
		for (int i = 0; i < N; i++) {
			if (i == pi)
				continue;
 			if (pieces[i].r_ == r) {
				if (pieces[i].c_ == c)
					continue;
				else if (pieces[i].c_ > c && pieces[i].c_ < p.c_ || pieces[i].c_ > p.c_ && pieces[i].c_ < c) {
					if (once)
						return false;
					else
						once = true;
				}
			}
		}
		if (once) {
#ifdef DEBUG
			printf("captured by %d-th cannon: (%d, %d)\n", pi, r, c);
#endif
			return true;
		}
		else
			return false;
	}
	else if (p.c_ == c) {
		bool once = false;
		for (int i = 0; i < N; i++) {
			if (i == pi)
				continue;
 			if (pieces[i].c_ == c) {
				if (pieces[i].r_ == r)
					continue;
				else if (pieces[i].r_ > r && pieces[i].r_ < p.r_ || pieces[i].r_ > p.r_ && pieces[i].r_ < r) {
					if (once)
						return false;
					else
						once = true;
				}
			}
		}
		if (once) {
#ifdef DEBUG
			printf("captured by %d-th cannon: (%d, %d)\n", pi, r, c);
#endif
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

int main()
{
	while (true) {
		scanf("%d %d %d", &N, &bg.r_, &bg.c_);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			char t[2];
			scanf("%s %d %d", t, &pieces[i].r_, &pieces[i].c_);
			pieces[i].t_ = t[0];
		}
		int nr_moves = 0;
		for (int i = 0; i < nr_g_dirs; i++) {
			int r = bg.r_ + g_dirs[i][0], c = bg.c_ + g_dirs[i][1];
			if (r < bg_row_min || r > bg_row_max || c < bg_column_min || c > bg_column_max)
				continue;
			nr_moves++;
			bool captured = false;
#ifdef DEBUG
			for (int j = 0; j < N; j++)
				switch (pieces[j].t_) {
				case 'G':
					captured |= captured_by_general(j, r, c);
					break;
				case 'R':
					captured |= captured_by_chariot(j, r, c);
					break;
				case 'H':
					captured |= captured_by_horse(j, r, c);
					break;
				case 'C':
					captured |= captured_by_cannon(j, r, c);
					break;
				}
#else
			for (int j = 0; j < N && !captured; j++)
				switch (pieces[j].t_) {
				case 'G':
					captured = captured_by_general(j, r, c);
					break;
				case 'R':
					captured = captured_by_chariot(j, r, c);
					break;
				case 'H':
					captured = captured_by_horse(j, r, c);
					break;
				case 'C':
					captured = captured_by_cannon(j, r, c);
					break;
				}
#endif
			if (captured)
				nr_moves--;
		}
		puts((!nr_moves) ? "YES" : "NO");
	}
	return 0;
}

