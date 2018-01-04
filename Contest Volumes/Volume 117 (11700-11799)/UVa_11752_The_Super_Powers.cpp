
/*
	UVa 11752 - The Super Powers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11752_The_Super_Powers.cpp
*/

#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 65536;
const int composite_numbers[] = {
	4, 6, 8, 9, 10,
	12, 14, 15, 16, 18, 20,
	21, 22, 24, 25, 26, 27, 28, 30,
	32, 33, 34, 35, 36, 38, 39, 40,
	42, 44, 45, 46, 48, 49, 50,
	51, 52, 54, 55, 56, 57, 58, 60,
	62, 63, 64
};

inline unsigned long long square(unsigned long long n)
{
	return n * n;
}

unsigned long long power(unsigned long long base, int exp)
{
	if (!exp)
		return 1;
	else if (!(exp & 1))
		return square(power(base, exp >>= 1));
	else
		return base * power(base, exp - 1);
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	const double log10_max = log10(static_cast<double>(numeric_limits<unsigned long long>::max()));
	vector<unsigned long long> super_powers;
	for (int i = 2; i < n_max; i++) {
		double c_max = log10_max / log10(static_cast<double>(i));
		for (int j = 0; composite_numbers[j] < c_max; j++) {
			super_powers.push_back(power(i, composite_numbers[j]));
#ifdef DEBUG
			printf("%d %d %llu\n", i, composite_numbers[j], super_powers.back());
#endif
		}
	}
#ifdef DEBUG
	printf("%d\n", super_powers.size());
#endif
	sort(super_powers.begin(), super_powers.end());
	vector<unsigned long long>::iterator se = unique(super_powers.begin(), super_powers.end());
	super_powers.resize(distance(super_powers.begin(), se));
#ifdef DEBUG
	printf("%d\n", super_powers.size());
#endif
	puts("1");
	for (size_t i = 0; i < super_powers.size(); i++)
		printf("%llu\n", super_powers[i]);
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

