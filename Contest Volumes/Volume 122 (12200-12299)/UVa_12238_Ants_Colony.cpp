
/*
	UVa 12238 - Ants Colony

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12238_Ants_Colony.cpp
*/

/*
For explanation, see Range Minimum Query and Lowest Common Ancestor - topcoder
	(https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/).
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int N_max = 100000;

struct edge {
	int v_;
	int weight_;
	edge(int v, int weight) : v_(v), weight_(weight) {}
};

vector<edge> edges[N_max];

const int level_max = 17; // ceil(log2(N_max))
int levels[N_max]; // level (depth) of node i in the tree
long long weights[N_max]; // weights[i] is the total length from the root to i-th node
int parents[N_max];	// parent node of i
int ancestors[N_max][level_max + 1];
	// ancestors[i][j] is the 2^j-th ancestor of node i

void dfs(int u, int parent, int level)
{
	levels[u] = level;
	const vector<edge>& mes = edges[u];
	for (size_t i = 0; i < mes.size(); i++) {
		int v = mes[i].v_, w = mes[i].weight_;
		if (v != parent) {
			parents[v] = u, weights[v] = w + weights[u];
			dfs(v, u, level + 1);
		}
	}
}

void process3(int n)
{
	for (int i = 0 ; i < n; i++) {
		// the first ancestor of every node i is parents[i]
		ancestors[i][0] = parents[i];
		for (int j = 1; 1 << j < n; j++)
			ancestors[i][j] = -1;
	}
	for (int j = 1; 1 << j < n; j++)
		for (int i = 0; i < n; i++)
			if (ancestors[i][j - 1] != -1)
				ancestors[i][j] = ancestors[ancestors[i][j - 1]][j - 1];
}

long long query(int p, int q)
{
	long long w = weights[p] + weights[q];
	//if p is situated on a higher level than q then we swap them
	if (levels[p] < levels[q])
		swap(p, q);
	// we compute the value of [log2(level[p)]
	int log;
	for (log = 1; 1 << log <= levels[p]; log++)
		;
	log--;
	// we find the ancestor of node p situated on the same level
	// with q using the values in ancestors[][]
	for (int i = log; i >= 0; i--)
		if (levels[p] - (1 << i) >= levels[q])
			p = ancestors[p][i];
	if (p == q)
	return w - weights[p] * 2;
	// we compute LCA(p, q) using the values in ancestors[][]
	for (int i = log; i >= 0;i--)
		if (ancestors[p][i] != -1 && ancestors[p][i] != ancestors[q][i])
			p = ancestors[p][i], q = ancestors[q][i];
	return w - weights[parents[p]] * 2;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			edges[i].clear();
		for (int v = 1; v < N; v++) {
			int u, w;
			scanf("%d %d", &u, &w);
			edges[u].push_back(edge(v, w)), edges[v].push_back(edge(u, w));
		}
		dfs(0, -1, 0);
		process3(N);
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			int s, t;
			scanf("%d %d", &s, &t);
			printf("%lld%c", query(s, t), ((Q) ? ' ' : '\n'));
		}
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

