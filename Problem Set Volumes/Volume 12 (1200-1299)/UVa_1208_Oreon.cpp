
/*
	UVa 1208 - Oreon

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1208_Oreon.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 26, m_max = n_max * n_max;
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
	edge() {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}
	bool operator==(const edge& e) const {return u_ == e.u_ && v_ == e.v_ && weight_ == e.weight_;}
	bool operator<(const edge& e) const
	{
		if (weight_ != e.weight_)
			return weight_ < e.weight_;
		else if (u_ != e.u_)
			return u_ < e.u_;
		else
			return v_ < e.v_;
	}
} edges[m_max];

int main()
{
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		int n, m = 0;
		scanf("%d", &n);
		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++) {
				int w;
				if (v < n - 1)
					scanf("%d,", &w);
				else
					scanf("%d", &w);
				if (w)
					edges[m++] = edge(u, v, w);
			}
		printf("Case %d:\n", tc);
		// apply Kruskal's minimum spanning tree algorithm
		vertices.init(n);
		sort(edges, edges + m); // sort the edges in ascending order of their weights
		for (int i = 0; i < m; i++)
			if (vertices.find(edges[i].u_) != vertices.find(edges[i].v_)) {
				printf("%c-%c %d\n", 'A' + edges[i].u_, 'A' + edges[i].v_, edges[i].weight_);
				vertices.do_union(edges[i].u_, edges[i].v_);
				if (vertices.nr_sets() == 1)
					break;
			}
	}
	return 0;
}

