
/*
	UVa 10147 - Highways

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10147_Highways.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
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

double euclidean_distance(const pair<int, int>& p1, const pair<int, int>& p2)
{
	double dx = static_cast<double>(p1.first - p2.first), dy = static_cast<double>(p1.second - p2.second);
	return sqrt(dx * dx + dy * dy);
}

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	double weight_;

	edge() : u_(-1), v_(-1), weight_(0.0) {}
	edge(int u, int v, double weight) : u_(u), v_(v), weight_(weight) {}

	bool operator<(const edge& e) const {return weight_ < e.weight_;}
};

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector< pair<int, int> > points(n + 1);
		for (int i = 1; i <= n; i++)
			cin >> points[i].first >> points[i].second;
		union_find vertices(n + 1);
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int j, k;
			cin >> j >> k;
			vertices.do_union(j, k);
		}
		if (vertices.nr_sets() == 2)
			cout << "No new highways need\n";
		else {
			vector<edge> edges;
			for (int i = 1; i < n; i++)
				for (int j = i + 1; j <= n; j++)
					if (vertices.find(i) != vertices.find(j))
						edges.push_back(edge(i, j, euclidean_distance(points[i], points[j])));
			// calculate the minimum spanning tree for the unconnecetd towns
			sort(edges.begin(), edges.end());
			for (vector<edge>::const_iterator ei = edges.begin(), ee = edges.end(); ei != ee; ++ei)
				if (vertices.do_union(ei->u_, ei->v_) != -1)
#if DEBUG
					cout << ei->u_ << ' ' << ei->v_ << ' ' << ei->weight_ << endl;
#else
					cout << ei->u_ << ' ' << ei->v_ << endl;
#endif
		}
		if (t)
			cout << endl;
	}
	return 0;
}

