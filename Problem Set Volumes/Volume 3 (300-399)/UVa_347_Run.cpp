
/*
	UVa 347 - Run

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_347_Run.cpp

	from ACM North Central Regionals 1996 Problem C
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1996/index.html)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

bool is_runaround_number(int n)
{
	bool bdigits[10]; // bdigits[i] is true if digit i appears in n
	memset(bdigits, 0, sizeof(bdigits));
	const int nr_digits_max = 7;
	int digits[nr_digits_max];
	int* q = &digits[nr_digits_max - 1];
	int* p = q++;
	while (true) {
		*p = n % 10;
		if (!*p || bdigits[*p])
			return false;
		bdigits[*p] = true;
		n /= 10;
		if (!n)
			break;
		p--;
	}
	int length = q - p;
	int i = length, j;
	int* r = p;
	while (true) {
		j = *r;
		*r = 0;
		r = p + ((r - p) + j) % length;
		if (--i) {
			if (!*r)
				return false;
		}
		else
			break;
	}
	return (r == p && !*r) ? true : false;
}

int main()
{
	vector<int> runaround_numbers;
	for (int n = 12; n < 10000000; n++)
		if (is_runaround_number(n))
			runaround_numbers.push_back(n);
#ifdef DEBUG
	cout << runaround_numbers.size() << endl;
#endif
	for (int cn = 1; ; cn++) {
		int r;
		cin >> r;
		if (!r)
			break;
		cout << "Case " << cn <<": " << *lower_bound(runaround_numbers.begin(), runaround_numbers.end(), r) << endl;
	}
	return 0;
}

