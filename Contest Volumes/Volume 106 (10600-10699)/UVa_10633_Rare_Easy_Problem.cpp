
/*
	UVa 10633 - Rare Easy Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10633_Rare_Easy_Problem.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	while (true) {
		const int nr_digits_max = 19;
		char s[nr_digits_max + 1];
		scanf("%s", s);
		if (!atoi(s))
			break;
		int length = strlen(s);
		for (int i = 0; i < length; i++)
			s[i] -= '0';
		char t[nr_digits_max + 1]; // t[i] is the i-th digit of N, except for the last one
		bool printed = false;
		for (int last_digit = 9; last_digit >= 0; last_digit--) {
			int carry = 0;
			t[length - 1] = last_digit - s[length - 1];
			if (t[length - 1] < 0) {
				t[length - 1] += 10;
				carry = 1;
			}
			for (int i = length - 2; i >= 0; i--) {
				t[i] = t[i + 1] - s[i] - carry;
				carry = 0;
				if (t[i] < 0) {
					t[i] += 10;
					carry = 1;
				}
			}
			if (t[0] == carry) {
				if (printed)
					putchar(' ');
				else
					printed = true;
				for (int i = (carry) ? 0 : 1; i < length; i++)
					putchar(t[i] + '0');
				putchar(last_digit + '0');
			}
		}
		putchar('\n');
	}
	return 0;
}

