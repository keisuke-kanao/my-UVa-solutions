
/*
	7.6.2 Carmichael Numbers
	PC/UVa IDs: 110702/10006, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10006_Carmichael_Numbers.cpp
*/

/*
Carmichael number From Wikipedia, the free encyclopedia (http://en.wikipedia.org/wiki/Carmichael_number)
	In number theory, a Carmichael number is a composite positive integer n which satisfies the congruence
		pow(b, n - 1) mod n = 1
	for all integers b which are relatively prime to n.
*/

#include <iostream>
#include <cmath>
using namespace std;

bool is_prime_number(int n)
{
	int max_dividend = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
	for (int divisor = 2; divisor <= max_dividend; divisor++)
		if (!(n % divisor))
			return false;
	return true;
}

/*
	modular exponentiation
*/
int mod_power(long long base, int exponent, long long modulus)
{
#if 0
/*
	The below is from "Introduction to Algorithms Second Edtion", page 879.
*/
	if (!exponent)
		return base % modulus;
	int msb = -1;
	for (int i = 0; i < sizeof(int) * 8; i++)
		if (exponent & (1 << i))
			msb = i;
	long long result = 1;
	for ( ; msb >= 0; msb--) {
		result = (result * result) % modulus;
		if (exponent & (1 << msb))
			result = (result * base) % modulus;
	}
	return static_cast<int>(result);
#else
/*
	The below is from "Modular exponentiation From Wikipedia, the free encyclopedia"
	(http://en.wikipedia.org/wiki/Modular_exponentiation).
*/
	long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            // multiply in this bit's contribution while using modulus to keep result small
            result = (result * base) % modulus;
        }
        // move to the next bit of the exponent, square (and mod) the base accordingly
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return static_cast<int>(result);
#endif
}

int gcd(int x, int y)
{
	if (!y)
		return x;
	else
		return gcd(y, x % y);
}

bool is_carmichael_number(int n)
{
	if (is_prime_number(n)) {
#ifdef DEBUG
		cout << n << "is a prime number.\n";
#endif
		return false;
	}
	for (int a = 2; a < n; a++) {
		int _gcd = gcd(n, a);
		if (_gcd != 1) // not a relatively prime
			continue;
		int _mod_power = mod_power(a, n - 1, n);
		if (_mod_power != 1) {
/*
			cout << "gcd(" << n << ", " << a << ") = " << _gcd << endl;
			cout << "mod_power(" << a << ", " << n - 1 << ", " << n << ") = " << _mod_power << endl;
*/
			return false;
		}
	}
	return true;
}

int main(int /* argc */, char** /* argv */)
{
	int n;
	while (cin >> n) {
		if (!n)
			break;
		if (is_carmichael_number(n))
			cout << "The number " << n << " is a Carmichael number.\n";
		else
			cout << n  << " is normal.\n";

	}
	return 0;
}

