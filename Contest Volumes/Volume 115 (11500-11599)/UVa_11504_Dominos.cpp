
/*
	UVa 11504 - Dominos

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11504_Dominos.cpp
*/

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

const int n_max = 100000;
vector <int> edges[n_max + 1]; // edges of directed graph
vector <int> redges[n_max + 1]; // edges of transposed graph
bool visited[n_max + 1];
vector <int> vstack;
int indices[n_max + 1]; // indices[i] is the strongly connected component index of vertex i
int in_edges[n_max + 1]; // in_edges[i] is the number of edges from outside of the strongly connected component of i

#ifdef __RECURSION__
void dfs1(int i) // depth-first seach for a directed graph
{
	visited[i] = true;
	vector<int>& e = edges[i];
	for (int j = 0; j < e.size(); j++)
		if (!visited[e[j]])
			dfs1(e[j]);
	vstack.push_back(i);
}

void dfs2(int i, int index) // depth-first search for the transposed graph
{
	visited[i] = false;
	indices[i] = index;
	vector<int>& re = redges[i];
	for (int j = 0; j < re.size(); j++)
		if (visited[re[j]])
			dfs2(re[j], index);
}
#else
void dfs1(int i) // depth-first seach for a directed graph
{
	stack<int> st;
	visited[i] = true;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		vector<int>& e = edges[i];
		bool pushed = false;
		for (int j = 0; j < e.size(); j++) {
			int k = e[j];
			if (!visited[k]) {
				visited[k] = true;
				st.push(k);
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

void dfs2(int i, int index) // depth-first search for the transposed graph
{
	stack<int> st;
	visited[i] = false;
	indices[i] = index;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		vector<int>& re = redges[i];
		bool pushed = false;
		for (int j = 0; j < re.size(); j++) {
			int k = re[j];
			if (visited[k]) {
				visited[k] = false;
				indices[k] = index;
				st.push(k);
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
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;

		for (int i = 1; i <= n_max; i++) {
			edges[i].clear ();
			redges[i].clear ();
		}
		vstack.clear();
		memset(visited, false, sizeof(visited));
		memset(in_edges, 0, sizeof(in_edges));

		for (int i = 0; i < m; i++) {
			int x, y;
			cin >> x >> y;
			edges[x].push_back(y);
			redges[y].push_back(x);
		}
		for (int i = 1; i <= n; i++)
			if (!visited[i])
				dfs1(i);
		int index = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]])
                dfs2(vstack[i], ++index);
		for (int i = 1; i <= n; i++) {
			vector<int>& e = edges[i];
			for (int j = 0; j < e.size(); j++) {
				int k = e[j];
				if (indices[i] != indices[k])
					in_edges[indices[k]]++;
			}
		}
		int nr = 0;
		for (int i = 1; i <= index; i++)
			if (!in_edges[i])
				nr++;
		cout << nr << endl;
	}
	return 0;
}

