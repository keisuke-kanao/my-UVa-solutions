
/*
	UVa 12060 - All Integer Average

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12060_All_Integer_Average.cpp
*/

#include <cstdio>
#include <cmath>

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int nr_digits(unsigned int n)
{
	return (n) ? static_cast<int>(log10(static_cast<double>(n)) + 1.0) : 0;
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int s = 0;
		for (int i = 0; i < n; i++) {
			int j;
			scanf("%d", &j);
			s += j;
		}
		int sign = 0;
		if (s < 0) {
			sign = -1;
			s = -s;
		}
		int a = s / n, b = n, c = s % n;
		int g = gcd(b, c);
		b /= g; c /= g;
		int p = 0;
		if (sign < 0)
			p += 2;
		p += nr_digits(a);
		int nb = nr_digits(b), nc = nr_digits(c);
		printf("Case %d:\n", case_nr);
		if (c) {
			for (int i = 0; i < p + nb - nc; i++)
				putchar(' ');
			printf("%d\n", c);
		}
		if (sign < 0)
			printf("- ");
		if (a)
			printf("%d", a);
		else if (!c)
			putchar('0');
		if (c)
			for (int i = 0; i < nb; i++)
				putchar('-');
		putchar('\n');
		if (c) {
			for (int i = 0; i < p; i++)
				putchar(' ');
			printf("%d\n", b);
		}
	}
	return 0;
}

/*
Sample Input 

3 1 2 3
3 -1 -2 -3
3 1 2 4
4 2 4 6 10
3 -1 -2 -4
10 1 1 1 1 1 1 1 1 1 4
10 1 -1 1 -1 1 -1 -1 1 1 1
10 1 -1 1 -1 1 -1 -1 1 1 -3
0

Sample Output 

Case 1:
2
Case 2:
- 2
Case 3:
 1
2-
 3
Case 4:
 1
5-
 2
Case 5:
   1
- 2-
   3
Case 6:
  3
1--
 10
Case 7:
1
-
5
Case 8:
  1
- -
  5

*/
