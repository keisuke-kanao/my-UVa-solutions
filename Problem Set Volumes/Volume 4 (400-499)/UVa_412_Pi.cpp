
/*
	UVa 412 - Pi

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_412_Pi.cpp

	from 1995 ACM East Central Regional Contest Problem A
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1995/index.html)
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		const int nr_integers_max = 50;
		int integers[nr_integers_max];
		for (int i = 0; i < n; i++)
			cin >> integers[i];
		int numerator = 0, denominator = 0;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++, denominator++)
				if (gcd(integers[i], integers[j]) == 1) // coprime
					numerator++;
		if (numerator)
			printf("%.6lf\n", sqrt((static_cast<double>(denominator) * 6.0) / static_cast<double>(numerator)));
		else
			printf("No estimate for this data set.\n");
	}
	return 0;
}

