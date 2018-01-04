
/*
	UVa 11492 - Babel

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11492_Babel.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>
using namespace std;

const int nr_letters = 26;

struct edge {
	int v_;
	int w_;
	int c_;
	edge(int v, int w, char c) : v_(v), w_(w), c_(c) {}
};

int dijkstra_shortest_path(int n, int s, int e, const vector< vector<edge> >& edges)
{
	vector< vector<int> > distances(n, vector<int>(nr_letters + 1, numeric_limits<int>::max()));
	vector< vector<bool> > in_queue(n, vector<bool>(nr_letters + 1, false));
	distances[s][0] = 0;
	queue <pair<int, int> > q;
	q.push(make_pair(s, 0));
	while(!q.empty()) {
		pair<int, int> u = q.front();
		q.pop();
		in_queue[u.first][u.second] = false;
		int d = distances[u.first][u.second];
		const vector<edge>& es = edges[u.first];
		for (size_t i = 0; i < es.size(); i++) {
			const edge& e = es[i];
			if (e.c_ != u.second && distances[e.v_][e.c_] > d + e.w_) {
				distances[e.v_][e.c_] = d + e.w_;
				if (!in_queue[e.v_][e.c_]) {
					in_queue[e.v_][e.c_] = true;
					q.push(make_pair(e.v_, e.c_));
				}
			}
		}
	}
	int min_d = numeric_limits<int>::max();
	for (int i = 0; i <= nr_letters; i++)
		min_d = min(min_d, distances[e][i]);
	return min_d;
}

int register_language(const string &s, map<string, int>& languages)
{
	pair<map<string, int>::iterator, bool> result =
		languages.insert(make_pair(s, static_cast<int>(languages.size())));
	return result.first->second;
}

int main()
{
	while (true) {
		int m;
		cin >> m;
		if (!m)
			break;
		map<string, int> languages;
		string sl, el;
		cin >> sl >> el;
		int sv = register_language(sl, languages),
			ev = register_language(el, languages);
		vector< vector<edge> > edges;
		while (m--) {
			string su, sv, se;
			cin >> su >> sv >> se;
			int u = register_language(su, languages),
				v = register_language(sv, languages);
			while (edges.size() <= u || edges.size() <= v)
				edges.push_back(vector<edge>());
			edges[u].push_back(edge(v, se.length(), se[0] - 'a' + 1));
			edges[v].push_back(edge(u, se.length(), se[0] - 'a' + 1));
		}
		int min_d = dijkstra_shortest_path(edges.size(), sv, ev, edges);
		if (min_d != numeric_limits<int>::max())
			cout << min_d << endl;
		else
			cout << "impossivel\n";
	}
	return 0;
}

