
/*
	UVa 11549 - Calculator Conundrum

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11549_Calculator_Conundrum.cpp
*/

#include <set>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	const int power_of_10s[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (k < 2)
			printf("%d\n", k);
		else {
			int power_of_10 = power_of_10s[n];
			int k_max = power_of_10 - 1, displayed_max = 0;
			set<int> displayed_numbers;
			while (true) {
				if (k == k_max) {
					displayed_max = k; break;
				}
				pair<set<int>::iterator, bool> result = displayed_numbers.insert(k);
				if (!result.second)
					break;
				if (k > displayed_max)
					displayed_max = k;
				long long lk = k;
				lk *= lk;
				int nr_digits = static_cast<int>(log10(static_cast<double>(lk)) + 1.0);
				if (nr_digits > n)
					lk /= power_of_10s[nr_digits - n];
				k = static_cast<int>(lk);
#ifdef DEBUG
				printf("%d\n", k);
#endif
			}
			printf("%d\n", displayed_max);
		}
	}
	return 0;
}

