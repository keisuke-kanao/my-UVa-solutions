
/*
	UVa 426 - Fifth Bank of Swamp County

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_426_Fifth_Bank_of_Swamp_County.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

#ifndef BUFSIZ
#define BUFSIZ	1024
#endif

const int number_max = 9999;

struct check {
	int y_, m_, d_;
	int number_;
	double amount_;

bool operator<(const check& c) const {return number_ < c.number_;}
} checks[number_max];

int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	getchar();
	while (N--) {
		char s[BUFSIZ];
		int nr_checks = 0;
		while (gets(s) && s[0]) {
			char *p = s, *q;
			check& c = checks[nr_checks];
			c.y_ = strtol(p, &q, 10);
			p = ++q;
			c.m_ = strtol(p, &q, 10);
			p = ++q;
			c.d_ = strtol(p, &q, 10);
			p = q;
			c.number_ = strtol(p, &q, 10);
			c.amount_ = strtod(q, NULL);
			if (c.amount_ < 1000000.0)
				nr_checks++;
		}
		sort(checks, checks + nr_checks);
		int nr_rows = (nr_checks + 2) / 3;
		for (int i = 0; i < nr_rows; i++)
			for (int j = i; j < nr_checks; j += nr_rows) {
				const check& c = checks[j];
				printf("%4d%c %9.2lf %02d/%02d/%02d%s", c.number_,
					((j && c.number_ != checks[j - 1].number_ + 1) ? '*' : ' '),
					c.amount_, c.y_, c.m_, c.d_,
					((j + nr_rows < nr_checks) ? "   " : "\n"));
			}
		if (N)
			putchar('\n');
	}
	return 0;
}

