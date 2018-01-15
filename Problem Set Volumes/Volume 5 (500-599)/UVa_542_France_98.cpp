
/*
	UVa 542 - France '98

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_542_France_98.cpp

	From International Collegiate Programming Contest 1998/99 University of Ulm Local Contest 1998 Problem F
		(https://cs05.informatik.uni-ulm.de/acm/Locals/1998/)
*/

#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
	const int nr_countries = 16, nr_rounds = 4;
	string countries[nr_countries];
	for (int i = 0; i < nr_countries; i++)
		cin >> countries[i];
	double p[nr_countries][nr_countries];
	for (int i = 0; i < nr_countries; i++)
		for (int j = 0; j < nr_countries; j++) {
			double pp;
			cin >> pp;
			p[i][j] = pp / 100.0;
	}
	double wp[nr_rounds + 1][nr_countries];
		// wp[i][j] is the winning probability of country i at round j
	for (int i = 0; i < nr_countries; i++)
		wp[0][i] = 1.0;
	for (int r = 1, s = 2, t = 1; r <= nr_rounds; r++, s *= 2, t *= 2)
		for (int i = 0; i < nr_countries; i++) { // i: index of country to calcuate the winning probability at round r
			double wpi = 0.0;
			for (int j = 0; j < nr_countries; j++) // index of opponent country
				if (i / s == j / s && i / t != j / t)
					wpi += p[i][j] * wp[r - 1][j];
			wp[r][i] = wpi * wp[r - 1][i];
		}
	for (int i = 0; i < nr_countries; i++)
		printf("%-10s p=%.2lf%%\n", countries[i].c_str(), wp[nr_rounds][i] * 100.0);
	return 0;
}

