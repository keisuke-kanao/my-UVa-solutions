
/*
	UVa 775 - Hamiltonian Cycle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_775_Hamiltonian_Cycle.cpp
*/

#include <vector>
#include <cstdio>
using namespace std;

const int n_max = 256;

vector<int> edges[n_max + 1];
bool visited[n_max + 1];
int path[n_max + 1];

bool hamiltonian_cycle(int n, int ni, int vi)
{
	if (ni == n) {
		const vector<int>& e = edges[path[ni - 1]];
		for (size_t i = 0; i < e.size(); i++)
			if (e[i] == 1) {
				path[ni] = 1;
				return true;
			}
		return false;
	}
	else {
		const vector<int>& e = edges[vi];
		for (size_t i = 0; i < e.size(); i++)
			if (!visited[e[i]]) {
				path[ni] = e[i];
				visited[e[i]] = true;
				if (hamiltonian_cycle(n, ni + 1, e[i]))
					return true;
				visited[e[i]] = false;
			}
		return false;
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		getchar();
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			visited[i] = false;
		}
		char c;
		while ((c = getchar()) != '%') {
			ungetc(c, stdin);
			int u, v;
			scanf("%d %d", &u, &v);
			edges[u].push_back(v);
			edges[v].push_back(u);
			getchar();
		}
		path[0] = 1;
		visited[1] = true;
		if (hamiltonian_cycle(n, 1, 1)) {
			for (int i = 0; i <= n; i++)
				printf("%d%c", path[i], ((i < n) ? ' ' : '\n'));
		}
		else
			puts("N");
	}
	return 0;
}

