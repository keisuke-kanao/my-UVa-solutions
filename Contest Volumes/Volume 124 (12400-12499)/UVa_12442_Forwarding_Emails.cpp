
/*
	UVa 12442 - Forwarding Emails

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12442_Forwarding_Emails.cpp
*/

#include <vector>
#include <cstdio>
using namespace std;

const int N_max = 50000;
int edges[N_max + 1];
bool visited[N_max + 1];
int connections[N_max + 1];

int dfs(int u)
{
	int c = 0;
	visited[u] = true;
	int v = edges[u];
	if (v && !visited[v])
		c += 1 + dfs(v);
	visited[u] = false;
	return connections[u] = c;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			edges[i] = 0;
			connections[i] = -1;
		}
		for (int i = 0; i < N; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			edges[u] = v;
		}
		int max_c = 0, max_i = -1;
		for (int i = 1; i <= N; i++) {
			if (connections[i] == -1)
				dfs(i);
			if (connections[i] > max_c) {
				max_c = connections[i]; max_i = i;
			}
		}
		printf("Case %d: %d\n", t, max_i);
	}
	return 0;
}

