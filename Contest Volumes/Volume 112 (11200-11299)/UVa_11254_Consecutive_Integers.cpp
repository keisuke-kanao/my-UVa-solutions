
/*
	UVa 11254 - Consecutive Integers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11254_Consecutive_Integers.cpp
*/

/*
Polite number (https://en.wikipedia.org/wiki/Polite_number)
	In number theory, a polite number is a positive integer that can be written as the sum of two or more consecutive positive integers. 
	Other positive integers are impolite.
	The impolite numbers are exactly the powers of two.
*/

#include <algorithm>
#include <iterator>
#include <cstdio>
using namespace std;

const int nr_sums_max = 44721;
int sums[nr_sums_max + 1];
int power_of_2s[] = {
	2, 4, 8, 16, 32, 64, 128, 256,
	512, 1024, 2048, 4096, 8192, 16384, 32768, 65536,
	131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216,
	33554432, 67108864, 134217728, 268435456, 536870912
};

int main()
{
	for (int i = 1; i <= nr_sums_max; i++)
		sums[i] = sums[i - 1] + i;
#ifdef DEBUG
	printf("%d\n", sums[nr_sums_max]); // 1000006281
#endif
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == -1)
			break;
		if (binary_search(power_of_2s, power_of_2s + sizeof(power_of_2s) / sizeof(int), n))
			printf("%d = %d + ... + %d\n", n, n, n);
		else {
			for (int i = distance(sums, lower_bound(sums, sums + nr_sums_max + 1, n)); ; i--)
				if (!((n - sums[i]) % i)) {
					int j = (n - sums[i]) / i;
					printf("%d = %d + ... + %d\n", n, j + 1, i + j);
					break;
				}
		}
	}
	return 0;
}

