
/*
	UVa 11282 - Mixing Invitations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11282_Mixing_Invitations.cpp
*/

#include <cstdio>

const int N_max = 20;
long long derangements[N_max + 1]; // derangements[i] is the number of derangements with i numbers
	// For more information, see https://en.wikipedia.org/wiki/Derangement.
int combinations[N_max + 1][N_max + 1];

void calculate_combinations(int n)
{
	for (int i = 0; i <= n; i++)
		combinations[i][0] = 1;
	for (int i = 0; i <= n; i++)
		combinations[i][i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			combinations[i][j] = combinations[i - 1][j - 1] + combinations[i - 1][j];
}

int main()
{
	derangements[0] = 1, derangements[1] = 0;
	for (int i = 2; i <= N_max; i++)
		derangements[i] = (i - 1) * (derangements[i - 2] + derangements[i - 1]);
	calculate_combinations(N_max);
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		long long nr_ways = 0;
		for (int i = 0; i <= M; i++)
			nr_ways += combinations[N][i] * derangements[N - i];
		printf("%lld\n", nr_ways);
	}
	return 0;
}

/*
Sample Input

3 2
4 1
4 4

Sample Output

5
17
24

*/

/*

3 2

3! - C(3, 3) = 6 - 1 = 5
		correct envelops
1 2 3	3	x
1 3 2	1
2 1 3	1
2 3 1	0
3 1 2	0
3 2 1	1


4 1

4! - C(4, 4) * (1 - 1)! - C(4, 2) * (2 - 1)! = 24 - 1 - 6 = 17

4 0
4! - C(4, 4) * (1 - 1)! - C(4, 2) * (2 - 1)! - C(4, 1) * (3 - 1)! = 24 - 1 - 6 - 8 = 9

4 2
4! - C(4, 4) * (1 - 1)! = 23
4 3

			correct envelops
1 2 3 4		4	x
1 2 4 3		2	x
1 3 2 4		2	x
1 3 4 2		1
1 4 2 3		1
1 4 3 2		2	x
2 1 3 4		2	x
2 1 4 3		0
2 3 1 4		1
2 3 4 1		0
2 4 1 3		0
2 4 3 1		1
3 1 2 4		1
3 1 4 2		0
3 2 1 4		2	x
3 2 4 1		1
3 4 1 2		0
3 4 2 1		0
4 1 2 3		0
4 1 3 2		1
4 2 1 3		1
4 2 3 1		2	x
4 3 1 2		0
4 3 2 1		0


*/

