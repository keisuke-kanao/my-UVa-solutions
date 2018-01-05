
/*
	UVa 10938 - Flea circus

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10938_Flea_circus.cpp

	This solution was verdicted as TLE.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct disjoint_set {
	int n_;
	vector<int> parents_;
	vector<int> ranks_;

	disjoint_set(int n);
	void make_set(int x);
	void do_union(int x, int y);
	int find(int x);
};

disjoint_set::disjoint_set(int n)
	: n_(n), parents_(n), ranks_(n, 0)
{
	for (int i = 0; i < n_; i++)
		parents_[i] = i;
}

void disjoint_set::make_set(int x)
{
	parents_[x] = x; ranks_[x] = 0;
}

void disjoint_set::do_union(int x, int y)
{
	int x_root = find(x), y_root = find(y);
	if (ranks_[x_root] > ranks_[y_root])
		parents_[y_root] = x_root;
	else if (ranks_[x_root] < ranks_[y_root])
		parents_[x_root] = y_root;
	else if (x_root != y_root) {
		parents_[y_root] = x_root;
		ranks_[x_root]++;
	}
}

int disjoint_set::find(int x)
{
	if (parents_[x] == x)
		return x;
	else
		return parents_[x] = find(parents_[x]);
}

enum {white, black};

struct node {
	int parent_;
	int distance_;
	int color_;
	int ancestor_;
	vector<int> children_;

	node() : parent_(-1), distance_(0), color_(white), ancestor_(-1) {}
};

struct lca { // lowest common ancestor
	int u_, v_;
	int ancestor_;
};

/*
function TarjanOLCA(u)
     MakeSet(u);
     u.ancestor := u;
     for each v in u.children do
         TarjanOLCA(v);
         Union(u,v);
         Find(u).ancestor := u;
     u.colour := black;
     for each v such that {u,v} in P do
         if v.colour == black
             print "Tarjan's Lowest Common Ancestor of " + u +
                   " and " + v + " is " + Find(v).ancestor + ".";
*/

void tarjan_OLCA(int u, vector<node>& nodes, vector<lca>& lcas, disjoint_set& ds) // Tarjan's off-line lowest common ancestor algorithm
{
	ds.make_set(u);
	nodes[u].ancestor_ = u;
	vector<int>& children = nodes[u].children_;
	for (size_t i = 0, j = children.size(); i < j; i++) {
		int v = children[i];
		tarjan_OLCA(children[i], nodes, lcas, ds);
		ds.do_union(u, v);
		nodes[ds.find(u)].ancestor_ = u;
	}
	nodes[u].color_ = black;
	for (size_t i = 0, j = lcas.size(); i < j; i++) {
		lca& l = lcas[i];
		if (l.u_ == u && nodes[l.v_].color_ == black) {
			l.ancestor_ = nodes[ds.find(l.v_)].ancestor_;
#ifdef DEBUG
			printf("  %d %d: %d\n", l.u_, l.v_, l.ancestor_);
#endif
		}
		else if (l.v_ == u && nodes[l.u_].color_ == black) {
			l.ancestor_ = nodes[ds.find(l.u_)].ancestor_;
#ifdef DEBUG
			printf("  %d %d: %d\n", l.v_, l.u_, l.ancestor_);
#endif
		}
	}
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		vector<node> nodes(n);
		for (int i = 0; i < n - 1; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--, b--;
			nodes[b].parent_ = a;
			nodes[a].children_.push_back(b);
		}
		int root;
		for (int i = 0; i < n; i++) {
			for (int parent = nodes[i].parent_; parent != -1; parent = nodes[parent].parent_)
				nodes[i].distance_++;
			if (!nodes[i].distance_)
				root = i;
		}
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			printf("  %d: %d\n", i, nodes[i].distance_);
#endif
		int l;
		scanf("%d", &l);
		vector<lca> lcas(l);
		for (int i = 0; i < l; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			u--, v--;
			lcas[i].u_ = u; lcas[i].v_ = v;
		}
		disjoint_set ds(n);
		tarjan_OLCA(root, nodes, lcas, ds);
		for (int i = 0; i < l; i++) {
			int u = lcas[i].u_, v = lcas[i].v_, ancestor = lcas[i].ancestor_,
				d = nodes[u].distance_ + nodes[v].distance_ - 2 * nodes[ancestor].distance_;
#ifdef DEBUG
			printf("u: %d v: %d ancestor: %d distance: %d\n", u, v, ancestor, d);
#endif
			if (u == v)
				printf("The fleas meet at %d.\n", u + 1);
			else {
				for (int j = d / 2; j; j--) {
					if (u == ancestor)
						u = -1;
					else if (u != -1)
						u = nodes[u].parent_;
					if (v == ancestor)
						v = -1;
					else if (v != -1)
						v = nodes[v].parent_;
#ifdef DEBUG
					printf("  u: %d v: %d\n", u, v);
#endif
				}
				if (d % 2) {
					if (u != -1 && v != -1)
						;
					else if (u == -1)
						u = nodes[v].parent_;
					else
						v = nodes[u].parent_;
					if (u > v)
						swap(u, v);
					printf("The fleas jump forever between %d and %d.\n", u + 1, v + 1);
				}
				else {
					printf("The fleas meet at %d.\n", (u != -1) ? u + 1 : v + 1);
				}
			}
		}
	}
	return 0;
}

