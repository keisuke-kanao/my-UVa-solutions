
/*
	UVa 725 - Division

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_725_Division.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int nr_digits = 5;
const int numerator_max = 98765;

void division(int n, int di, int used_digits[], int denominator_digits[], int* nr_pairs)
{
	if (di == nr_digits) {
		int denominator = 0;
		for (int i = 0; i < nr_digits; i++) {
			denominator *= 10;
			denominator += denominator_digits[i];
		}
		int numerator = denominator * n;
		int nd;
		for (nd = 0; numerator && nd < nr_digits; numerator /= 10, nd++) {
			int d = numerator % 10;
			if (used_digits[d])
				break;
			used_digits[d] = -1;
		}
		if (nd == nr_digits && !numerator) {
			(*nr_pairs)++;
			cout << setfill('0') << setw(nr_digits) << denominator * n << " / " <<
				setw(nr_digits) << denominator << " = " << n << endl;
		}
		for (int i = 0; i < nr_digits * 2; i++)
			if (used_digits[i] == -1)
				used_digits[i] = 0;
	}
	else {
		for (int i = 0; i < nr_digits * 2; i++)
			if (!used_digits[i]) {
				used_digits[i] = 1;
				denominator_digits[di] = i;
				division(n, di + 1, used_digits, denominator_digits, nr_pairs);
				used_digits[i] = 0;
			}
	}
}

int main()
{
	bool printed = false;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (printed)
			cout << endl;
		else
			printed = true;
		int used_digits[nr_digits * 2];
		for (int i = 0; i < nr_digits * 2; i++)
			used_digits[i] = 0;
		int nr_pairs = 0, denominator_digits[nr_digits];
		division(n, 0, used_digits, denominator_digits, &nr_pairs);
		if (!nr_pairs)
			cout << "There are no solutions for " << n << ".\n";
	}
	return 0;
}

