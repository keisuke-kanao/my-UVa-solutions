
/*
	UVa 11631 - Dark roads

	To build using Visucal Studio 2008:
		cl -EHsc UVa_11631_Dark_roads.cpp

	from University of Ulm Local Contest 2009
		(http://www.informatik.uni-ulm.de/acm/Locals/2009/)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int m_max = 200000, n_max = 200000;

class union_find {
public:
	union_find() {}
	~union_find() {}
	void init(int n);
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}

private:
	int n_; // number of elements
	int s_; // number of sets
	int representatives_[m_max]; // representatives[i] is the representative of a set to which i belongs
	int ranks_[m_max]; // ranks_[i] is the number of elements in the set to which i belongs
};

void union_find::init(int n)
{
	n_ = n; s_ = n;
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

union_find vertices;

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int weight_;

	edge() : u_(-1), v_(-1), weight_(-1) {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}

	bool operator<(const edge& e) const {return weight_ < e.weight_;}
} edges[n_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int m, n;
		cin >> m >> n;
		if (!m && !n)
			break;
		int sum_of_weights = 0;
		for (int i = 0; i < n; i++) {
			cin >> edges[i].u_ >> edges[i].v_ >> edges[i].weight_;
			sum_of_weights += edges[i].weight_;
		}
		sort(edges, edges + n);
		vertices.init(m);
		int sum_of_mst_weights = 0;
		for (int i = 0; i < n; i++)
			if (vertices.do_union(edges[i].u_, edges[i].v_) != -1)
				sum_of_mst_weights += edges[i].weight_;
		cout << sum_of_weights - sum_of_mst_weights << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

