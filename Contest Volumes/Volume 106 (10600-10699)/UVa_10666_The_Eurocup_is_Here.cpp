
/*
	UVa 10666 - The Eurocup is Here!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10666_The_Eurocup_is_Here.cpp
*/

/*
10666 - The Eurocup is Here!

I'm sad England didn't win the Euro cup, but anyway let's congratulate the Greek's for eventually winning the cup...

Let's move on to the problem itself, for optimistic ranking, 
count the number of ones in binary representation of X then add 1. Why? try it yourself first.
for pessimistic ranking, count the number of zeros at the least significant digit before encounter one 
(which is total nodes - number of children in topological tree).

It is hard to explain the logic why binary representation helps... I just unintentionally figure out this pattern...
*/

#include <cstdio>

int main()
{
	int M, N, X;
	scanf("%d", &M);
	while (M--) {
		scanf("%d %d", &N, &X);
		int nr_ones = 0, nr_zeros = 0;
		for ( ; X; X >>= 1) {
			if (X & 1)
				nr_ones++;
			else if (!nr_ones)
				nr_zeros++;
		}
		unsigned int r = 1U << N;
		printf("%d %u\n", nr_ones + 1,
			((nr_ones || nr_zeros) ? r - ((1U << nr_zeros) - 1) : 1));
	}
	return 0;
}

/*
Sample Input

4
3 1
4 10
2 2
4 15

Sample Output

2 8
3 15
2 3
5 16


3 1
	1
		number of ones: 1		optimistic ranking: 1 + 1 = 2
		number of zeros: 0 		pessimistic ranking: 2^3 - 0b = 8

4 10
	1010
		number of ones: 2		optimistic ranking: 2 + 1 = 3
		number of zeros: 1 		pessimistic ranking: 2^4 - 1b = 15

2 2
	10
		number of ones: 1		optimistic ranking: 1 + 1 = 2
		number of zeros: 1		pessimistic ranking: 2^2 - 1b = 3

4 15
	1111
		number of ones: 4		optimistic ranking: 4 + 1 = 5
		number of zeros: 0		pessimistic ranking: 2^4 - 0b = 16

4 4
	0100
		number of ones: 1		optimistic ranking: 4 + 1 = 2
		number of zeros: 2		pessimistic ranking: 2^4 - 11b = 13

4 8
	1000
		number of ones: 1		optimistic ranking: 4 + 1 = 2
		number of zeros: 3		pessimistic ranking: 2^4 - 111b = 9

*/


