
/*
	UVa 533 - Equation Solver

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_533_Equation_Solver.cpp

	from University of Ulm Local Contest 1997 Problem E
		(http://www.informatik.uni-ulm.de/acm/Locals/1997/)
*/

#include <cstdio>
#include <cctype>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif

struct linear_expression {
	int v_, c_;

	linear_expression() : v_(0), c_(0) {}
};

const int nr_chars_max = 100;
const char *ps;

int get_number()
{
	if (isdigit(*ps)) {
		int n = *ps++ - '0';
		while (isdigit(*ps)) {
			n = n * 10 + *ps++ - '0';
		}
		return n;
	}
	else
		return -1;
}

void expression(linear_expression& le);
void term(linear_expression& le);
void factor(linear_expression& le);

void expression(linear_expression& le)
{
	term(le);
	while (*ps == '+' || *ps == '-') {
		char c = *ps++;
		linear_expression le_;
		term(le_);
		if (c == '+')
			le.v_ += le_.v_, le.c_ += le_.c_;
		else
			le.v_ -= le_.v_, le.c_ -= le_.c_;
	}
}

void term(linear_expression& le)
{
	factor(le);
	while (*ps == '*') {
		ps++;
		linear_expression le_;
		factor(le_);
		le.v_ = le.c_ * le_.v_ + le.v_ * le_.c_;
		le.c_ *= le_.c_;
	}
}

void factor(linear_expression& le)
{
	int n = get_number();
	if (n != -1)
		le.c_ = n;
	else if (*ps == 'x')
		ps++, le.v_ = 1;
	else {
#ifndef ONLINE_JUDGE
		assert(*ps == '(');
#endif
		ps++;
		expression(le);
#ifndef ONLINE_JUDGE
		assert(*ps == ')');
#endif
		ps++;
	}
}

int main()
{
	char s[nr_chars_max + 1];
	for (int eq = 1; gets(s); eq++) {
		if (eq > 1)
			putchar('\n');
		ps = s;
		linear_expression lle, rle;
		expression(lle);
#ifdef DEBUG
		printf("%d*x + %d\n",  lle.v_, lle.c_);
#endif
#ifndef ONLINE_JUDGE
		assert(*ps == '=');
#endif
		ps++;
		expression(rle);
#ifdef DEBUG
		printf("%d*x + %d\n",  rle.v_, rle.c_);
#endif
		printf("Equation #%d\n", eq);
		int v = lle.v_, c = lle.c_;
		v -= rle.v_, c -= rle.c_;
		if (v)
			printf("x = %.6lf\n", static_cast<double>(-c) / v);
		else if (c)
			puts("No solution.");
		else
			puts("Infinitely many solutions.");
	
	}
	return 0;
}

