
/*
	UVa 1174 - IP-TV

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1174_IP-TV.cpp
*/

#include <vector>
#include <map>
#include <queue>
#include <set>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 15;

struct city {
	char s_[nr_chars_max + 1];

	city() {}
	city(const char* s) {strcpy(s_, s);}
	bool operator<(const city& c) const {return strcmp(s_, c.s_) < 0;}
};

int register_city(const char* s, map<city, int>& cities)
{
	pair<map<city, int>::iterator, bool> result = cities.insert(make_pair(city(s), static_cast<int>(cities.size())));
	return result.first->second;
}

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

struct distance_comparator {
	const vector<int>& distances_;

	distance_comparator(const vector<int>& distances) : distances_(distances) {}
	bool operator() (int i, int j) const
	{
		return (distances_[i] != distances_[j]) ? distances_[i] < distances_[j] : i < j;
	}
};

int mst_prim(int n, const vector< vector<edge> >& edges)
{
	vector<bool> visited(n, false);
	vector<int> distances(n, numeric_limits<int>::max());
	distances[0] = 0;
	int mst_distance = 0;
	set<int, distance_comparator> pq(distances); // priority queue
	pq.insert(0);
	while (!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		mst_distance += distances[u];
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_, w = es[i].w_;
			if (!visited[v] && w < distances[v]) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = w;
				pq.insert(v);
			}
		}
	}
	return mst_distance;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int M, N;
		scanf("%d %d", &M, &N);
		map<city, int> cities;
		vector< vector<edge> > edges(M);
		while (N--) {
			char B[nr_chars_max + 1], E[nr_chars_max + 1];
			int C;
			scanf("%s %s %d", B, E, &C);
			int u = register_city(B, cities), v = register_city(E, cities);
			edges[u].push_back(edge(v, C));
			edges[v].push_back(edge(u, C));
		}
		printf("%d\n", mst_prim(M, edges));
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

