
/*
	UVa 707 - Robbery

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_707_Robbery.cpp

	from Mid-Central European Regional Contest 1999
*/

#include <cstdio>

const int W_max = 100, H_max = 100, t_max = 100;
int W, H, t, city[t_max + 1][H_max + 1][W_max + 1];

struct deduction {
	int r_, c_;
} deductions[t_max + 1];

const int nr_moves = 5;
const int moves[nr_moves][2] = {{0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void deduce(int ti, int r, int c)
{
#ifdef DEBUG
	printf("%d %d %d\n", ti, r, c);
#endif
	if (deductions[ti].r_ == -1)
		deductions[ti].r_ = r, deductions[ti].c_ = c;
	else if (r != deductions[ti].r_ || c != deductions[ti].c_)
		deductions[ti].c_ = -1;
}

int move(int ti, int r, int c)
{
	int& result = city[ti][r][c];
	if (result != -1)
		return result;
	if (ti == t) {
		result = 1;
		deduce(ti, r, c);
	}
	else {
		result = 0;
		for (int i = 0; i < nr_moves; i++) {
			int nr = r + moves[i][0], nc = c + moves[i][1];
			if (nr > 0 && nr <= H && nc > 0 && nc <= W && move(ti + 1, nr, nc)) {
				result = 1;
				deduce(ti, r, c);
			}
		}
	}
	return result;
}

int main()
{
	for (int nr = 1; ; nr++) {
		scanf("%d %d %d", &W, &H, &t);
		if (!W)
			break;
		for (int i = 1; i <= t; i++) {
			for (int j = 1; j <= H; j++)
				for (int k = 1; k <= W; k++)
					city[i][j][k] = -1;
			deductions[i].r_ = deductions[i].c_ = -1;
		}
		int n;
		scanf("%d", &n);
		while (n--) {
			int ti, Li, Ti, Ri, Bi;
			scanf("%d %d %d %d %d", &ti, &Li, &Ti, &Ri, &Bi);
			for (int i = Ti; i <= Bi; i++)
				for (int j = Li; j <= Ri; j++)
					city[ti][i][j] = 0;
		}
		for (int i = 1; i <= H; i++)
			for (int j = 1; j <= W; j++)
				move(1, i, j);
		printf("Robbery #%d:\n", nr);
		if (deductions[t].r_ == -1)
			puts("The robber has escaped.\n");
		else {
			int nr_deductions = 0;
			for (int i = 1; i <= t; i++)
				if (deductions[i].c_ != -1) {
					nr_deductions++;
					printf("Time step %d: The robber has been at %d,%d.\n", i, deductions[i].c_, deductions[i].r_);
				}
			if (nr_deductions)
				putchar('\n');
			else
				puts("Nothing known.\n");
		}
	}
	return 0;
}

