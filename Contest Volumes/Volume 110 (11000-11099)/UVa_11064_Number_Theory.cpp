
/*
	UVa 11064 - Number Theory

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11064_Number_Theory.cpp
*/

/*
	Utilize Euler's totient or phi function, É”(n). É”(n) is an arithmetic function 
	that counts the number of positive integers less than or equal to n that are relatively prime to n.
	For more information, see Euler's totient function - Wikipedia, the free encyclopedia.
		(http://en.wikipedia.org/wiki/Euler's_totient_function)
*/

#include <iostream>
#include <cmath>
using namespace std;

int number_of_divisors(int n)
{
	if (n < 3)
		return n;
	int nr = 2; // 1 and n
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; i++)
		if (!(n % i)) {
			nr++;
			int j = n / i;
			if (j > i)
				nr++;
		}
	return nr;
}

int phi_function(int n)
{
	int phi = n;
	bool a_new_prime = true;
	for ( ; !(n & 1); n >>= 1)
		if (a_new_prime) {
			a_new_prime = false;
			phi >>= 1; // phi /= 2
		}
	a_new_prime = true;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; ) {
		if (!(n % i)) {
			if (a_new_prime) {
				a_new_prime = false;
				phi /= i; phi *= i - 1;
			}
			n /= i;
		}
		else {
			i += 2;
			a_new_prime = true;
		}
	}
	if (n > 1) {
		phi /= n; phi *= n - 1;
	}
	return phi;
}

int main()
{
	int n;
	while (cin >> n) {
		cout << n - (number_of_divisors(n) + phi_function(n)) + 1 << endl;
	}
	return 0;
}

