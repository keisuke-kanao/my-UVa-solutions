
/*
	UVa 10820 - Send a Table

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10820_Send_a_Table.cpp
*/

/*
	The number of integers coprime to a positive integer n, between 1 and n, 
	is given by Euler's totient function (or Euler's phi function).
	See Euler's totient function - Wikipedia, the free encyclopedia
		(http://en.wikipedia.org/wiki/Euler%27s_totient_function)
*/

#include <iostream>
using namespace std;
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 50000;
int nr_coprime_pairs[n_max + 1]; // nr_coprime_pairs[i] is the number of coprime pairs from 1 to i

int phi_function(int n)
{
	int phi = n;
	if (n & 1)
		;
	else {
		phi >>= 1;
		n >>= 1;
		for (; !(n & 1); n >>= 1)
			;
	}
	int prime = 0;
	for (int i = 3; i * i <= n; ) {
		if (n % i) {
			prime = 0;
			i += 2;
		}
		else {
			if (!prime) {
				prime = i;
				phi /= i;
				phi *= i - 1;
			}
			n /= i;
		}
	}
	if (n > 1 && n != prime) {
		phi /= n;
		phi *= n - 1;
	}
	return phi;
}

void generate_nr_coprime_pairs()
{
	nr_coprime_pairs[0] = nr_coprime_pairs[1] = 0;
	int nr_pairs = 0;
	for (int i = 2; i <= n_max; i++) {
		nr_pairs += phi_function(i);
		nr_coprime_pairs[i] = nr_pairs;
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	generate_nr_coprime_pairs();
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int nr_pairs = 1;
		if (n > 1)
			nr_pairs += nr_coprime_pairs[n] * 2;
		cout << nr_pairs << endl;
	}
	return 0;
}

