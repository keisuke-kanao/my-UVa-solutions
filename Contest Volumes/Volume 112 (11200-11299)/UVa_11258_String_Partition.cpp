
/*
	UVa 11258 - String Partition

	To build using Visual Studio 2012:
		cl -EHsc -O2 -DONLINE_JUDGE UVa_11258_String_Partition.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

const int nr_digits_max = 200;
#ifdef ONLINE_JUDGE
long long max_sum[nr_digits_max];
	// max_s[i] is the max. sum of digits up to i
#else
long long max_sum[nr_digits_max][nr_digits_max];
	// max_s[i][j] is the max. sum of digits bewteen i-th and j-th
#endif

int get_integer(const char s[], int si, int sj)
{
	long long i = s[si++] - '0';
	for ( ; si <= sj; si++) {
		i *= 10;
		i += s[si] - '0';
		if (i > INT_MAX)
			return -1;
	}
	return i;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		char digits[nr_digits_max + 1];
		scanf("%s", digits);
		int n = strlen(digits);
#if ONLINE_JUDGE
		max_sum[0] = digits[0] - '0';
		for (int i = 1; i < n; i++) {
			long long max_s = get_integer(digits, 0, i);
			for (int j = 1; j <= 10 && j <= i; j++) {
				int k = get_integer(digits, i - j + 1, i);
				if (k != -1)
					max_s = max(max_s, max_sum[i - j] + k);
			}
			max_sum[i] = max_s;
		}
		printf("%lld\n", max_sum[n - 1]);
#else
		for (int i = 0; i < n; i++)
			max_sum[i][i] = digits[i] - '0';
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n - k; i++) {
				long long max_s = get_integer(digits, i, i + k);
				for (int j = i; j < i + k; j++)
					max_s = max(max_s, max_sum[i][j] + max_sum[j + 1][i + k]);
				max_sum[i][i + k] = max_s;
			}
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			printf("%lld%c", max_sum[i][j], ((j < n - 1) ? ' ' : '\n'));
#endif
		printf("%lld\n", max_sum[0][n - 1]);
#endif
	}
	return 0;
}

