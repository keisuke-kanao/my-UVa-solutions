
/*
	UVa 654 - Ratio

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_654_Ratio.cpp
*/

/*
654 - Ratio

From a given numerator A and denominator B, construct ratios starting with denominator 1 which closest to the actual value of A/B. 
Keep computing ratios that are getting closer and closer to the actual value until our approximation equal to A/B.
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	int printed = false;
	int numerator, denominator, g;
	while (scanf("%d %d", &numerator, &denominator) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		if (!denominator)
			continue;
		if (!numerator) {
			puts("0/1");
			continue;
		}
		g = gcd(numerator, denominator);
		numerator /= g, denominator /= g;
		long long pn = static_cast<long long>(static_cast<double>(numerator) / denominator + 0.5), pd = 1,
			pdiff = llabs(numerator * pd - denominator * pn);
		printf("%lld/%lld\n", pn, pd);
 		for (long long d = 2; d < denominator; d++) {
			for (long long n = 0; n <= static_cast<long long>(ceil(static_cast<double>(numerator * d) / denominator)); n++) {
				int diff = llabs(numerator * d - denominator * n);
				if (pd * diff < d * pdiff) {
					printf("%lld/%lld\n", n, d);
					pd = d, pn = n, pdiff = llabs(numerator * pd - denominator * pn);
					break;
				}
			}
		}
		printf("%d/%d\n", numerator, denominator);
	}
	return 0;
}

