
/*
	UVa 10938 - Flea circus

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10938_Flea_circus.cpp

	An accepted solution.
*/

#include <cstdio>
#include <vector>
using namespace std;

const int n_max = 5000;
vector<int> nodes[n_max + 1];
bool visited[n_max + 1];
int path[n_max + 1];

void dfs(int distance, int u, int v, bool& done)
{
	if (visited[u] || done)
		return;
	path[distance] = u;
	if (u == v) {
		done = true;
		if (distance % 2 == 0)
			printf("The fleas meet at %d.\n", path[distance / 2]);
		else {
			if (path[distance / 2] < path[distance / 2 + 1])
				printf("The fleas jump forever between %d and %d.\n", path[distance / 2], path[distance / 2 + 1]);
			else
				printf("The fleas jump forever between %d and %d.\n", path[distance / 2 + 1], path[distance / 2]);
		}
	}
	visited[u] = true;
	vector<int>& ns = nodes[u];
	for (size_t i = 0, j = ns.size(); i < j; i++)
		dfs(distance + 1, ns[i], v, done);
	visited[u] = false;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 1; i <= n; i++)
			nodes[i].clear();
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			nodes[a].push_back(b);
			nodes[b].push_back(a);
		}
		int l;
		scanf("%d", &l);
		while(l--) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(u == v)
				printf("The fleas meet at %d.\n", u);
			else {
				bool done = false;
				dfs(0, u, v, done);
			}
        }
    }
    return 0;
}

