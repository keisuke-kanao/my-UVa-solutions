
/*
	UVa 12406 - Help Dexter

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12406_Help_Dexter.cpp
*/

#include <cstdio>
#include <cstdlib>

const int p_max = 17, q_max = 17;
char digits[p_max + 1];

bool ascending_number(int p, int pi, int divisor, long long& smallest)
{
	if (pi == p) {
		digits[p] = '\0';
		long long n = atoll(digits);
		if (!(n % divisor)) {
			smallest = n;
			return true;
		}
		else
			return false;
	}
	else {
		digits[pi] = '1';
		if (ascending_number(p, pi + 1, divisor, smallest))
			return true;
		digits[pi] = '2';
		if (ascending_number(p, pi + 1, divisor, smallest))
			return true;
		return false;
	}
}

bool descending_number(int p, int pi, int divisor, long long& largest)
{
	if (pi < 0) {
		digits[p] = '\0';
		long long n = atoll(digits);
		if (!(n % divisor)) {
			largest = n;
			return true;
		}
		else
			return false;
	}
	else {
		digits[pi] = '2';
		if (descending_number(p, pi - 1, divisor, largest))
			return true;
		digits[pi] = '1';
		if (descending_number(p, pi - 1, divisor, largest))
			return true;
		return false;
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int p, q;
		scanf("%d %d", &p, &q);
		int divisor = 1 << q;
		long long smallest = 0, largest = 0;
		ascending_number(p, 0, divisor, smallest);
		descending_number(p, p - 1, divisor, largest);
		printf("Case %d: ", t);
		if (smallest > 0) {
			if (smallest != largest)
				printf("%lld %lld\n", smallest, largest);
			else
				printf("%lld\n", smallest);
		}
		else
			puts("impossible");
	}
	return 0;
}

/*
Sample Input

3
2 2
2 1
2 3

Sample Output

Case 1: 12
Case 2: 12 22
Case 3: impossible

*/

