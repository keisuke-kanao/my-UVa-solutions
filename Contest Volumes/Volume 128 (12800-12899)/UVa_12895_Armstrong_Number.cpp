
/*
	UVa 12895 - Armstrong Number

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12895_Armstrong_Number.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		const int nr_digits_max = 10;
		char s[nr_digits_max + 1];
		scanf("%s", s);
		int N = atoi(s), nr_digits = strlen(s);
		int digits[nr_digits_max];
		long long pows[nr_digits_max];
		for (int i = 0; i < nr_digits; i++)
			pows[i] = digits[i] = s[i] - '0';
		for (int n = 2; n <= nr_digits; n++)
			for (int i = 0; i < nr_digits; i++)
				pows[i] *= digits[i];
		long long sum = 0;
		for (int i = 0; i < nr_digits; i++)
			sum += pows[i];
		puts((sum == N) ? "Armstrong" : "Not Armstrong");
	}
	return 0;
}

