
/*
	UVa 762 - We Ship Cheap

	To build using Visual Studio 2008:
		cl -EHsc UVa_762_We_Ship_Cheap.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int register_vertex(const string& s, vector<string>& cities, map<string, int>& vertices)
{
	pair< map<string, int>::iterator, bool> result = vertices.insert(make_pair(s, vertices.size()));
	if (result.second)
		cities.push_back(s);
	return result.first->second;
}

int get_vertex(const string& s, map<string, int>& vertices)
{
	map<string, int>::iterator i = vertices.find(s);
	return (i != vertices.end()) ? i->second : -1;
}

bool bfs(int source, int destination, const vector< vector<int> >& edges, vector<int>& parents)
{
	vector<bool> visited(edges.size(), false);
	queue<int> q;
	visited[source] = true;
	q.push(source);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (i == destination)
			return true;
		const vector<int>& e = edges[i];
		for (int j = 0; j < e.size(); j++) {
			int k = e[j];
			if (!visited[k]) {
				visited[k] = true;
				parents[k] = i;
				q.push(k);
			}
		}
	}
	return false;
}

void print_routes(int i, const vector<int>& parents, const vector<string>& cities)
{
	int p = parents[i];
	if (p != -1) {
		print_routes(p, parents, cities);
		cout << cities[p] << ' ' << cities[i] << endl;
	}
}

int main()
{
	int nr_links;
	bool printed = false;
	while (cin >> nr_links) {
		string s, t;
		vector<string> cities;
		map<string, int> vertices;
		vector< vector<int> > edges;
		while (nr_links--) {
			cin >> s >> t;
			int i = register_vertex(s, cities, vertices), j = register_vertex(t, cities, vertices);
			while (i >= edges.size() || j >= edges.size())
				edges.push_back(vector<int>());
			edges[i].push_back(j);
			edges[j].push_back(i);
		}
		cin >> s >> t;
		if (printed)
			cout << endl;
		else
			printed = true;
		int i = get_vertex(s, vertices), j = get_vertex(t, vertices);
		bool result = false;
		if (i != -1 && j != -1) {
			if (i == j) {
				result = true;
				cout << s << ' ' << s << endl;
			}
			else {
				vector<int> parents(edges.size(), -1);
				if (result = bfs(i, j, edges, parents))
					print_routes(j, parents, cities);
			}
		}
		else if (s == t)
			result = true;
		if (!result)
			cout << "No route\n";
	}
	return 0;
}

