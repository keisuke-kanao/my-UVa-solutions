
/*
	UVa 290 - Palindroms <---> smordnilaP

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_290_Palindroms_smordnilaP.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

char to_digit(char c)
{
	return (isdigit(c)) ? c - '0' : ((isupper(c)) ? c - 'A' + 10 : c - 'a' + 10);
}

bool is_palindrom(const int* pn, int length)
{
	for (int i = 0, j = length - 1; i < j; i++, j--)
		if (pn[i] != pn[j])
			return false;
	return true;
}

int main()
{
	string number;
	while (cin >> number) {
		transform(number.begin(), number.end(), number.begin(), to_digit);
		int nr_digits = static_cast<int>(number.length());
		int min_base = -1;
		for (int i = 0; i < nr_digits; i++)
			if (number[i] > min_base)
				min_base = number[i];
		if (!min_base)
			min_base++;
		int base = 15;
		for ( ; base > min_base; base--) {
			if (base < 15)
				cout << ' ';
			const int nr_steps_max = 1024;
			int nr_digits_max = static_cast<int>(nr_digits + nr_steps_max);
			int *pn = new int[nr_digits_max], *ps = new int[nr_digits_max];
			for (int i = nr_digits - 1; i >= 0; i--)
				pn[i] = number[i];
			int nd = nr_digits, ns = 0;
			while (!is_palindrom(pn, nd)) {
				int i, j, carry;
				for (i = 0, carry = 0; i < nd; i++) {
					ps[i] = pn[i] + pn[nd - i - 1] + carry;
					if (ps[i] >= base) {
						ps[i] -= base;
						carry = 1;
					}
					else
						carry = 0;
				}
				if (carry)
					ps[i++] = carry;
				nd = i;
				for (i = 0; i < nd; i++)
					pn[i] = ps[i];
#ifdef DEBUG
				for (i = nd - 1; i >= 0; i--)
					cout << ((pn[i] > 9) ? static_cast<char>(pn[i] - 10 + 'A') : static_cast<char>(pn[i] + '0'));
				cout << endl;
#endif
				ns++;
			}
			delete[] pn; delete[] ps;
			cout << ns;
		}
		for ( ; base >= 2; base--) {
			if (base < 15)
				cout << ' ';
			cout << '?';
		}
		cout << endl;
	}
	return 0;
}

