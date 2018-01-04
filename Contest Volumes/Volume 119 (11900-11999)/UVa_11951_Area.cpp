
/*
	UVa 11951 - Area

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11951_Area.cpp

	Although this solution is an accepted solution. its execution time was 0.979 sec.
	I might be virdicted as TLE if it were submitted again.
*/

#include <cstdio>

const int N_max = 100, M_max = 100;

int sp[N_max][M_max]; // sp[x][y] is the sum of p[i][j] for 0 <= i <= x and 0 <= j <= y

int sum(int xt, int yl, int xb, int yr)
{
	if (xt && yl)
		return sp[xb][yr] - sp[xt - 1][yr] - sp[xb][yl - 1] + sp[xt - 1][yl - 1];
	else if (xt)
		return sp[xb][yr] - sp[xt - 1][yr];
	else if (yl)
		return sp[xb][yr] - sp[xb][yl - 1];
	else
		return sp[xb][yr];
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++)
			for (int j = 0, s = 0; j < M; j++) {
				int p;
				scanf("%d", &p);
				s += p;
				sp[i][j] = s;
				if (i)
					sp[i][j] += sp[i - 1][j];
			}
		int S = 0, P = 0;
		for (int xt = 0; xt < N; xt++)
			for (int yl = 0; yl < M; yl++) 
				for (int xb = xt; xb < N; xb++)
					for (int yr = yl; yr < M; yr++) {
						int cost = sum(xt, yl, xb, yr);
						if (cost <= K) {
							int area = (xb - xt + 1) * (yr - yl + 1);
#ifdef DEBUG
							printf("%d, %d - %d, %d: %d, %d\n", xt, yl, xb, yr, area, cost);
#endif
							if (area > S || area == S && P > cost) {
								S = area, P = cost;
							}
						}
						else
							break;
					}
		printf("Case #%d: %d %d\n", t, S, P);
	}
	return 0;
}

/*
An ordinal solution is like below:

int T, N, M, K;
int A[150][150];
 
int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; t++) {
        scanf("%d %d %d", &N, &M, &K);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                scanf("%d", &A[i][j]);
                if(i > 0) A[i][j] += A[i - 1][j];
            }
        }
 
        int best_cost = 0;
        int best_area = 0;
        for(int i = 0; i < N; i++) {
            for(int j = i; j < N; j++) {
                int area = 0;
                int cost = 0;
                int start = 0;
                for(int k = 0; k < M; k++) {
                    int col_sum = A[j][k];
                    if(i > 0) col_sum -= A[i - 1][k];
                    cost += col_sum;
                    if(cost > K) {
                        while(cost > K) {
                            cost -= A[j][start];
                            if(i > 0) cost += A[i - 1][start];
                            start++;
                        }
                    } 
                    area = (k - start + 1) * (j - i + 1);
                    if(area == best_area)
                        if(cost < best_cost)
                            best_cost = cost;
                    if(area > best_area) {
                        best_area = area;
                        best_cost = cost;
                    }
 
                }
            }
        }
        printf("Case #%d: %d %d\n", t, best_area, best_cost);
    }
}

*/

