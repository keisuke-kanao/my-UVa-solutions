
/*
	UVa 10056 - What is the Probability?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10056_What_is_the_Probability.cpp
*/

/*
	Let p(i) be the probability of the i-th player to win, then:
		p(i) = (1 - p)^(i - 1) * p + (1 - p)^(i - 1) * p * (1 - p)^N + (1 - p)^(i - 1) * p * (1 - p)^2N + ...
			 = (1 - p)^(i - 1) * p * Σ{(1 - p)^N}^k (k = 0 to ∞)
			 = {(1 - p)^(i - 1) * p} / {1 - (1 - p)^N}
*/

#include <iostream>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	int s;
	cin >> s;
	while (s--) {
		int n, i;
		double p;
		cin >> n >> p >> i;
		const double epsilon = numeric_limits<double>::epsilon();
		double npi = (p < epsilon) ?
			0.0 : pow(1.0 - p, static_cast<double>(i - 1)) * p / (1.0 - pow(1.0 - p, static_cast<double>(n)));
		printf("%.4lf\n", npi);
	}
	return 0;
}

