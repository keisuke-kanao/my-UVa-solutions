
/*
	UVa 10408 - Farey sequences

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10408_Farey_sequences.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 1000;
bool coprimes[n_max + 1][n_max + 1]; // coprimes[i][j] is true if i and j is coprime

struct fraction {
	int numerator_, denominator_;

	fraction() : numerator_(1), denominator_(1) {}
	fraction(int n, int d) : numerator_(n), denominator_(d) {}
	bool operator<(const fraction& f) const {return numerator_ * f.denominator_ < f.numerator_ * denominator_;}
} fractions[n_max * n_max];

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	for (int i = 2; i <= n_max; i++)
		for (int j = 1; j < i; j++)
			if (gcd(i, j) == 1)
				coprimes[i][j] = coprimes[j][i] = true;
	int n, k;
	while (cin >> n >> k) {
		int nr_fractions = 0;
		fractions[nr_fractions++] = fraction(1, 1);
		for (int i = 2; i <= n; i++)
			for (int j = 1; j < i; j++)
				if (coprimes[i][j])
					fractions[nr_fractions++] = fraction(j, i);
		sort(fractions, fractions + nr_fractions);
		cout << fractions[k - 1].numerator_ << '/' << fractions[k - 1].denominator_ << endl;
	}
	return 0;
}

