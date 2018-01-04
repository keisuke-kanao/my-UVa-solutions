
/*
	UVa 11733 - Airports

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11733_Airports.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 10000, m_max = 100000;
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

int main()
{
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		int n, m, a;
		scanf("%d %d %d", &n, &m, &a);
		for (int i = 0; i < m; i++) {
			int x, y, c;
			scanf("%d %d %d", &edges[i].u_, &edges[i].v_, &edges[i].weight_);
			edges[i].u_--; edges[i].v_--;
		}
		// apply Kruskal's minimum spanning tree algorithm
		vertices.init(n);
		sort(edges, edges + m); // sort the edges in ascending order of their weights
		int cost = 0;
		for (int i = 0; i < m && edges[i].weight_ < a; i++)
			if (vertices.find(edges[i].u_) != vertices.find(edges[i].v_)) {
				vertices.do_union(edges[i].u_, edges[i].v_);
				cost += edges[i].weight_;
				if (vertices.nr_sets() == 1)
					break;
			}
		printf("Case #%d: %d %d\n", tc, cost + a * vertices.nr_sets(), vertices.nr_sets());
	}
	return 0;
}

