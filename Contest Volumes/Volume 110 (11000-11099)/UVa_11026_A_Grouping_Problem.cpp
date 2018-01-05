
/*
	UVa 11026 - A Grouping Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11026_A_Grouping_Problem.cpp
*/

/*
This problem is analogous to binomial theorem.
Here m=number of elements k=set elements
Lets consider val[m][0]=1 that means empty sets with elements
Here we need to find the sum of product of a k  element subset given n elements.
Define val[m][k] as the sum of product of the first m element k element  subsets.
val[m][k]= val[m-1][k]+val[m-1][k-1]*( Value of the mth element ).
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 1000;

long long elements[N_max + 1], sums[N_max + 1][N_max + 1];
	// sums[i][j] is the sum of product of j elements from the first i elements

int main()
{
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= N; j++)
				sums[i][j] = 0;
		for (int i = 1; i <= N; i++)
			scanf("%d", &elements[i]);
		for (int i = 0; i <= N; i++)
			sums[i][0] = 1;
		for (int i = 1; i <= N; i++)
			for (int j = 1, e = elements[i]; j <= i; j++) {
				sums[i][j] = (sums[i - 1][j] + sums[i - 1][j - 1] * e % M) % M;
#ifdef DEBUG
			for (int j = 1; j <= i; j++)
				printf("[%d][%d]:%lld%c", i, j, sums[i][j], ((j < i) ? ' ' : '\n'));
#endif
		}
		long long max_fitness = -1;
		for (int j = 1; j <= N; j++)
			max_fitness = max(max_fitness, sums[N][j]);
		printf("%lld\n", max_fitness);
	}
	return 0;
}

