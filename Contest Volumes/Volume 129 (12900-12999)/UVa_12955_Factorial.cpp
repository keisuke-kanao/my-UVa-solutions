
/*
	UVa 12955 - Factorial

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12955_Factorial.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 100000, nr_factorials = 8;
const int factorials[nr_factorials] = {40320, 5040, 720, 120, 24, 6, 2, 1}; 
int min_nr_sums;

void sum_of_factorials(int n, int nr_sums)
{
	if (!n) {
		min_nr_sums = min(min_nr_sums, nr_sums);
		return;
	}
	if (n + nr_sums <= min_nr_sums) {
		for (int i = 0; i < nr_factorials; i++)
			if (n >= factorials[i])
				sum_of_factorials(n - factorials[i], nr_sums + 1);
	}
}

int main()
{
	int N;
	while (scanf("%d", &N) != EOF) {
		min_nr_sums = N;
		sum_of_factorials(N, 0);
		printf("%d\n", min_nr_sums);
	}
	return 0;
}

