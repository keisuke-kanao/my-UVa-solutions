
/*
	UVa 1241 - Jollybee Tournament

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1241_Jollybee_Tournament.cpp
*/

#include <cstdio>

const int nr_players_max = 1 << 10;
bool players[nr_players_max];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M;
		scanf("%d %d", &N, &M);
		int nr_players = 1 << N;
		for (int i = 0; i < nr_players; i++)
			players[i] = true;
		while (M--) {
			int p;
			scanf("%d", &p);
			players[p - 1] = false;
		}
		int nr_wo = 0;
		for (int n = nr_players; n; n >>= 1)
			for (int i = 0; i < n / 2; i++) {
				if (players[2 * i] && !players[2 * i + 1] || !players[2 * i] && players[2 * i + 1])
					nr_wo++;
				players[i] = players[2 * i] || players[2 * i + 1];
			}
		printf("%d\n", nr_wo);
	}
	return 0;
}


/*

Sample Input 

3 
2 2 
3 4 
3 5 
1 2 3 4 5 
2 1
2

Sample Output 

1 
2 
1

*/

