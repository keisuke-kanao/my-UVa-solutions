
/*
	UVa 11480 - Jimmy's Balls

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11480_Jimmys_Balls.cpp
*/

/*
From http://www.comp.nus.edu.sg/~stevenha/programming/volC14.html#11480_-_Jimmys_Balls:

Simple mathematics:
We are going to solve an system:
(1) 0 < r < b < g
(2) r + b + g = n

Suppose r is constant, we have:
(1) --> 0 < (b - r) < (g - r)
(2) --> (b - r) + (g - r) = n - 3*r;

So (b - r) & (g - r) is the solution of the following system:
(3) 0 < x < y
(4) x + y < n - 3*r
The number of solutions of this system is (n - 3*r - 1)/ 2

In short, just try all values of r. For each value r, we add (n - 3*r - 1)/2 to the result.
*/

#include <cstdio>

int main()
{
	for (int cn = 1; ; cn++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		long long nr_combinations = 0;
		for (int i = 1; ; i++) {
			int j = (n - 3 * i - 1) / 2;
			if (j < 1)
				break;
			nr_combinations += j;
		}
		printf("Case %d: %lld\n", cn, nr_combinations);
	}
	return 0;
}

