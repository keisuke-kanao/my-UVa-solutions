
/*
	UVa 665 - False coin

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_665_False_coin.cpp
*/

#include <cstdio>
#include <cstring>

const int N_max = 100;
int numbers[N_max];
bool coins[N_max + 1], false_coins[N_max + 1];

int main()
{
	int M;
	scanf("%d", &M);
	while (M--) {
		int N, K;
		scanf("%d %d", &N, &K);
		memset(false_coins, -1, sizeof(false_coins));
		while (K--) {
			int P;
			scanf("%d", &P);
			for (int i = 0; i < 2 * P; i++)
				scanf("%d", &numbers[i]);
			char s[2];
			scanf("%s", s);
			memset(coins, 0, sizeof(coins));
			if (s[0] == '=') {
				for (int i = 0; i < 2 * P; i++)
					coins[numbers[i]] = true;
				for (int i = 1; i <= N; i++)
					if (coins[i])
						false_coins[i] = false;
			}
			else {
				if (s[0] == '<')
					for (int i = P; i < 2 * P; i++)
						coins[numbers[i]] = true;
				else
					for (int i = 0; i < P; i++)
						coins[numbers[i]] = true;
				for (int i = 1; i <= N; i++)
					false_coins[i] = false_coins[i] && coins[i];
			}
#ifdef DEBUG
			for (int i = 1; i <= N; i++)
				printf("%d%c", false_coins[i], ((i < N) ? ' ' : '\n'));
#endif
		}
		int ci = 0;
		for (int i = 1; i <= N; i++)
			if (false_coins[i]) {
				if (!ci)
					ci = i;
				else {
					ci = 0; break;
				}
			}
		printf("%d\n", ci);
		if (M)
			putchar('\n');
	}
	return 0;
}

/*
3

5 3
2 1 2 3 4
<
1 1 4
=
1 2 5
=

5 2
1 1 2
=
1 1 3
<

5 3
1 1 3
<
1 1 4
=
1 3 4
=
*/

