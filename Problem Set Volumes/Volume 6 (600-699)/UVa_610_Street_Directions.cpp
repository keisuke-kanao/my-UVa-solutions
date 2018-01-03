
/*
	UVa 610 - Street Directions

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_610_Street_Directions.cpp
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

const int n_max = 1000;

vector<int> edges[n_max + 1];
bool bridges[n_max + 1][n_max + 1]; // bridges[u][v] is true if an edge u - v (u < v) is a bridge

struct state {
	bool visited_;
	int parent_;
	int discovery_; // discovery time
	int earliest_; // time of earliest visited vertex reachable from the subtree rooted with this vertex

	state() : visited_(false), parent_(-1), discovery_(-1), earliest_(-1) {}
} states[n_max + 1];

void find_bridges(int u, int t)
{
	states[u].visited_ = true;
	states[u].discovery_ = states[u].earliest_ = t;
	const vector<int>& es = edges[u];
	for (size_t i = 0, e = es.size(); i < e; i++) {
		int v = es[i];
		if (!states[v].visited_) {
			states[v].parent_ = u;
			find_bridges(v, t + 1);

			// see if the subtree rooted with v has a connection to one of the ancestors of u
			states[u].earliest_  = min(states[u].earliest_, states[v].earliest_);
			// If the lowest vertex reachable from subtree under v is below u in DFS tree, then u - v is a bridge
			if (states[v].earliest_ > states[u].discovery_) {
				bridges[min(u, v)][max(u, v)] = true;
#ifdef DEBUG
				printf("bridge: %d - %d\n", min(u, v), max(u, v));
#endif
			}
		}
		else if (v != states[u].parent_)
			states[u].earliest_  = min(states[u].earliest_, states[v].discovery_);
	}
#ifdef DEBUG
	printf("%d: parent = %d, discovery = %d, earliest = %d\n", u,
		states[u].parent_, states[u].discovery_, states[u].earliest_);
#endif
}

int main()
{
	for (int cn = 1; ; cn++) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			states[i].visited_ = false;
			states[i].parent_ = states[i].discovery_ = states[i].earliest_ = -1;
			for (int j = i + 1; j <= n; j++)
				bridges[i][j] = false;
		}
		while (m--) {
			int i, j;
			scanf("%d %d", &i, &j);
			edges[i].push_back(j);
			edges[j].push_back(i);
		}
		find_bridges(1, 0);
		printf("%d\n\n", cn);
#ifdef __SORTED_LIST__
		vector< pair<int, int> > streets;
		for (int u = 1; u <= n; u++) {
			const vector<int>& es = edges[u];
			for (size_t i = 0, e = es.size(); i < e; i++) {
				int v = es[i];
				if (u < v) {
					bool b = bridges[u][v];
					if (states[v].parent_ == u) {
						streets.push_back(make_pair(u, v));
						if (b)
							streets.push_back(make_pair(v, u));
					}
					else if (states[u].parent_ == v) {
						streets.push_back(make_pair(v, u));
						if (b)
							streets.push_back(make_pair(u, v));
					}
					else if (states[v].discovery_ < states[u].discovery_)
						streets.push_back(make_pair(u, v));
					else
						streets.push_back(make_pair(v, u));
				}
			}
		}
		sort(streets.begin(), streets.end());
		for (vector< pair<int, int> >::const_iterator i = streets.begin(), e = streets.end(); i != e; i++)
			printf("%d %d\n", i->first, i->second);
#else
		for (int u = 1; u <= n; u++) {
			const vector<int>& es = edges[u];
			for (size_t i = 0, e = es.size(); i < e; i++) {
				int v = es[i];
				if (u < v) {
					bool b = bridges[u][v];
					if (states[v].parent_ == u) {
						printf("%d %d\n", u, v);
						if (b)
							printf("%d %d\n", v, u);
					}
					else if (states[u].parent_ == v) {
						printf("%d %d\n", v, u);
						if (b)
							printf("%d %d\n", u, v);
					}
					else if (states[v].discovery_ < states[u].discovery_)
						printf("%d %d\n", u, v);
					else
						printf("%d %d\n", v, u);
				}
			}
		}
#endif
		puts("#");
	}
	return 0;
}

