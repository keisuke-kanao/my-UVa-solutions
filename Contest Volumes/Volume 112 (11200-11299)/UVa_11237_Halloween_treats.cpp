
/*
	UVa 11237 - Halloween treats

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11237_Halloween_treats.cpp
*/

/*
Hint: n >= c. 
Bigger hint: the solution is always possible. Think about partial sums of a[i]'s and the pigeonhole principle.

Sorry I m really a novice here, but i m asking about: what do u mean by partial sums of a[i]'s???
The sequence 0, a[0], a[0]+a[1], a[0]+a[1]+a[2], ...
*/

#include <cstdio>
#include <cstring>

const int n_max = 100000;
int pss[n_max + 1]; // pss[i] is ((sum of ai) mod n) for i > 0, or 0 for i == 0
int indices[n_max + 1]; // indices[j] is the previous indices of ai where pss[i] == j

int main()
{
	while (true) {
		int c, n;
		scanf("%d %d", &c, &n);
		if (!c)
			break;
		for (int i = 1, s = 0; i <= n; i++) {
			int ai;
			scanf("%d", &ai);
			pss[i] = s = (s + ai) % c;
#ifdef DEBUG
			printf("%d%c", pss[i], ((i < n) ? ' ' : '\n'));
#endif
		}
		memset(indices + 1, -1, sizeof(int) * n);
		int j;
		for (j = 1; j <= n; j++) {
			if (indices[pss[j]] != -1)
				break;
			indices[pss[j]] = j;
		}
		for (int i = indices[pss[j]] + 1; i <= j; i++)
			printf("%d%c", i, ((i < j) ? ' ' : '\n'));
	}
	return 0;
}

/*
Sample Input

4 5
1 2 3 7 5
3 6
7 11 2 5 13 17
0 0

Sample Output

3 5
2 3 4
*/

/*

4 5
1 2 3 7 5

                     1  2  3  7  5
                  0  1  3  6 13 18
mod 4             0	 1  3  2  1  2
                        2  3  7
                              7  5



3 6
7 11 2 5 13 17


                   7 11  2  5 13 17
                0  7 18 20 25 38 55
mod 3           0  1  0  2  1  2  1
                   7 11
                     11  2  5
                            5 13
                              13 17

*/

