
/*
	UVa 186 - Trip Routing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_186_Trip_Routing.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cstring>
using namespace std;

int register_city(const string& s, map<string, int>& cities)
{
	pair<map<string, int>::iterator, bool> result = cities.insert(make_pair(s, static_cast<int>(cities.size())));
	return result.first->second;
}

void register_vertex(int i, const string& s, map<int, string>& vertices)
{
	vertices.insert(make_pair(i, s));
}

void register_route(int i, int j, const string& s, map< pair<int, int>, string>& routes)
{
	routes[make_pair(min(i, j), max(i, j))] = s;
}

void floyd_warshall_with_path_reconstruction(int n, vector < vector<int> >& distances, vector <vector<int> >& next)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (distances[i][k] != numeric_limits<int>::max() && distances[k][j] != numeric_limits<int>::max()) {
					int through_k = distances[i][k] + distances[k][j]; // distance through vertex k
 					if (through_k < distances[i][j]) {
						distances[i][j] = through_k; next[i][j] = k;
					}
				}
}

bool get_path(int u, int v, const vector < vector<int> >& distances, const vector <vector<int> >& next,
	vector<int>& path)
{
	if (distances[u][v] == numeric_limits<int>::max())
		return false; // no path between the pair of vertices u and v
	int intermediate = next[u][v];
	if (intermediate == -1) {
		path.push_back(u); path.push_back(v); // there exits a direct edge from u to v, with no vertices between
		return true;
	}
	else {
		if (!get_path(u, intermediate, distances, next, path))
			return false;
		path.pop_back();
		return get_path(intermediate, v, distances, next, path);
	}
}

int main()
{
	const int n_max = 100;
	vector< vector<int> > distances(n_max, vector<int>(n_max, numeric_limits<int>::max()));
	vector< vector<int> > next(n_max, vector<int>(n_max, -1));
	map<string, int> cities;
	map<int, string> vertices;
	map< pair<int, int>, string> routes;

	string line;
	while (true) {
		getline(cin, line);
		if (line.empty())
			break;
		const char* p = line.c_str();
		const char* q = strchr(p, ',');
		string city = line.substr(0, q - p);
		int u = register_city(city, cities);
		register_vertex(u, city, vertices);
		const char* r = q + 1; q = strchr(r, ',');
		city = line.substr(r - p, q - r);
		int v = register_city(city, cities);
		register_vertex(v, city, vertices);
		r = q + 1; q = strchr(r, ',');
		int d = static_cast<int>(strtol(q + 1, NULL, 10));
		if (d < distances[u][v]) {
			register_route(u, v, line.substr(r - p, q - r), routes);
			distances[u][v] = distances[v][u] = d;
		}
	}
	int n = static_cast<int>(cities.size());
	floyd_warshall_with_path_reconstruction(n, distances, next);

	while (getline(cin, line)) {
		const char* p = line.c_str();
		const char* q = strchr(p, ',');
		int u = cities[line.substr(0, q - p)], v = cities[line.substr(q + 1 - p)];
		vector<int> path;
		get_path(u, v, distances, next, path);
		cout << "\n\nFrom                 To                   Route      Miles\n";
		cout << "-------------------- -------------------- ---------- -----\n";
		int distance = 0;
		for (size_t pi = 0, pe = path.size(); pi < pe - 1; pi++) {
			int u = path[pi], v = path[pi + 1];
			cout << left << setfill(' ') << setw(21) << vertices[u] << setw(21) << vertices[v] <<
				setw(11) << routes[make_pair(min(u, v), max(u, v))] << right << setw(5) << distances[u][v] << endl;
			distance += distances[u][v];
		}
		cout << "                                                     -----\n";
		cout << "                                          Total      " << setfill(' ') << setw(5) << distance << endl;
	}
	return 0;
}

