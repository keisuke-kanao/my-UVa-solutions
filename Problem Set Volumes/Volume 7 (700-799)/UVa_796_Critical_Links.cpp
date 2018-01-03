
/*
	UVa 796 - Critical Links

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_796_Critical_Links.cpp
*/


#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
using namespace std;

struct vertex_state {
	bool visited_;
	int parent_;
	int discovery_; // discovery time
	int earliest_; // time of earliest visited vertex reachable from the subtree rooted with this vertex

	vertex_state() : visited_(false), parent_(-1), discovery_(-1), earliest_(-1) {}
};

void find_bridges(int u, int t, const vector< vector<int> >& edges, vector<vertex_state>& states, vector< pair<int, int> >& bridges)
{
	states[u].visited_ = true;
	states[u].discovery_ = states[u].earliest_ = t;
	const vector<int>& es = edges[u];
	for (size_t i = 0, e = es.size(); i < e; i++) {
		int v = es[i];
		if (!states[v].visited_) {
			states[v].parent_ = u;
			find_bridges(v, t + 1, edges, states, bridges);

			// see if the subtree rooted with v has a connection to one of the ancestors of u
			states[u].earliest_  = min(states[u].earliest_, states[v].earliest_);
			// If the lowest vertex reachable from subtree under v is below u in DFS tree, then u - v is a bridge
			if (states[v].earliest_ > states[u].discovery_)
				bridges.push_back(make_pair(min(u, v), max(u, v)));
		}
		else if (v != states[u].parent_)
			states[u].earliest_  = min(states[u].earliest_, states[v].discovery_);
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		vector< vector<int> > edges(n);
		for (int i = 0; i < n; i++) {
			int j, u, v;
			scanf("%d (%d)", &u, &j);
			while (j--) {
				scanf("%d", &v);
				edges[u].push_back(v);
				edges[v].push_back(u);
			}
		}
		vector<vertex_state> states(n);
		vector< pair<int, int> > bridges;
		for (int i = 0; i < n; i++)
			if (!states[i].visited_)
				find_bridges(i, 0, edges, states, bridges);
		sort(bridges.begin(), bridges.end());
		printf("%d critical links\n", bridges.size());
		for (vector< pair<int, int> >::const_iterator i = bridges.begin(), e = bridges.end(); i != e; i++)
			printf("%d - %d\n", i->first, i->second);
		putchar('\n');
	}
	return 0;
}

