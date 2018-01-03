
/*
	UVa 1395 - Slim Span

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1395_Slim_Span.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int n_max = 100, m_max = n_max * (n_max - 1) / 2;

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
	int representatives_[n_max]; // representatives[i] is the representative of a set to which i belongs
 	int ranks_[n_max]; // ranks_[i] is the number of elements in the set to which i belongs
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
} edges[m_max];

struct edge_comparator {
	int weight_;
	edge_comparator(int weight) : weight_(weight) {}

	bool operator() (const edge& i, const edge& j)
	{
		return abs(weight_ - i.weight_) < abs(weight_ - j.weight_);
	}
};

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		for (int i = 0; i < m; i++) {
			int x, y, c;
			scanf("%d %d %d", &edges[i].u_, &edges[i].v_, &edges[i].weight_);
			edges[i].u_--; edges[i].v_--;
		}
		int min_cost = infinite;
		for (int i = 0; i < m; i++) {
			// apply Kruskal's minimum spanning tree algorithm
			vertices.init(n);
			sort(edges, edges + m, edge_comparator(edges[i].weight_)); // sort the edges in ascending order of their differences from edges[i].weight_
			int min_w = infinite, max_w = 0, cost = 0;
			for (int j = 0; j < m && cost < min_cost; j++) {
				const edge& e = edges[j];
				if (vertices.find(e.u_) != vertices.find(e.v_)) {
					vertices.do_union(e.u_, e.v_);
					min_w = min(min_w, e.weight_), max_w = max(max_w, e.weight_);
					cost = max_w - min_w;
					if (vertices.nr_sets() == 1)
						break;
				}
			}
			if (!i && vertices.nr_sets() > 1) // no spanning trees
				break;
			min_cost = min(min_cost, cost);
		}
		printf("%d\n", (min_cost < infinite) ? min_cost : -1);
	}
	return 0;
}

