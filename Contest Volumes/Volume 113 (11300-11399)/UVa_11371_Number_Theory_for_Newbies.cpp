
/*
	UVa 11371 - Number Theory for Newbies

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11371_Number_Theory_for_Newbies.cpp
*/

#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_digits_max = 10;

long long atoll(const char * s)
{
	long long ll = 0;
	for ( ; *s; s++) {
		ll *= 10;
		ll += *s - '0';
	}
	return ll;
}

int main()
{
	char digits[nr_digits_max + 1];
	while (scanf("%s", digits) != EOF) {
		int length = strlen(digits);
		sort(digits, digits + length, greater<char>());
		long long a = atoll(digits);
		sort(digits, digits + length);
		// the first digit must not be '0'
		int i = 0;
		while (digits[i] == '0')
			i++;
		swap(digits[0], digits[i]);
		long long b = atoll(digits);
		printf("%lld - %lld = %lld = 9 * %d\n", a, b, a - b, (a - b) / 9);
	}
	return 0;
}

