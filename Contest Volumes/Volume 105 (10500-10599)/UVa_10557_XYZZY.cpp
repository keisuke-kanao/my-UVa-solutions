
/*
	UVa 10557 - XYZZY

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_10557_XYZZY.cpp

	from 27 September, 2003 - Waterloo local contest Problem D
		(http://plg1.cs.uwaterloo.ca/~acm00/030927/data/)
*/

/*
From Our Quest to Solve the UVa ICPC Online Problem Set :: UVa Solutions
	(http://www.questtosolve.com/browse.php?pid=10557)

Firstly, change all positive energies into negative, and negative energies into positive. 
Now the energies are more intuitively like costs. Positive is bad, negative is good.

Clearly we're trying to find the shortest path to the end, and we may have negative-weight cycles. 
Therefore, Bellman-Ford will be the algorithm of choice.

Now, just because we have a shortest path with cost < 100, that doesn't mean we can actually *use* that path. 
The net cost may be < 100, but there may be a section that takes more than 100 energy to traverse. 
So we need to modify Bellman-Ford a bit. Every time you relax an edge, 
if the resulting relaxed distance is >= 100, don't relax it, because we can't actually use it.

If you find a negative-weight cycle, don't just output "winnable" right away. 
Make sure that you can actually reach the cycle from the start, 
and make sure that you can actually reach the end from the cycle.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>
using namespace std;

bool bfs(int n, int s, int e, const vector< vector<int> >& rooms)
{
	vector<bool> visited(n, false);
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (i == e)
			return true;
		for (vector<int>::const_iterator j = rooms[i].begin(), k = rooms[i].end(); j != k; ++j)
			if (!visited[*j]) {
				visited[*j] = true;
				q.push(*j);
			}
	}
	return false;
}

bool bellman_ford(int n, const vector<int>& energies, const vector< pair<int, int> >& doors,
	const vector< vector<int> >& rooms)
{
	if (n == 1)
		return true;
	// initialize the graph
	vector<long long> distances(n, numeric_limits<int>::max());
	distances[0] = -100;
	// relax the edges repeatedly
	for (int i = 0; i < n - 1; i++) {
		for (size_t j = 0, e = doors.size(); j < e; j++) {
			const pair<int, int>& d = doors[j];
			if (distances[d.first] + energies[d.first] < min(0LL, distances[d.second]))
				distances[d.second] = distances[d.first] + energies[d.first];
		}
		if (distances[n - 1] < 0)
			return true;
	}
	// check for negative-weight cycles
	for (size_t i = 0, e = doors.size(); i < e; i++) {
		const pair<int, int>& d = doors[i];
		if (distances[d.first] + energies[d.first] < min(0LL, distances[d.second]) &&
			bfs(n, 0, d.first, rooms) && bfs(n, d.second, n - 1, rooms)) // cycle is reachable both from start and to finish
			return true;
	}
	return false;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (n == -1)
			break;
		vector<int> energies(n); // energies[i] is the energy of i-th room
		vector< pair<int, int> > doors(n); // there is a one-way door form doors[].first to doors[].second
		vector< vector<int> > rooms(n);
		for (int i = 0; i < n; i++) {
			int e;
			cin >> e;
			energies[i] = -e;
			int j;
			cin >> j;
			for (int k = 0; k < j; k++) {
				int l;
				cin >> l;
				doors.push_back(make_pair(i, l - 1));
				rooms[i].push_back(l - 1);
			}
		}
		cout << (bellman_ford(n, energies, doors, rooms) ? "winnable\n" : "hopeless\n");
	}
	return 0;
}

