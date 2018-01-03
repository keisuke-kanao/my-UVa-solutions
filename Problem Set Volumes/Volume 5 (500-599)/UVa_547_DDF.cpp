
/*
	UVa 547 - DDF

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_547_DDF.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

const int DDF_max = 3000;

struct DDF {
	int nr_seqs_; // number of integers comprising a DDF sequence
	int next_; // next integer of a DDF sequence
} DDFs[DDF_max + 1];

int sum_of_digits(int n)
{
	int s = 0;
	do {
		s += n % 10;
		n /= 10;
	} while (n);
	return s;
}

int sum_of_digits_of_factors(int n)
{
	int s = 0;
	for (int i = 1; i <= static_cast<int>(sqrt(static_cast<double>(n))); i++)
		if (!(n % i)) {
			s += sum_of_digits(i);
			if (n / i > i)
				s += sum_of_digits(n / i);
		}
#ifndef ONLINE_JUDGE
	assert(s < 1000);
#endif
	return s;
}

int follow_DDF(int n)
{
	int s = sum_of_digits_of_factors(n);
	DDFs[n].next_ = s;
	if (s == n)
		return 0;
	if (DDFs[s].nr_seqs_)
		DDFs[n].nr_seqs_ = DDFs[s].nr_seqs_ + 1;
	else
		DDFs[n].nr_seqs_ = follow_DDF(s) + 1;
	return DDFs[n].nr_seqs_;
}

void print_DDF(int n)
{
	while (true) {
		printf(" %d", n);
		if (DDFs[n].next_ == n)
			break;
		n = DDFs[n].next_;
	}
	putchar('\n');
}

int main()
{
	for (int i = 1; i <= DDF_max; i++) {
		if (!DDFs[i].nr_seqs_)
			follow_DDF(i);
#ifdef DEBUG
		print_DDF(i);
#endif
	}
	for (int i = 1; ; i++) {
		int m, n;
		if (scanf("%d %d", &m, &n) == EOF)
			break;
		int j_max, nr_seqs_max = -1;
		for (int j = min(m, n), k = max(m, n); j <= k; j++)
			if (DDFs[j].nr_seqs_ > nr_seqs_max) {
				j_max = j;
				nr_seqs_max = DDFs[j].nr_seqs_;
			}
		printf("Input%d: %d %d\n", i, m, n);
		printf("Output%d:", i);
		print_DDF(j_max);
	}
	return 0;
}

