
/*
	UVa 10883 - Supermean

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10883_Supermean.cpp
*/

/*
It's a combinatory problem. As you see a naive solution won't work since finding means that way might take a running time of 50000^2

But we can find a sequence like this: supermean = ((n-1)C0 * a1 + (n-1)C1 * a2 + .....+(n-1)Cmid-1 * a mid + ... + (n-1)C0 * an) / 2 ^ (n-1)

which helps us to find solution in O(n)

Again the problem is, for 50000 numbers this will overflow. Hence, you can split the numbers using logarithm function. A pow function won't work!

Also consider negative numbers for logarithm. Happy hunting!


{Σnumbers[k]*C(n - 1, k) (k = 0, 1, ..., n - 1)}/2^(n - 1)

*/

#include <cstdio>
#include <cmath>

const int n_max = 50000;
double sums_of_log2s[n_max + 1];
	// sums_of_log2s[i] is the sum of log2[i] (i = 1, 2, ..., i)
int numbers[n_max];

double coefficient(int n, int k)
{
	double d = static_cast<double>(-n);
	if (k)
		d += sums_of_log2s[n] - sums_of_log2s[n - k] - sums_of_log2s[k];
	return pow(2.0, d);
}

int main()
{
	double s = 0.0;
	for (int i = 1; i <= n_max; i++) {
		s += log2(static_cast<double>(i));
		sums_of_log2s[i] = s;
	}
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int n;
		scanf("%d", &n);
		double sm = 0.0, d;
		for (int k = 0; k < n; k++) {
			scanf("%lf", &d);
			sm += coefficient(n - 1, k) * d;
		}
		printf("Case #%d: %.3lf\n", cn, sm);
	}
	return 0;
}

