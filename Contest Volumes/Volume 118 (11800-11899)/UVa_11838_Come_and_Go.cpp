
/*
	UVa 11838 - Come and Go

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11838_Come_and_Go.cpp
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int n_max = 2000;
vector <int> edges[n_max + 1]; // edges of directed graph
vector <int> redges[n_max + 1]; // edges of transposed graph
bool visited[n_max + 1];
vector <int> vstack;

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

void dfs2(int i) // depth-first search for the transposed graph
{
	visited[i] = false;
	vector<int>& re = redges[i];
	for (int j = 0; j < re.size(); j++)
		if (visited[re[j]])
			dfs2(re[j]);
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

void dfs2(int i) // depth-first search for the transposed graph
{
	stack<int> st;
	visited[i] = false;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		vector<int>& re = redges[i];
		bool pushed = false;
		for (int j = 0; j < re.size(); j++) {
			int k = re[j];
			if (visited[k]) {
				visited[k] = false;
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
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			redges[i].clear();
			visited[i] = false;
		}
		vstack.clear();
		while (m--) {
			int v, w, p;
			cin >> v >> w >> p;
			edges[v].push_back(w);
			redges[w].push_back(v);
			if (p == 2) {
				edges[w].push_back(v);
				redges[v].push_back(w);
			}
		}
		// calculate number of strongly connected components
		for (int i = 1; i <= n; i++)
			if (!visited[i])
				dfs1(i);
		int nr_scc = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]]) {
				nr_scc++;
                dfs2(vstack[i]);
			}
		cout << ((nr_scc == 1) ? 1 : 0) << endl;
	}
	return 0;
}

