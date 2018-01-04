
/*
	UVa 11743 - Credit Check

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11743_Credit_Check.cpp
*/

#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		const int nr_digits = 16;
		char digits[nr_digits + 1];
		scanf("%s", &digits[0]);
		scanf("%s", &digits[4]);
		scanf("%s", &digits[8]);
		scanf("%s", &digits[12]);
		int sum = 0;
		for (int i = 0; i < nr_digits; i++) {
			int v = digits[i] - '0';
			if (!(i & 1)) {
				v <<= 1;
				v = (v / 10) + (v % 10);
			}
			sum += v;
		}
#ifdef DEBUG
		printf("sum = %d\n", sum);
#endif
		if (sum % 10)
			printf("Invalid\n");
		else
			printf("Valid\n");
	}
	return 0;
}

