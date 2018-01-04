
/*
	UVa 247 - Calling Circles

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_247_Calling_Circles.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cstring>
using namespace std;

const int n_max = 25;
bool edges[n_max][n_max]; // edges of directed graph
bool redges[n_max][n_max]; // edges of transposed graph
bool visited[n_max];
vector <int> vstack;
int indices[n_max]; // indices[i] is the strongly connected component index of vertex i

int get_vertex(const string& s, map<string, int>& vertices, map<int, string>& names)
{
	int v = static_cast<int>(vertices.size());
	pair<map<string, int>::iterator, bool> result = vertices.insert(make_pair(s, v));
	if (result.second)
		names.insert(make_pair(v, s));
	return result.first->second;
}

#ifdef __RECURSION__
void dfs1(int n, int i) // depth-first seach for a directed graph
{
	visited[i] = true;
	for (int j = 0; j < n; j++)
		if (edges[i][j] && !visited[j])
			dfs1(n, j);
	vstack.push_back(i);
}

void dfs2(int n, int i, int index) // depth-first search for the transposed graph
{
	visited[i] = false;
	indices[i] = index;
	for (int j = 0; j < n; j++)
		if (redges[i][j] && visited[j])
			dfs2(n, j, index);
}
#else
void dfs1(int n, int i) // depth-first seach for a directed graph
{
	stack<int> st;
	visited[i] = true;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		bool pushed = false;
		for (int j = 0; j < n; j++) {
			if (edges[i][j] && !visited[j]) {
				visited[j] = true;
				st.push(j);
				pushed = true;
			}
			if (pushed)
				break;
		}
		if (!pushed) {
			st.pop();
			vstack.push_back(i);
		}
	}
}

void dfs2(int n, int i, int index) // depth-first search for the transposed graph
{
	stack<int> st;
	visited[i] = false;
	indices[i] = index;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		bool pushed = false;
		for (int j = 0; j < n; j++) {
			if (redges[i][j] && visited[j]) {
				visited[j] = false;
				indices[j] = index;
				st.push(j);
				pushed = true;
			}
			if (pushed)
				break;
		}
		if (!pushed)
			st.pop();
	}
}
#endif

int main()
{
	bool printed = false;
	for (int ds = 1; ; ds++) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		if (printed)
			cout << endl;
		else
			printed = true;
		map<string, int> vertices;
		map<int, string> names;
		memset(edges, 0, sizeof(edges));
		memset(redges, 0, sizeof(redges));
		vstack.clear();
		memset(visited, 0, sizeof(visited));
		while (m--) {
			string s, t;
			cin >> s >> t;
			int u = get_vertex(s, vertices, names), v = get_vertex(t, vertices, names);
			edges[u][v] = redges[v][u] = true;
		}
		for (int i = 0; i < n; i++)
			if (!visited[i])
				dfs1(n, i);
		int index = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]])
                dfs2(n, vstack[i], ++index);
		cout << "Calling circles for data set " << ds << ":\n";
		for (int i = 1; i <= index; i++) {
			bool indices_printed = false;
			for (int j = 0; j < n; j++)
				if (indices[j] == i) {
					if (indices_printed)
						cout << ", ";
					else
						indices_printed = true;
					cout << names[j];
				}
			cout << endl;
		}
	}
	return 0;
}

