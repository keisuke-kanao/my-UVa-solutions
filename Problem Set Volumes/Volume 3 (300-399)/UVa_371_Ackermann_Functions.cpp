
/*
	UVa 371 - Ackermann Functions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_371_Ackermann_Functions.cpp
*/

#include <iostream>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_cache_max = 2097152;
int cache[nr_cache_max]; // cache[i] is the sequence length of i

int sequence_length(int n)
{
	if (n < nr_cache_max && cache[n])
		return cache[n];
	else {
		int length = 0;
		long long m = n;
		while (true) {
			if (m & 1) {
				m *= 3; m++;
			}
			else
				m >>= 1;
			length++;
			if (m == 1)
				break;
			else if (m < nr_cache_max && cache[m]) {
				length += cache[m];
				break;
			}
		}
		if (n < nr_cache_max)
			cache[n] = length;
		return length;
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = -1;
#endif
	while (true) {
		int l, h;
		cin >> l >> h;
#ifdef __ELAPSED_TIME__
		if (start == -1)
			start = clock();
#endif
		if (!l && !h)
			break;
		if (l > h)
			swap(l, h);
		int max_i, max_length = -1;
		for (int i = l; i <= h; i++) {
			int length = sequence_length(i);
			if (length > max_length) {
				max_i = i;
				max_length = length;
			}
		}
		cout << "Between " << l << " and " << h << ", " << max_i <<
			" generates the longest sequence of " << max_length << " values.\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

