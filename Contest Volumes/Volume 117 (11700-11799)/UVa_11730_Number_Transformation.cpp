
/*
	UVa 11730 - Number Transformation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11730_Number_Transformation.cpp
*/

#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int S_max = 100, T_max = 1000;
int min_nrs[T_max + 1]; // min_nrs[i] is the minimum number of transformations found so far

size_t get_prime_factors(int n, vector<int>& factors)
{
	bool first = true;
	for ( ; !(n & 1); n >>= 1)
		if (first) {
			first = false;
			factors.push_back(2);
		}
	first = true;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; ) {
		if (!(n % i)) {
			if (first) {
				first = false;
				factors.push_back(i);
			}
			n /= i;
		}
		else {
			first = true;
			i += 2;
		}
	}
	if (n > 1 && !factors.empty())
		factors.push_back(n);
	return static_cast<int>(factors.size());
}

void number_transformation(int S, int T, int nr)
{
	if (S == T) {
		if (min_nrs[T] == -1 || nr < min_nrs[T])
			min_nrs[T] = nr;
	}
	else if (min_nrs[S] == -1 || nr < min_nrs[S]) {
		min_nrs[S] = nr;
		vector<int> factors;
		int fn = get_prime_factors(S, factors);
		for (int i = fn - 1; i >= 0; i--)
			if (S + factors[i] <= T)
				number_transformation(S + factors[i], T, nr + 1);
	}
}

int main()
{
	for (int cn = 1; ; cn++) {
		int S, T;
		scanf("%d %d", &S, &T);
		if (!S && !T)
			break;
		memset(min_nrs, -1, sizeof(min_nrs));
		number_transformation(S, T, 0);
		printf("Case %d: %d\n", cn, min_nrs[T]);
	}
	return 0;
}

