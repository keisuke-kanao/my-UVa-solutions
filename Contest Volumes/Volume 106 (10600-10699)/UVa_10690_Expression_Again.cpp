
/*
	UVa 10690 - Expression Again

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10690_Expression_Again.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 50, M_max = 50, integer_min = -50, integer_max = 50;
const int first_term_min = (N_max + M_max) * integer_min, first_term_max = (N_max + M_max) * integer_max;
int integers[N_max + M_max + 1];

bool expressions[2][N_max + 1][first_term_max - first_term_min + 1];
	// expressions[i][j][k] is true for the product of up to (i % 2)-th integers 
	// with j integers for the first term and sum of j integers (the first term) being k

#ifdef DEBUG
void print_expressions(int i,int j, int k_min, int k_max, const bool exps[])
{
	printf("[%d][%d]:", i, j);
	for (int k = k_min; k <= k_max; k++)
		if (exps[k])
			printf(" %d", k + first_term_min);
	putchar('\n');
}
#endif

int main()
{
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		int s = 0;
		for (int i = 1; i <= N + M; i++) {
			scanf("%d", &integers[i]);
			s += integers[i];
		}
		memset(&expressions[1], 0, sizeof(expressions[0]));
		int pj_min = 0, pj_max = 1, integer = integers[1];
		int pk_min = 0 - first_term_min, pk_max = integer - first_term_min;
		expressions[1][pj_min][pk_min] = expressions[1][pj_max][pk_max] = true;
#ifdef DEBUG
		print_expressions(1, pj_min, pk_min, pk_min, expressions[1][pj_min]);
		print_expressions(1, pj_max, pk_max, pk_max, expressions[1][pj_max]);
#endif
		if (pk_min > pk_max)
			swap(pk_min, pk_max);
		for (int i = 2; i <= N + M; i++) {
			int pi = (i - 1) %2, ci = i % 2;
			int cj_min = max(0, i - M), cj_max = min(i, N);
			int ck_min = pk_min, ck_max = pk_max;
			memset(&expressions[ci], 0, sizeof(expressions[0]));
			integer = integers[i];
			for (int j = pj_min; j <= pj_max; j++) {
				for (int k = pk_min; k <= pk_max; k++)
					if (expressions[pi][j][k]) {
						expressions[ci][j][k] = true;
						if (j < cj_max) {
							expressions[ci][j + 1][k + integer] = true;
							ck_min = min(ck_min, k + integer), ck_max = max(ck_max, k + integer);
						}
					}
			}
			pj_min = cj_min, pj_max = cj_max;
			pk_min = ck_min, pk_max = ck_max;
#ifdef DEBUG
			for (int j = pj_min; j <= pj_max; j++)
				print_expressions(i, j, pk_min, pk_max, expressions[ci][j]);
#endif
		}
		int ci = (N + M) % 2, p_min = (N_max + M_max) * integer_max + 1, p_max = (N_max + M_max) * integer_min - 1;
		for (int k = pk_min; k <= pk_max; k++)
			if (expressions[ci][pj_min][k]) {
				int p = k + first_term_min;
				p *= s - p;
				p_min = min(p_min, p), p_max = max(p_max, p);
			}
		printf("%d %d\n", p_max, p_min);
	}
	return 0;
}

