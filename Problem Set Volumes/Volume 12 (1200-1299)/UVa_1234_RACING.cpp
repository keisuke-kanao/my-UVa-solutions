
/*
	UVa 1234 - RACING

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1234_RACING.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
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
	int u_, v_, w_;
	bool operator<(const edge& e) const {return w_ > e.w_;}
} edges[m_max];

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			edge& e = edges[i];
			scanf("%d %d %d", &e.u_, &e.v_, &e.w_);
			e.u_--, e.v_--;
		}
		// apply Kruskal's algorithm to get a maximum spanning tree
		vertices.init(n);
		sort(edges, edges + m); // sort the edges in descending order of their weights
		int min_cost = 0;
		for (int i = 0; i < m; i++) {
			edge& e = edges[i];
			if (vertices.find(e.u_) != vertices.find(e.v_)) {
#ifdef DEBUG
				printf("%d-%d: %d\n", e.u_ + 1, e.v_ + 1, e.w_);
#endif
				vertices.do_union(e.u_, e.v_);
			}
			else {
#ifdef DEBUG
				printf("cycle %d-%d: %d\n", e.u_ + 1, e.v_ + 1, e.w_);
#endif
				min_cost += e.w_;
			}
		}
		printf("%d\n", min_cost);
	}
	scanf("%*d"); // read '0'
	return 0;
}

