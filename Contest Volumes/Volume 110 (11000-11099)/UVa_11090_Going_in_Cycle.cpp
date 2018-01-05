
/*
	UVa 11090 - Going in Cycle!!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11090_Going_in_Cycle.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

struct edge {
    int v_, w_;
    edge(int v, int w): v_(v), w_(w) {}
};

double spfa(int st, int n, const vector< vector<edge> >& edges)
{
	vector< vector<int> > dists(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));
	vector< vector<bool> > in_queues(n + 1, vector<bool>(n + 1, false));
    queue< pair<int, int> > q;
    dists[st][0] = 0;
    q.push(make_pair(st, 0));
	while(!q.empty()) {
		int u = q.front().first, v = q.front().second;
		q.pop();
        in_queues[u][v] = false;
		if (v + 1 > n)
			continue;
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int ev = es[i].v_, ew = es[i].w_;
            if (dists[ev][v + 1] > dists[u][v] + ew) {
				dists[ev][v + 1] = dists[u][v] + ew;
                if(!in_queues[ev][v + 1]) {
                    in_queues[ev][v + 1] = true;
                    q.push(make_pair(ev, v + 1));
                }
            }
		}
	}
	double mean = numeric_limits<double>::max();
    for(int i = 1; i <= n; i++)
		if(dists[st][i] < numeric_limits<int>::max())
			mean = min(mean, static_cast<double>(dists[st][i]) / i);
	return mean;
}

int main()
{
	int N;
	cin >> N;
	for (int cn = 1; cn <= N; cn++) {
		int n, m;
		cin >> n >> m;
		vector< vector<edge> > edges(n + 1);
		while (m--) {
			int a, b, c;
			cin >> a >> b >> c;
			edges[a].push_back(edge(b, c));
		}
		double min_mean = numeric_limits<double>::max();
		for (int i = 1; i <= n; i++)
			min_mean = min(min_mean, spfa(i, n, edges));
		cout << "Case #" << cn << ": ";
		if (min_mean < numeric_limits<float>::max())
			cout << fixed << setprecision(2) << min_mean << endl;
		else
			cout << "No cycle found.\n";
	}
	return 0;
}

/*

Sample Input

2
2 1
1 2 1
2 2
1 2 2
2 1 3

Output for Sample Input

Case #1: No cycle found.
Case #2: 2.50
*/

