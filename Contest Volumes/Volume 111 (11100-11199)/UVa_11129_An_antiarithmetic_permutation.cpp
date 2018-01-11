
/*
	UVa 11129 - An antiarithmetic permutation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11129_An_antiarithmetic_permutation.cpp
*/

/*
From World of Seven - Methods to Solve - ACM UVa Online Judge
	(http://www.comp.nus.edu.sg/~stevenha/programming/acmoj.html)

11129 - An antiarithmetic permutation

This is an ad hoc problem. 
Notice that if the first half of an array are even numbers, the second half of an array are odd numbers, 
then no arithmetic progression containing both odd and even elements will be found 
because (even even odd) and (even odd odd) are impossible to be arithmetic progression. 
Then the problem becomes to find a permutation of all odd(even) elements smaller than n 
which contains no subsequence which is arithmetic progression. 
If we devide all elements of the odd(even) permutation by 2, we will get an antiarithmetic permutation, 
which is a subproblem. 
So this problem can be solved using divide and conquer. The total complexity should be O(n log n).
*/

#include <iostream>
using namespace std;

const int n_max = 10000;
int perm[n_max + 1];

void antiarithmetic_permutation(int n, int pi)
{
	if (n == 2) {
		perm[pi] = 0; perm[pi + 1] = 1;
	}
	else if (n == 3) {
		perm[pi] = 0; perm[pi + 1] = 2; perm[pi + 2] = 1;
	}
	else {
		int nr_even = (n + 1) / 2, nr_odd = n / 2;
		antiarithmetic_permutation(nr_even, pi);
		antiarithmetic_permutation(nr_odd, pi + nr_even);
		for ( ; nr_even; pi++, nr_even--)
			perm[pi] <<= 1; // perm[pi] = perm[pi] * 2
		for ( ; nr_odd; pi++, nr_odd--) {
			perm[pi] <<= 1; perm[pi]++; // perm[pi] = perm[pi] * 2 + 1
		}
	}
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		antiarithmetic_permutation(n, 0);
		cout << n << ':';
		for (int i = 0; i < n; i++)
			cout << ' ' << perm[i];
		cout << endl;
	}
	return 0;
}

