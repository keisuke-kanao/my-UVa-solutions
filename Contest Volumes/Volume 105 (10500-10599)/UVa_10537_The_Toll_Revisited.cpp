
/*
	UVa 10537 - The Toll! Revisited

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10537_The_Toll_Revisited.cpp
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdio>
#include <cctype>
using namespace std;

const long long infinite = numeric_limits<long long>::max();

const int nr_letters = 'Z' - 'A' + 1, nr_vertices = nr_letters * 2;

vector<int> edges[nr_vertices];

bool visited[nr_vertices];
long long distances[nr_vertices];
int parents[nr_vertices];

struct distance_comparator {
	bool operator() (int i, int j) const
	{
		return (distances[i] != distances[j]) ? distances[i] < distances[j] : i < j;
	}
};

inline long long get_distance(int u, long long p)
{
	if (u < nr_letters) { // town
		return p + (p + 18) / 19;
/*
		long long q = p / 19, m = p % 19;
		return (m) ? 20 * q + m + 1 : 20 * q;
*/
	}
	else // village
		return p + 1;
}

long long dijkstra_shortest_path(int start, int end, long long p)
{
	for (int i = 0; i < nr_vertices; i++)
		visited[i] = false, distances[i] = infinite;
	set<int, distance_comparator> pq; // priority queue
	distances[start] = p, parents[start] = -1;
	pq.insert(start);
	while(!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		if (u == end)
			break;
		long long d = get_distance(u, distances[u]);
#ifdef DEBUG
		printf("\t%c %lld %lld\n", ((u < nr_letters) ? u + 'A' : u + 'a' - nr_letters), d, w);
#endif
		const vector<int>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i];
			if (!visited[v] && distances[v] > d) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = d, parents[v] = u;
				pq.insert(v);
			}
		}
	}
	return distances[end];
}

inline int get_vertex(char cu)
{
	return (isupper(cu)) ? cu - 'A' : cu - 'a' + nr_letters;
}

int main()
{
	for (int cn = 1; ; cn++) {
		int n;
		cin >> n;
		if (n == -1)
			break;
		for (int i = 0; i < nr_vertices; i++)
			edges[i].clear();
		while (n--) {
			char cu, cv;
			cin >> cu >> cv;
			int u = get_vertex(cu), v = get_vertex(cv);
			edges[u].push_back(v), edges[v].push_back(u);
		}
		long long p;
		char cs, ce;
		cin >> p >> cs >> ce;
		int start = get_vertex(cs), end = get_vertex(ce);
		long long d = dijkstra_shortest_path(end, start, p);
		printf("Case %d:\n%lld\n", cn, d);
		int u = start;
		while (true) {
			putchar((u < nr_letters) ? u + 'A' : u + 'a' - nr_letters);
			if ((u = parents[u]) == -1)
				break;
			putchar('-');
		}
		putchar('\n');
	}
	return 0;
}

