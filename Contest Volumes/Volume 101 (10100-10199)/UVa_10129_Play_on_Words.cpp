
/*
	UVa 10129 - Play on Words

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10129_Play_on_Words.cpp

	An accepted solution.
*/

/*
	This is an Eulerian path (or trail) problem, similar to UVa 10054 Necklace 
	which is a Eulerian curcuit (or cycle) problem.

	Generate an directed unweighted graph where vertices are first/last letters and edges are words.

	A directed graph has an Eulerian trail if and only if 
		at most one vertex has (out-degree) - (in-degree) = 1, 
		at most one vertex has (in-degree) - (out-degree) = 1, 
		every other vertex has equal in-degree and out-degree, 
		and all of its vertices with nonzero degree belong to a single connected component of the underlying undirected graph.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool check_degrees(int n, const vector<int>& in_degrees, const vector<int>& out_degrees)
{
	int start = -1, end = -1;
	for (int i = 0; i < n; i++) {
		int j  = out_degrees[i] - in_degrees[i];
		if (j < -1 || j > 1)
			return false;
		else if (j == -1) {
			if (start != -1)
				return false;
			start = i;
		}
		else if (j == 1) {
			if (end != -1)
				return false;
			end = i;
		}
	}
	return true;
}

void dfs(int n, int i, const vector< vector<bool> >& graph, vector<bool>& visited)
{
	visited[i] = true;
	const vector<bool>& g = graph[i];
	for (int j = 0; j < n; j++)
		if (g[j] && !visited[j])
			dfs(n, j, graph, visited);
}

bool check_connection(int n, const vector<int>& in_degrees, const vector<int>& out_degrees,
	const vector< vector<bool> >& graph)
{
	// do a depth-first-search and see if all of the vertices are connected
	vector<bool> visited(n, false);
	int start;
	for (start = 0; start < n; start++)
		if (in_degrees[start])
			break;
	if (start < n)
		dfs(n, start, graph, visited);
	for (int i = 0; i < n; i++)
		if (in_degrees[i] || out_degrees[i]) {
			if (!visited[i])
				return false;
		}
	return true;
}

int main()
{
	const int nr_letters = 'z' - 'a' + 1;
	int t;
	cin >> t;
	while (t--) {
		int nr_plates;
		cin >> nr_plates;
		vector<int> in_degrees(nr_letters, 0), out_degrees(nr_letters);
		vector< vector<bool> > graph(nr_letters, vector<bool>(nr_letters, false));
			// graph[0 - (nr_letters - 1)] are for first letters, graph[nr_letter - (nr_letters * 2 - 1)] are for last letters
		for (int i = 0; i < nr_plates; i++) {
			string s;
			cin >> s;
			int j = s[0] - 'a', k = s[s.length() - 1] - 'a';
			in_degrees[j]++;
			out_degrees[k]++;
			graph[j][k] = graph[k][j] = true;
		}
		if (check_degrees(nr_letters, in_degrees, out_degrees) &&
			check_connection(nr_letters, in_degrees, out_degrees, graph))
			cout << "Ordering is possible.\n";
		else
			cout << "The door cannot be opened.\n";
	}
	return 0;
}

