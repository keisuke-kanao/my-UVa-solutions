
/*
	UVa 10163 - Storage Keepers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10163_Storage_Keepers.cpp
*/

#include <algorithm>
#include <functional>
#include <cstdio>
using namespace std;

const int N_max = 100, M_max = 30, P_max = 1000, infinite = P_max * M_max + 1;

int Ps[M_max + 1];
int Ls[M_max + 1][N_max + 1];
	// Ls[m][n] is the minimum safe number of U when the keepers between 1 and m look after n storages
int Ys[M_max + 1][N_max + 1];
	// Ys[m][n] is the money paid when the keepers between 1 and m look after n storages

int main()
{
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		for (int m = 1; m <= M; m++)
			scanf("%d", &Ps[m]);
		for (int m = 1; m <= M; m++)
			for (int n = 1; n <= N; n++)
				Ls[m][n] = 0, Ys[m][n] = infinite;
		sort(Ps + 1, Ps + M + 1, greater<int>());
		Ls[1][1] = Ys[1][1] = Ps[1];
		for (int m = 2; m <= M; m++) {
			if (Ps[m] > Ls[m - 1][1])
				Ls[m][1] = Ys[m][1] = Ps[m];
			else
				Ls[m][1] = Ys[m][1] = Ls[m - 1][1];
		}
		for (int n = 2; n <= N; n++)
			if (Ps[1] / n)
				Ls[1][n] = Ps[1] / n, Ys[1][n] = Ps[1];
		for (int m = 2; m <= M; m++)
			for (int n = 2; n <= N; n++)
				for (int k = 1; k < n; k++)
					if (Ps[m] / k)
						Ls[m][n] = max(Ls[m][n], min(Ls[m - 1][n - k], Ps[m] / k));
		int L_max = 0;
		for (int m = 1; m <= M; m++)
			L_max = max(L_max, Ls[m][N]);
		if (!L_max) {
			puts("0 0");
			continue;
		}

		for(int i = 0; i <= M; ++i)
			for(int j = 0; j <= N; ++j)
				Ys[i][j] = infinite;
		Ys[0][0] = 0;
		for(int i = 1; i <= M; ++i){
			for(int j = 0; j <= N; ++j){
				if(Ys[i - 1][j] >= infinite){ continue; }
				Ys[i][j] = min(Ys[i][j], Ys[i - 1][j]);
				int x = min(N, j + Ps[i] / L_max);
				Ys[i][x] = min(Ys[i][x], Ys[i - 1][j] + Ps[i]);
			}
		}
#ifdef DEBUG
		for (int m = 0; m <= M; m++)
			for (int n = 0; n <= N; n++)
				printf("Ls[%d][%d]:%d, Ys[%d][%d]:%d\n", m, n, Ls[m][n], m, n, Ys[m][n]);
#endif
		int Y_min = infinite;
		for (int m = 1; m <= M; m++)
			Y_min = min(Y_min, Ys[m][N]);
		printf("%d %d\n", L_max, Y_min);
	}
	return 0;
}

