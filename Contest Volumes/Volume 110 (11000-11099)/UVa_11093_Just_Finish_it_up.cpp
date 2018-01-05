
#include <cstdio>
#include <cstring>

int stations[200100];

int main()
{
	int N, T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &stations[i]);
			stations[N + i] = stations[i];
		}
		for (int i = 1; i <= N; i++) {
			int x;
			scanf("%d", &x);
			stations[i] -= x;
			stations[N + i] -= x;
		}
		stations[0] = 0;
		for (int i = 1; i <= N * 2; i++)
			stations[i] += stations[i - 1];
		int s = 0, mi = 1, cn = 0;
		for (int i = 0; i <= N * 2; i++) {
			if (stations[i] >= mi) {
				if (++cn > N)
					break;
			}
			else {
				mi = stations[i];
				s = i;
				cn = 1;
				if (i >= N)
					break;
			}
		}
		printf("Case %d: ", cs);
		if (cn > N)
			printf("Possible from station %d\n", s + 1);
		else
			printf("Not possible\n");
	}
	return 0;
}

