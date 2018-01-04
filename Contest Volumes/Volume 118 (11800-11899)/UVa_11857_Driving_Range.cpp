
/*
	UVa 11857 - Driving Range

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11857_Driving_Range.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 1000000, m_max = 1000000;
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
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		for (int i = 0; i < m; i++)
			scanf("%d %d %d", &edges[i].u_, &edges[i].v_, &edges[i].weight_);
		// apply Kruskal's minimum spanning tree algorithm
		vertices.init(n);
		sort(edges, edges + m); // sort the edges in ascending order of their weights
		int max_cost = -1;
		for (int i = 0; i < m; i++)
			if (vertices.find(edges[i].u_) != vertices.find(edges[i].v_)) {
				vertices.do_union(edges[i].u_, edges[i].v_);
				if (vertices.nr_sets() == 1) {
					max_cost = edges[i].weight_;
					break;
				}
			}
		if (max_cost != -1)
			printf("%d\n", max_cost);
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}

