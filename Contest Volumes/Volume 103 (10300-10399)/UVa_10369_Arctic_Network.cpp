
/*
	UVa 10369 - Arctic Network

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10369_Arctic_Network.cpp

	from Waterloo ACM Programming Contest September 28, 2002 Problem C
		(http://plg1.cs.uwaterloo.ca/~acm00/020928/)
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
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

struct edge {
	int u_, v_;
	double weight_;
	bool operator<(const edge& e) const {return weight_ < e.weight_;}
};

double euclidean_distance(const pair<int, int>& p, const pair<int, int>& q)
{
	double dx = static_cast<double>(p.first - q.first), dy = static_cast<double>(p.second - q.second);
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int s, p;
		cin >> s >> p;
		vector< pair<int, int> > vertices(p);
		for (int i = 0; i < p; i++)
			cin >> vertices[i].first >> vertices[i].second;
		int nr_edges = p * (p - 1) / 2; // C(p, 2)
		vector<edge> edges(nr_edges);
		for (int i = 0, j = 0; j < p - 1; j++)
			for (int k = j + 1; k < p; k++) {
				edge& e = edges[i++];
				e.u_ = j; e.v_ = k;
				e.weight_ = euclidean_distance(vertices[j], vertices[k]);
			}
		sort(edges.begin(), edges.end());
		union_find forests(p);
		double min_d = 0.0;
		// using Kruskal algorithm, find "Minimum Spanning Forest" in the graph that has S components left
		for (int i = 0; i < nr_edges; i++)
			if (forests.do_union(edges[i].u_, edges[i].v_) != -1) {
				min_d = max(min_d, edges[i].weight_);
				if (forests.nr_sets() == s)
					break;
			}
		printf("%.2f\n", min_d);
	}
	return 0;
}

