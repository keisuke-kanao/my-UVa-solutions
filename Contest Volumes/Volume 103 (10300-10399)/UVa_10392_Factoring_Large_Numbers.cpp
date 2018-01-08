
/*
	UVa 10392 - Factoring Large Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 -DONLINE_JUDGE UVa_10392_Factoring_Large_Numbers.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#ifdef ONLINE_JUDGE

const int max_prime = 1000000;

bool is_prime(int n)
{
/*
	if (n < 2)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
*/
		for (int i = 3; i <= sqrt(static_cast<double>(n)) + 1; i += 2)
			if (!(n % i))
				return false;
/*
	}
*/
	return true;
}

size_t generate_primes(vector<int>& primes)
{
	for (int i = 3; i <= max_prime; i += 2)
		if (is_prime(i))
			primes.push_back(i);
	return primes.size();
}

void print_factors(long long n, const vector<int>& primes)
{
	const char* spaces = "    ";
	for ( ; !(n & 1); n >>= 1)
		cout << spaces << 2 << endl;
	size_t i = 0;
	while (n > 1 && i < primes.size()) {
		if (!(n % primes[i])) {
			cout << spaces << primes[i] << endl;
			n /= primes[i];
		}
		else
			i++;
	}
	if (n > 1)
		cout << spaces << n << endl;
}

int main()
{
	vector<int> primes;
	generate_primes(primes);
#ifdef DEBUG
	cout << "number of primes = " << primes.size() << endl;
#endif
	while (true) {
		long long n;
		cin >> n;
		if (n < 0)
			break;
		if (n > 1)
			print_factors(n, primes);
		cout << endl;
	}
	return 0;
}

#else // !ONLINE_JUDGE

void print_factors(long long n)
{
	const char* spaces = "    ";
	for ( ; !(n & 1); n >>= 1)
		cout << spaces << 2 << endl;
	long long i = 3, e = static_cast<long long>(sqrt(static_cast<double>(n)) + 1);
	while (i <= e) {
		if (!(n % i)) {
			cout << spaces << i << endl;
			n /= i;
			e = static_cast<long long>(sqrt(static_cast<double>(n)) + 1);
		}
		else
			i += 2;
	}
	if (n > 1)
		cout << spaces << n << endl;
}

int main()
{
	while (true) {
		long long n;
		cin >> n;
		if (n < 0)
			break;
		print_factors(n);
		cout << endl;
	}
	return 0;
}

#endif // ONLINE_JUDGE

