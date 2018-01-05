
/*
	UVa 11105 - Semi-prime H-numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11105_Semi_prime_H_numbers.cpp
*/

#include <iostream>
using namespace std;

const int h_nr_max = 1000001;

int h_numbers[h_nr_max + 1];
	// h_numbers[i] is the number of product of H-numbers
int semi_prime_h_numbers[h_nr_max + 1];
	// semi_prime_h_numbers[i] is the number of semi-prime H-numbers up to i

int main()
{
	for (int i = 5; i <= h_nr_max; i += 4) {
		if (!h_numbers[i])
			h_numbers[i] = 1;
		for (int j = 5; j <= i && i * j <= h_nr_max; j += 4)
			h_numbers[i * j] = h_numbers[i] + h_numbers[j];
	}
#ifdef DEBUG
	int prime_h_numbers = 0;
#endif
	for (int i = 5; i <= h_nr_max; i += 4) {
		semi_prime_h_numbers[i] = semi_prime_h_numbers[i - 4];
		if (h_numbers[i] == 2)
			semi_prime_h_numbers[i]++;
#ifdef DEBUG
		else if (h_numbers[i] == 1)
			prime_h_numbers++;
#endif
	}
#ifdef DEBUG
	cout << prime_h_numbers << ' ' << semi_prime_h_numbers[h_nr_max] << endl;
#endif
	while (true) {
		int h;
		cin >> h;
		if (!h)
			break;
		cout << h << ' ' << semi_prime_h_numbers[h] << endl;
	}
	return 0;
}

