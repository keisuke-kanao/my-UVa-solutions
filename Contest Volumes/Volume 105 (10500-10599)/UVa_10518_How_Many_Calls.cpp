
/*
	UVa 10518 - How Many Calls?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10518_How_Many_Calls.cpp
*/

/*
Let nr_calls_fib(n) be the number of calls to evaluate the n-th (n > 0) fibonacci number, then:
	nr_calls_fib(n) = 2 * fib(n) - 1
*/

#include <cstdio>

long long fib_mod(long long n, int m) // calculate fib(n) mod m in O(log2(n))
{
	long long i = 1, h = 1, j = 0, k = 0, t;
	for ( ; n > 0; n >>= 1) {
		if (n & 1) {
			t = j * h % m;
			j = i * h % m + j * k % m + t;
			i = i * k % m + t;
		}
		t = h * h % m;
		h = 2 * k * h % m + t;
		k = k * k % m + t;
	}
	return j;
}

int main()
{
	for (int c = 1; ; c++) {
		long long n;
		int b;
		scanf("%lld %d", &n, &b);
		if (!n && !b)
			break;
		int nr_calls = 1 % b;
		if (n) {
			long long fb = fib_mod(n + 1, b);
			nr_calls = static_cast<int>((2 * fb - 1 + b) % b);
		}
		printf("Case %d: %lld %d %d\n", c, n, b, nr_calls);
	}
	return 0;
}

