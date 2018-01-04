
/*
	UVa 11686 - Pick up sticks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11686_Pick_up_sticks.cpp
*/

#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

const int n_max = 1000000;
vector<int> adjacency_list[n_max + 1];
int sorted_list[n_max];
int in_degrees[n_max + 1];

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		for (int i = 1; i <= n; i++) {
			adjacency_list[i].clear();
			in_degrees[i] = 0;
		}
		while (m--) {
			int a, b;
			scanf("%d %d", &a, &b);
			adjacency_list[a].push_back(b);
			in_degrees[b]++;
		}
		int si = 0;
		queue<int> q;
		for (int i = 1; i <= n; i++)
			if (!in_degrees[i])
				q.push(i);
		while (!q.empty()) {
			int i = q.front(); q.pop();
			sorted_list[si++] = i;
			const vector<int>& l = adjacency_list[i];
			for (size_t j = 0, e = l.size(); j < e; j++) {
				int k = l[j];
				if (!--in_degrees[k])
					q.push(k);
			}
		}
		if (si == n) {
			for (int i = 0; i < si; i++)
				printf("%d\n", sorted_list[i]);
		}
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}

