
/*
	UVa 11354 - Bond

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11354_Bond.cpp

	This is an accepted solution.
*/

/*
When constructing the union-find tree, add weight info to the edge in the union-find tree.
For query(a,b):
query(a,b) := max(the last edge weight of path a -> LCA(a,b),
                  the last edge weight of path b -> LCA(a,b));

LCA(a,b) is LCA of a,b in union-find tree.
The hight of tree is O(logn), so you could answer the query with O(logn).
*/

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 50000, M_max = 100000;

class union_find {
public:
	void init(int n);
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}

private:
	int n_; // number of elements
	int s_; // number of sets
	int representatives_[N_max]; // representatives[i] is the representative of a set to which i belongs
 	int ranks_[N_max]; // ranks_[i] is the number of elements in the set to which i belongs
} vertices;

void union_find::init(int n)
{
	n_ = s_ = n;
	for (int i = 0; i < n_; i++) {
		representatives_[i] = i;
		ranks_[i] = 1;
	}
}

int union_find::find(int i) const // return the representative of a set to which i belongs
{
	return (representatives_[i] == i) ? i : find(representatives_[i]);
}

int union_find::do_union(int i, int j)
// generate the union of the two sets to which i and j belong and return the representative of the result set
{
	int ri = find(i), rj = find(j);
	if (ri == rj) // already in the same set
		return -1;
	s_--;
	if (ranks_[ri] >= ranks_[rj]) {
		ranks_[ri] += ranks_[rj];
		representatives_[rj] = ri;
		return ri;
	}
	else {
		ranks_[rj] += ranks_[ri];
		representatives_[ri] = rj;
		return rj;
	}
}

struct edge {
	int u_, v_, weight_;
	bool operator<(const edge& e) const {return weight_ < e.weight_;}
} edges[M_max];


struct mst_edge {
	int v_;
	int weight_;
	mst_edge(int v, int weight) : v_(v), weight_(weight) {}
};

vector<mst_edge> mst_edges[N_max];

// for below, see "Range Minimum Query and Lowest Common Ancestor - topcoder.html".

const int di_max = 1000000000, level_max = 16; // ceil(log2(N_max))
int levels[N_max]; // level (depth) of node i in the tree
int weights[N_max];
int parents[N_max];	// parent node of i
int ancestors[N_max][level_max + 1], max_weights[N_max][level_max + 1];
	// ancestors[i][j] is the 2^j-th ancestor of node i

void dfs(int u, int parent, int level)
{
	levels[u] = level;
	const vector<mst_edge>& mes = mst_edges[u];
	for (size_t i = 0; i < mes.size(); i++) {
		int v = mes[i].v_, w = mes[i].weight_;
		if (v != parent) {
			parents[v] = u, weights[v] = w;
			dfs(v, u, level + 1);
		}
	}
}

void process3(int n)
{
	for (int i = 0 ; i < n; i++) {
		// the first ancestor of every node i is parents[i]
		ancestors[i][0] = parents[i], max_weights[i][0] = weights[i];
		for (int j = 1; 1 << j < n; j++)
			ancestors[i][j] = -1;
	}
	for (int j = 1; 1 << j < n; j++)
		for (int i = 0; i < n; i++)
			if (ancestors[i][j - 1] != -1) {
                int a = ancestors[i][j - 1];
				ancestors[i][j] = ancestors[a][j - 1];
				max_weights[i][j] = max(max_weights[i][j - 1], max_weights[a][j - 1]);
			}
}

int query(int p, int q)
{
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
	int max_w = -di_max;
	for (int i = log; i >= 0; i--)
		if (levels[p] - (1 << i) >= levels[q]) {
			max_w = max(max_w, max_weights[p][i]);
			p = ancestors[p][i];
		}
	if (p == q)
		return max_w;
	// we compute LCA(p, q) using the values in ancestors[][]
	for (int i = log; i >= 0;i--)
		if (ancestors[p][i] != -1 && ancestors[p][i] != ancestors[q][i]) {
			max_w = max(max_w, max_weights[p][i]);
			p = ancestors[p][i];
            max_w = max(max_w, max_weights[q][i]);
			q = ancestors[q][i];
		}
	max_w = max(max_w, weights[p]);
	max_w = max(max_w, weights[q]);
	return max_w;
}

int main()
{
	bool printed = false;
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &edges[i].u_, &edges[i].v_, &edges[i].weight_);
			edges[i].u_--; edges[i].v_--;
		}
		// apply Kruskal's minimum spanning tree algorithm
		vertices.init(N);
		sort(edges, edges + M); // sort the edges in ascending order of their weights
		for (int i = 0; i < N; i++)
			mst_edges[i].clear();
		for (int i = 0; i < M; i++) {
			int u = edges[i].u_, v = edges[i].v_, w = edges[i].weight_;
			if (vertices.find(u) != vertices.find(v)) {
				vertices.do_union(u, v);
				mst_edges[u].push_back(mst_edge(v, w)), mst_edges[v].push_back(mst_edge(u, w));
				if (vertices.nr_sets() == 1)
					break;
			}
		}
		dfs(0, -1, 0);
		process3(N);
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			int s, t;
			scanf("%d %d", &s, &t);
			printf("%d\n", query(s - 1, t - 1));
		}
	}
	return 0;
}

