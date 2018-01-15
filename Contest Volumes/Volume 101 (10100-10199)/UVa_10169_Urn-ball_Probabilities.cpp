
/*
	UVa 10169 - Urn-ball Probabilities !

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10169_Urn-ball_Probabilities.cpp
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int n_max = 1000000;
double p[n_max + 1];
	// p[i] is the probability that you have not picked up two red balls in all of your pick-ups in i pick-ups
double q[n_max + 1];
	// q[i] is number of zeros in probability that all of your pick ups has both balls as red in i pick-ups

int main()
{
	p[0] = 1.0; q[0] = 0.0;
	for (int i = 1; i <= n_max; i++) {
		double d = static_cast<double>(i);
		p[i] = p[i - 1] * (d * (d + 1.0) - 1.0) / (d * (d + 1.0));
		q[i] = q[i - 1] - log10(1.0 / (d * (d + 1.0)));
	}
	int n;
	while (cin >> n)
		printf("%.6lf %d\n", 1.0 - p[n], static_cast<int>(q[n]));
	return 0;
}

