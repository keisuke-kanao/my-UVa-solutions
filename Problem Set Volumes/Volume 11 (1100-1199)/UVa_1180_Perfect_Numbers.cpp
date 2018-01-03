
/*
	UVa 1180 - Perfect Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1180_Perfect_Numbers.cpp
*/

/*
6, 28, 496, 8128, 33550336, 8589869056, 137438691328, 2305843008139952128, 
2658455991569831744654692615953842176
*/

#include <set>
#include <cstdio>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

long long sum_of_divisors(long long n)
{
	int e = 0, i, j;
	long long s = 1, p = 1;
	for ( ; !(n & 1); n >>= 1) {
		e++;
		p *= 2;
	}
	if (e) {
		s *= p * 2 - 1;
		e = 0, p = 1;
	}
	for (i = 3, j = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= j; ) {
		if (!(n % i)) {
			e++;
			p *= i;
			n /= i;
		}
		else {
			if (e) {
				s *= (p * i - 1) / (i - 1);
				e = 0, p = 1;
			}
			i += 2;
		}
	}
	if (e)
		s *= (p * i - 1) / (i - 1);
	if (n > 1)
		s *= (n * n - 1) / (n - 1);
	return s;
}

int main()
{
	const long long pn_max = 1LL << 33;
	const int first_few_primes[] = {2, 3, 5, 7};
	set<int> primes(first_few_primes, first_few_primes + sizeof(first_few_primes) / sizeof(int));
	for (int n = 11; ; n += 2)
		if (is_prime(n)) {
			long long pn = static_cast<long long>(1 << (n - 1)) * ((1 << n) - 1);
			if (pn > pn_max)
				break;
			if (pn == sum_of_divisors(pn) - pn) {
				primes.insert(n);
#ifdef DEBUG
				printf("%d %lld\n", n, pn);
#endif
			}
		}
	int nr;
	scanf("%d", &nr);
	while (nr--) {
		int n;
		scanf("%d%*c", &n);
		puts((primes.find(n) != primes.end()) ? "Yes" : "No");
	}
	return 0;
}

