
/*
	UVa 10179 - Irreducable Basic Fractions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10179_Irreducable_Basic_Fractions.cpp
*/

/*
	Utilize Euler's totient or phi function, φ(n). φ(n) is an arithmetic function 
	that counts the number of positive integers less than or equal to n that are relatively prime to n.
	For more information, see Euler's totient function - Wikipedia, the free encyclopedia.
		(http://en.wikipedia.org/wiki/Euler's_totient_function)
*/

#include <iostream>
#include <cmath>
using namespace std;

long long phi_function(int n)
{
	long long phi = n;
	bool a_new_prime = true;
	for ( ; !(n & 1); n >>= 1)
		if (a_new_prime) {
			a_new_prime = false;
			phi >>= 1; // phi /= 2
		}
	a_new_prime = true;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			if (a_new_prime) {
				a_new_prime = false;
				phi *= i - 1; phi /= i;
			}
			n /= i;
		}
		else {
			i += 2;
			a_new_prime = true;
		}
	}
	if (n > 1) {
		phi *= n - 1; phi /= n;
	}
	return phi;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << phi_function(n) << endl;
	}
	return 0;
}

