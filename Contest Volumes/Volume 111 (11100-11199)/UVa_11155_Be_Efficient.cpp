
/*
	UVa 11155 - Be Efficient

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11155_Be_Efficient.cpp
*/

/*
First, generate the sequence x[i] like the problem description
Then, generate the sequence s[i],
where s[i] = x[0] + x[1] + ... x[i]
While computing, you can set s[i] = (s[i-1] + x[i]) % m; , because we only deal with the remainder modulo m

For each 0<=r<m, count the number of s[i], so that s[i] % m = r
That means, you have to iterate through s, and set
mod[s[i] % m]++;

Moreover, set mod[0]++;
because mod[0] is kind of special because mod[0] itself can be the sequence we're looking for..

Then, the result is sum ( mod[i]*(mod[i] - 1) div 2, i=0..m-1)
That's simply because each subsequence can be represented as s[i] - s[j] for some i,j.
*/

#include <cstdio>
#include <cstring>

const int N_max = 10000, M_max =  10000;
int sums[N_max]; // sums[i] = (X0 + X1 + ... + Xi) % M
int remainders[M_max]; // reminders[i] is the number of sums[j] such that sums[j] = i
/*
	For each pair of sums[j] and sums[k] such that sums[j] = sums[k], (sums[j] - sums[k]) % M = 0.
	Also, if sums[j] = 0, sums[j] % M = 0.
*/

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int A, B, C, M, N;
		scanf("%d %d %d %d %d", &A, &B, &C, &M, &N);
		int x = A % M;
		sums[0] = x;
		for (int i = 1; i < N; i++) {
			x = (x * B + C) % M + 1;
			sums[i] = (sums[i - 1] + x) % M;
		}
		memset(remainders, 0, sizeof(int) * M);
		for (int i = 0; i < N; i++)
			remainders[sums[i]]++;
		long long result = remainders[0];
		for (int i = 0; i < M; i++) {
#ifdef DEBUG
			if (remainders[i] > 1)
				printf("[%d]:%d%c", i, remainders[i], ((i < M - 1) ? ' ' : '\n'));
#endif
			result += remainders[i] * (remainders[i] - 1) / 2;
				// number of ways to pick up two pair of sums out of remainders[i], in other worods, C(remainders[i], 2)
		}
		printf("Case %d: %lld\n", t, result);
	}
	return 0;
}

