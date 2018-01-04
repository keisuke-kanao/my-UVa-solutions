
/*
	UVa 11747 - Heavy Cycle Edges

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11747_Heavy_Cycle_Edges.cpp

	An accepted solution.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class union_find {
public:
	union_find(int _n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}

private:
	int n_; // number of elements
	int s_; // number of sets
	vector<int> representatives_; // representatives[i] is the representative of a set to which i belongs
	vector<int> ranks_; // ranks_[i] is the number of elements in the set to which i belongs
};

union_find::union_find(int n)
	: n_(n), s_(n), representatives_(n), ranks_(n, 1)
{
	for (int i = 0; i < n_; i++)
		representatives_[i] = i;
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
	int u_, v_;
	int w_;

	bool operator<(const edge& e) const {return w_ < e.w_;}
};

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		union_find vertices(n);
		vector<edge> edges(m);
		for (int i = 0; i < m; i++)
			cin >> edges[i].u_ >> edges[i].v_ >> edges[i].w_;
		sort(edges.begin(), edges.end());
		for (int i = 0; i < m; i++)
			if (vertices.do_union(edges[i].u_, edges[i].v_) != -1)
				edges[i].w_ = -1;
		int nw = 0;
		for (int i = 0; i < m; i++)
			if (edges[i].w_ != -1) {
				if (nw++)
					cout << ' ';
				cout << edges[i].w_;
			}
		if (nw)
			cout << endl;
		else
			cout << "forest\n";
	}
	return 0;
}

