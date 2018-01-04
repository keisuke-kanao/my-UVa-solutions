
/*
	UVa 117 - The Postal Worker Rings Once

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_117_The_Postal_Worker_Rings_Once.cpp

	See Eulerian path - Wikipedia, the free encyclopedia
  	(http://en.wikipedia.org/wiki/Eulerian_path)
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int weight_;

	edge() : u_(-1), v_(-1), weight_(-1) {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}
};

int bellman_ford(int n, int s, int t, const vector<edge>& edges)
{
	// apply the Bellman-Ford's shortest path algorithm
	// initialize the graph
	vector<int> distances(n, numeric_limits<int>::max());
	distances[s] = 0;
	// relax the edges repeatedly
	for (int i = 0; i < n - 1; i++)
		for (size_t j = 0, je = edges.size(); j < je; j++) {
			const edge& e = edges[j];
			long long ld = static_cast<long long>(distances[e.u_]);
			if (ld + e.weight_ < distances[e.v_])
				distances[e.v_] = distances[e.u_] + e.weight_;
		}
	return distances[t];
}

int main()
{
	const int nr_letters = 'z' - 'a' + 1;
	int vertices[nr_letters]; // vertices[i] is the vertex of (i - 'a')
	int degrees[nr_letters]; // degrees[i] is the degree of vertex i
	string s;
	while (cin >> s) {
		for (int i = 0; i < nr_letters; i++) {
			vertices[i] = -1;
			degrees[i] = 0;
		}
		vector<edge> edges;
		int n = 0, shortest_path_length = 0;
		do {
			int i = s[0] - 'a', j = s[s.length() - 1] - 'a';
			int length = s.length();
			if (vertices[i] == -1)
				vertices[i] = n++;
			if (vertices[j] == -1)
				vertices[j] = n++;
			shortest_path_length += length;
			int u = vertices[i], v = vertices[j];
			edges.push_back(edge(u, v, length));
			edges.push_back(edge(v, u, length));
			degrees[u]++; degrees[v]++;
			cin >> s;
		} while (s != "deadend");
		int s = -1, t = -1;
		for (int i = 0; i < n; i++)
			if (degrees[i] & 1) {
				if (s == -1)
					s = i;
				else
					t = i;
			}
/*
	If every vertices of the graph has even degree, Eulerian trails that starting any vertex are Eulerian circuits.
	If there are exactly two vertices of odd degree, all Eulerian trails start at one of them and end at the other.
	There are no graphs that have exactly one vertex of odd degree.
*/
		if (s != -1)
			shortest_path_length += bellman_ford(n, s, t, edges);
		cout << shortest_path_length << endl;
	}
	return 0;
}

