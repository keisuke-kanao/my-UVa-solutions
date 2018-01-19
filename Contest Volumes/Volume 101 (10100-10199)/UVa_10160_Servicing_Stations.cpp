
/*
	8.6.4 Servicing Stations
	PC/UVa IDs: 110804/10160, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10160_Servicing_Stations.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

void dominating_set(const vector<int>& vertices,
	int n /* number of vertices */, int iv /* index to the vector of vertices */,
	int v /* number of vertices used so far */, const vector<unsigned long long>& adjacency,
	const vector<unsigned long long>& coverable,
	const unsigned long long all_covered, unsigned long long covered, int& min_covered)
{
	if (min_covered <= v + 1 || iv == n)
		return; // no need to further search
	if ((covered | coverable[iv]) != all_covered)
		return;
	int i = vertices[iv];
	unsigned long long current = static_cast<unsigned long long>(1) << i;
	unsigned long long c = covered | adjacency[i] | current;
	if (c == all_covered) {
#ifdef DEBUG
		cout << "min. number of vertices = " << v + 1 << endl;
#endif
		min_covered = v + 1;
		return;
	}
	dominating_set(vertices, n, iv + 1, v + 1, adjacency, coverable, all_covered, c, min_covered);
	dominating_set(vertices, n, iv + 1, v, adjacency, coverable, all_covered, covered, min_covered);
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n, m;
	while (cin >> n >> m) {
		if (!n && !m)
			break;
		vector<unsigned long long> adjacency(n, 0); // adjacency bitmap of n vertices
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			adjacency[u] |= static_cast<unsigned long long>(1) << v; adjacency[v] |= static_cast<unsigned long long>(1) << u;
		}
		multimap<int, int, greater<int> > degrees; // value is a vertex, key is its degree
		for (int i = 0; i < n; i++) {
			int degree = 0;
			for (int j = 0; j < n; j++)
				if (adjacency[i] & (static_cast<unsigned long long>(1) << j))
					degree++;
			degrees.insert(pair<int, int>(degree, i));
		}
		vector<int> vertices(n); // vector of vertices in descending order of their degrees
		vector<int>::iterator i = vertices.begin();
		for (multimap<int, int, greater<int> >::const_iterator j = degrees.begin(); j != degrees.end(); j++) {
#ifdef DEBUG
			cout << j->first << ' ' << j->second << endl;
#endif
			*i++ = j->second;
		}
#ifdef DEBUG
		cout << endl;
#endif
		vector<unsigned long long> coverable(n);
			// coverable[i] is the bitmap covered by the set of vertices from vertices[i] - vertices[n - 1]
		unsigned long long c = 0;
		for (int iv = n - 1; iv >= 0; iv--) {
			int i = vertices[iv];
			c |= adjacency[i] | (static_cast<unsigned long long>(1) << i);
			coverable[iv] = c;
		}
		unsigned long long all_covered = (static_cast<unsigned long long>(1) << n) - 1, covered = 0;
		int min_covered = n;
		dominating_set(vertices, n, 0, 0, adjacency, coverable, all_covered, covered, min_covered);
		cout << min_covered << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

