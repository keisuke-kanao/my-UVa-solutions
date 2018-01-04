
/*
	UVa 302 - John's trip

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_302_Johns_trip.cpp
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 1994, m_max = 44;

struct edge {
	int v_, nr_;

	edge() {}
	edge(int v, int nr) : v_(v) , nr_(nr) {}

	bool operator<(const edge& e) const {return nr_ < e.nr_;}
};

vector<edge> edges[m_max + 1];
int n, m, nrs[n_max];
bool visited[m_max + 1];

void remove_edge(int u, int v, int nr)
{
	lower_bound(edges[u].begin(), edges[u].end(), edge(v, nr))->v_ = 0;
	lower_bound(edges[v].begin(), edges[v].end(), edge(u, nr))->v_ = 0;
}

void recover_edge(int u, int v, int nr)
{
	lower_bound(edges[u].begin(), edges[u].end(), edge(v, nr))->v_ = v;
	lower_bound(edges[v].begin(), edges[v].end(), edge(u, nr))->v_ = u;
}

int dfs(int u) // count the number of vertices reachable from u
{
	visited[u] = true;
	int nr_reachable = 1;
	const vector<edge>& es = edges[u];
	for (size_t i = 0, j = es.size(); i < j; i++) {
		int v = es[i].v_;
		if (v && !visited[v])
			nr_reachable += dfs(v);
	}
	return nr_reachable;
}

bool is_bridge(int u, int v, int nr)
{
	if (u == v)
		return false;
	const vector<edge>& es = edges[u];
	int size = 0;
	for (size_t i = 0, j = es.size(); i < j; i++)
		if (es[i].v_)
			size++;
	if (size == 1) // v is the only adjacent vertex of u
		return false;
	// count the number of vertices reachable from u
	memset(visited, 0, sizeof(visited));
	int nr_reachable_0 = dfs(u);
	// remove edge (u, v) and after removing the edge, count the number of vertices reachable from u
	remove_edge(u, v, nr);
	memset(visited, 0, sizeof(visited));
	int nr_reachable_1 = dfs(u);
	recover_edge(u, v, nr);
	return nr_reachable_0 > nr_reachable_1;
}

void print_eulerian_path(int u)
{
	vector<edge>& es = edges[u];
	for (size_t i = 0, j = es.size(); i < j; i++) {
		int v = es[i].v_, nr = es[i].nr_;
		if (v && !is_bridge(u, v, nr)) {
#ifdef DEBUG
			printf("%d %d %d\n", u, v, nr);
#endif
			nrs[n++] = nr;
			remove_edge(u, v, nr);
			print_eulerian_path(v);
		}
	}
}

bool compare_edge(const edge& ei, const edge& ej)
{
	return ei.nr_ == ej.nr_;
}

int main()
{
	while (true) {
		int x, y, z;
		scanf("%d %d", &x, &y);
		if (!x && !y)
			break;
		scanf("%d", &z);
		if (m) {
			for (int i = 1; i <= m; i++)
				edges[i].clear();
			n = m = 0;
		}
		int s = 0;
		while (true) {
			edges[x].push_back(edge(y, z));
			edges[y].push_back(edge(x, z));
			if (!m)
				s = min(x, y);
			m = max(m, max(x, y));
			scanf("%d %d", &x, &y);
			if (!x && !y)
				break;
			scanf("%d", &z);
		}
		bool eulerian_circuit = true;
		for (int i = 1; i <= m; i++)
			if (edges[i].size() & 1) {
				eulerian_circuit = false;
				break;
			}
		if (eulerian_circuit) {
			for (int i = 1; i <= m; i++) {
				vector<edge>& es = edges[i];
				sort(es.begin(), es.end());
				es.resize(distance(es.begin(), unique(es.begin(), es.end(), compare_edge)));
			}
			print_eulerian_path(s);
			for (int i = 0; i < n; i++)
				printf("%d%c", nrs[i], ((i < n - 1) ? ' ' : '\n'));
			putchar('\n');
		}
		else
			printf("Round trip does not exist.\n\n");
	}
	return 0;
}

