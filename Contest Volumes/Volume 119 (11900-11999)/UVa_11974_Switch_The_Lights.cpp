
/*
	UVa 11974 - Switch The Lights

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11974_Switch_The_Lights.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 15, M_max = 100;
int N, M, switches[M_max];
bool visited[1 << N_max];

int bfs()
{
	int s = 1 << N;
	memset(visited, 0, s);
	queue< pair<int, int> > q;
	s--;
	visited[s] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair<int, int> c = q.front();
		q.pop();
		if (!c.first)
			return c.second;
		c.second++;
		for (int i = 0; i < M; i++) {
			s = c.first ^ switches[i];
			if (!visited[s]) {
				visited[s] = true;
				q.push(make_pair(s, c.second));
			}
		}
	}
	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < M; i++) {
			int s = 0;
			for (int j = 0, b = 1 << (N - 1); j < N; j++, b >>= 1) {
				int K;
				scanf("%d", &K);
				if (K)
					s |= b;
			}
			switches[i] = s;
		}
		int nr = bfs();
		if (nr != -1)
			printf("Case %d: %d\n", t, nr);
		else
			printf("Case %d: IMPOSSIBLE\n", t);
	}
	return 0;
}

