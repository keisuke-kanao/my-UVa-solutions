
/*
	UVa 11728 - Alternate Task

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11728_Alternate_Task.cpp
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int s_max = 1000;
int sums_of_factors[s_max + 1];
	// sums_of_factors[i] is the largetst number whose factors add up to i

int sum_of_factors(int n)
{
	int i, j, k, s = 1;
	if (n > 1)
		s += n;
	for (i = 2, k = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= k; i++)
		if (!(n % i)) {
			j = n / i;
			if (i <= j)
				s += i;
			if (i < j)
				s += j;
		}
	return s;
}

int main()
{
	int i, s;
	for (i = 1; i <= s_max; i++)
		sums_of_factors[i] = -1;
	for (int i = 1; i <= s_max; i++)
		if ((s = sum_of_factors(i)) <= s_max)
			sums_of_factors[s] = i;
	for (int cn = 1; ; cn++) {
		int s;
		cin >> s;
		if (!s)
			break;
		cout << "Case " << cn << ": " << sums_of_factors[s] << endl;
	}
	return 0;
}

