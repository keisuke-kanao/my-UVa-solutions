
/*
	UVa 908 - Re-connecting Computer Sites

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_908_Re-connecting_Computer_Sites.cpp

	This is an accepted solution.
*/

#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 1000000;

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
};

int main()
{
	bool printed = false;
	int n;
	while (scanf("%d", &n) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		int mst = 0;
		for (int i = 0; i < n - 1; i++) {
			int w;
			scanf("%*d %*d %d", &w);
			mst += w;
		}
		int k;
		scanf("%d", &k);
		vector<edge> edges;
		for (int i = 0; i < k; i++) {
			edge e;
			scanf("%d %d %d", &e.u_, &e.v_, &e.weight_);
			e.u_--; e.v_--;
			edges.push_back(e);
		}
		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			edge e;
			scanf("%d %d %d", &e.u_, &e.v_, &e.weight_);
			e.u_--; e.v_--;
			edges.push_back(e);
		}
		printf("%d\n", mst);
		sort(edges.begin(), edges.end()); // sort the edges in ascending order of their weights
		mst = 0;
		// apply Kruskal's minimum spannig tree algorithm
		vertices.init(n);
		for (size_t i = 0, e = edges.size(); i < e; i++) {
			if (vertices.find(edges[i].u_) != vertices.find(edges[i].v_)) {
				vertices.do_union(edges[i].u_, edges[i].v_);
				mst += edges[i].weight_;
			}
			if (vertices.nr_sets() == 1)
				break;
		}
		printf("%d\n", mst);
	}
	return 0;
}

