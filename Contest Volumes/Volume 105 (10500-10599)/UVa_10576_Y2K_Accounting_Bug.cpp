
/*
	UVa 10576 - Y2K Accounting Bug

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10576_Y2K_Accounting_Bug.cpp
*/

#include <cstdio>

const int nr_months = 12, nr_posts = 8, nr_consecutive_posts = 5;
int s, d, max_amount, posts[nr_months];

void calculate_amount(int pi, int amount)
{
	if (pi == nr_posts) {
		amount = 0;
		for (int i = 0; i < nr_months; i++) {
#ifdef DEBUG
			printf("%d%c", posts[i], ((i < nr_months - 1) ? ' ' : '\n'));
#endif
			amount += posts[i];
		}
		if (amount > max_amount)
			max_amount = amount;
	}
	else if (!pi) {
		int i;
		for (i = 0; i < nr_consecutive_posts; i++) {
			posts[i] = s;
			amount += s;
		}
		for (i--; i >= 0 && amount >= 0; i--) {
			posts[i] = -d;
			amount -= s + d;
		}
		calculate_amount(pi + 1, amount);
	}
	else {
		amount -= posts[pi - 1];
		posts[pi + nr_consecutive_posts - 1] = (amount + s < 0) ? s : -d;
		amount += posts[pi + nr_consecutive_posts - 1];
		calculate_amount(pi + 1, amount);
	}
}

int main()
{
	while (scanf("%d %d", &s, &d) != EOF) {
		max_amount = -1;
		calculate_amount(0, 0);
		if (max_amount >= 0)
			printf("%d\n", max_amount);
		else
			puts("Deficit");
	}
	return 0;
}

