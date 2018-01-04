
/*
	UVa 11538 - Chess Queen

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11538_Chess_Queen.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

/*
from Methods to Solve:
	http://www.comp.nus.edu.sg/~stevenha/programming/volC15.html#11538

This is a math related game problem....or somehow ad-hoc problem
Observe that there are two cases of attacking, so first consider the horizontal and vertical: there are m*(m-1)*n + n*(n-1)*m.

Then, consider the two kinds of diagonals: 
  the one with length n and k (2<=k<n)(assume that m>n). for the one with length n: (m-n+1)*n*(n-1). 

For k ones: there are k*(k-1), k are from 2 to n-1. sum those up. 
we have 1^2+2^2+.....+n^2 - (1+2+3+....+(n-1))....using math formula: n*(n-1)*(2*n-1)/6 - (n-1)*n/2. 
as it is double side of the square, so we have to times 2 for the length k diagonals. 

Besides, the diagonals are of two directions, we have to times 2 at the end [(m-n+1)*n*(n-1)+(n*(n-1)*(2*n-1)/6-(n-1)*n/2)*2]*2. 
So, in total the sum is 
  m*(m-1)*n + n*(n-1)*m + (n*(n-1)*(2*n-1)/6 - (n-1)*n/2) * 4 + 2*n*(n-1)*(m-n+1) 

in the program just simply sub in the value and get the answer. 
note the problem of overflow, use unsigned long long int to make sure there is no over flow.

This is a math problem. 
To calculate the number of ways to make the queens in attacking position, we can divide the  answer into three parts: 
 two queens in the same row, on the same column, or the same diagonal. 
All data must be unsigned long long, and the output must be %llu in C (%I64u was WA, canft understand).

Answer = m*(m-1)*n + n*(n-1)*m + (n*(n-1)*(2*n-1)/6 - (n-1)*n/2) * 4 + 2 * n*(n-1)*(m-n+1);


For a n * m checkerboard, horizontal and vertical consider n * (m-1) * m + (n-1) * m * n way, 
the diagonal direction, 2 (slope of 1 and -1 in both cases ) * 2 * (1 * (1-1) +2 * 1 +3 * 2 + ........ + s * (s-1) * 2) - 2 * (bs-1) * s * (s- 1) ways.
Where s is the smaller of n and m, b is greater; 

*/

int main()
{
	while (true) {
		long long M, N;
		cin >> M >> N;
		if (!M && !N)
			break;
		if (M < N)
			swap(M, N);
		long long nr_ways = (M - 1) * M * N + // horizontal
			(N - 1) * M * N + // vertical
			(N * (N - 1) * (2 * N - 1) / 6 - (N - 1) * N / 2) * 4 + 2 * N * (N - 1) * (M - N + 1); // diagonal
		cout << nr_ways << endl;
	}
	return 0;
}

/*
int main() // first version
{
	while (true) {
		long long M, N;
		cin >> M >> N;
		if (!M && !N)
			break;
		long long nr_ways = (M - 1) * M * N + // horizontal
			(N - 1) * M * N; // vertical
		// diagonal
		for (long long i = 1; i <= N; i++)
			for (long long j = 1; j <= M; j++)
				nr_ways += min(i - 1, M - j) + // upper right
					min(i - 1, j - 1) + // upper left
					min(N - i, M - j) + // lower right
					min(N - i, j - 1); // lower left
		cout << nr_ways << endl;
	}
	return 0;
}
*/

