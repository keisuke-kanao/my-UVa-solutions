
/*
	UVa 12160 - Unlock the Lock

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12160_Unlock_the_Lock.cpp
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int n_max = 10000;
int visited[n_max];

int bfs(int L, int U, int R, int codes[])
{
	memset(visited, -1, sizeof(visited));
	queue<int> q;
	visited[L] = 0;
	q.push(L);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		int p = visited[u];
		if (u == U)
			return p;
		p++;
		for (int i = 0; i < R; i++) {
			int v = (u + codes[i]) % n_max;
			if (visited[v] == -1) {
				visited[v] = p;
				q.push(v);
			}
		}
	}
	return -1;
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int L, U, R;
		scanf("%d %d %d", &L, &U, &R);
		if (!L && !U && !R)
			break;
		const int nr_codes_max = 10;
		int codes[nr_codes_max];
		for (int i = 0; i < R; i++)
			scanf("%d", &codes[i]);
		int nr = bfs(L, U, R, codes);
		printf("Case %d: ", case_nr);
		if (nr != -1)
			printf("%d\n", nr);
		else
			puts("Permanently Locked");
	}
	return 0;
}

