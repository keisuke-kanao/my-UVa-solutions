
/*
	UVa 10765 - Doves and bombs

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10765_Doves_and_bombs.cpp

	http://www.geeksforgeeks.org/biconnected-components/
*/

#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const int n_max = 10000;
vector<int> edges[n_max];

struct state {
	bool visited_;
	int parent_;
	int discovery_;
	int earliest_; // time of earliest visited vertex reachable from the subtree rooted with this vertex

	state() : parent_(-1), discovery_(-1), earliest_(-1) {}
} states[n_max];

struct pigeon_value {
	int i_, values_;

bool operator<(const pigeon_value& pv) const {
	return (values_ != pv.values_) ? values_ > pv.values_ : i_ < pv.i_;
}
} pigeon_values[n_max];

void find_articulation_points(int u, int t)
{
	states[u].visited_ = true;
	states[u].discovery_ = states[u].earliest_ = t;
	const vector<int>& es = edges[u];
	int nr_children = 0;
	for (size_t i = 0, e = es.size(); i < e; i++) {
		int v = es[i];
		if (!states[v].visited_) {
			nr_children++;
			states[v].parent_ = u;
			find_articulation_points(v, t + 1);

			// see if the subtree rooted with v has a connection to one of the ancestors of u
			states[u].earliest_  = min(states[u].earliest_, states[v].earliest_);
			if (states[u].parent_ == -1 && nr_children > 1 ||
				// u is root of DFS tree and has two or more chilren
				states[u].parent_ != -1 && states[v].earliest_ >= states[u].discovery_) {
            	// u is not root and the earliest value of one of its children is more than discovery value of u.
#ifdef DEBUG
				printf("articulation point = %d\n", u);
#endif
				pigeon_values[u].values_++;
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
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			edges[i].clear();
			states[i].visited_ = false;
			states[i].parent_ = states[i].discovery_ = states[i].earliest_ = -1;
			pigeon_values[i].i_ = i;
			pigeon_values[i].values_ = 1;
		}
		while (true) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (x == -1)
				break;
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		find_articulation_points(0, 0);
		sort(pigeon_values, pigeon_values + n);
		for (int i = 0; i < m; i++)
			printf("%d %d\n", pigeon_values[i].i_, pigeon_values[i].values_);
		putchar('\n');
	}
	return 0;
}

