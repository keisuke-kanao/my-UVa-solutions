
/*
	UVa 382 - Perfection

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_382_Perfection.cpp

	from 1996 ACM Mid-Atlantic Programming Contest Problems Problem 6
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidAtl/1996/index.html)
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

const int n_max = 10000;
bool factors[n_max];

int sum_of_factors(int n)
{
	if (n < 3)
		return n - 1;
	memset(factors, 0, sizeof(factors));
	int sum = 1;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n)) + 1.0); i <= e; i++)
		if (!(n % i)) {
			if (!factors[i]) {
				factors[i] = true;
				sum += i;
			}
			int j = n / i;
			if (!factors[j]) {
				factors[j] = true;
				sum += j;
			}
		}
	return sum;
}

int main()
{
	cout << "PERFECTION OUTPUT\n";
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << setfill(' ') << setw(5) << n << "  ";
		int sum = sum_of_factors(n);
		if (sum == n)
			cout << "PERFECT\n";
		else if (sum < n)
			cout << "DEFICIENT\n";
		else
			cout << "ABUNDANT\n";
	}
	cout << "END OF OUTPUT\n";
	return 0;
}

