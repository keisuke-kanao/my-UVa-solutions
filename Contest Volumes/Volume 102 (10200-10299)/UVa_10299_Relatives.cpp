
/*
	UVa 10299 - Relatives

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10299_Relatives.cpp

	This problem is similar to 10179 - Irreducable Basic Fractions.

	from Waterloo ACM Programming Contest June 1, 2002 Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/020601/data/)
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
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
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
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << ((n == 1) ? 0 : phi_function(n)) << endl;
	}
	return 0;
}

