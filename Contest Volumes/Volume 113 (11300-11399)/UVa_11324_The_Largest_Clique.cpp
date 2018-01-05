
/*
	UVa 11324 - The Largest Clique

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11324_The_Largest_Clique.cpp
*/

/*
Use Dynamic Programming. 

Hint 1: Decomposing a directed graph into its strongly connected components. 
Hint 2: If we merge the vertices in each strong component into a single super vertex, 
  and joint two super vertices (A, B) 
  if and only if there are vertices u is element of A and v is element of B 
  such that (u, v) is element of E, then the resulting digraph, called the component digraph, is necessarily acyclic.
*/

#include <algorithm>
#include <vector>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 1000;
vector<int> edges[n_max + 1]; // edges of directed graph
vector<int> redges[n_max + 1]; // edges of transposed graph
bool visited[n_max + 1];
vector <int> vstack;
int indices[n_max + 1]; // indices[i] is the strongly connected component index of vertex i

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

int scc_vertices[n_max + 1], cliques[n_max + 1];
vector<int> scc_edges[n_max + 1]; // edges of directed graph

int transitive_closure(int u)
{
	if (cliques[u] != -1)
		return cliques[u];
	int c = scc_vertices[u];
	const vector<int>& es = scc_edges[u];
	for (size_t i = 0; i < es.size(); i++)
		c = max(c, transitive_closure(es[i]) + scc_vertices[u]);
	return cliques[u] = c;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n_max; i++) {
			edges[i].clear(), redges[i].clear();
			scc_vertices[i] = 0;
			cliques[i] = -1;
			scc_edges[i].clear();
		}
		vstack.clear();
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			edges[u].push_back(v), redges[v].push_back(u);
		}

		// calculate number of strongly connected components
		for (int i = 1; i <= n; i++)
			if (!visited[i])
				dfs1(i);
		int index = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]])
                dfs2(vstack[i], ++index);
#ifdef DEBUG
		printf("%d\n", index);
		for (int i = 1; i <= n; i++)
			printf("v-%d: s-%d%c", i, indices[i], ((i < n) ? ' ' : '\n'));
#endif
		// count the number of vertices of strongly connected components
		for (int i = 1; i <= n; i++)
			scc_vertices[indices[i]]++;
#ifdef DEBUG
		for (int i = 1; i <= index; i++)
			printf("s-%d: %d%c", i, scc_vertices[i], ((i < index) ? ' ' : '\n'));
#endif
		// create the adjacent matrix of strongly connected components
		for (int i = 1; i <= n; i++) {
			const vector<int>& es = edges[i];
			for (size_t j = 0; j < es.size(); j++) {
				int u = indices[i], v = indices[es[j]];
				if (u != v)
					scc_edges[u].push_back(v);
			}
		}
		int max_clique_size = 0;
		for (int i = 1; i <= index; i++)
			max_clique_size = max(max_clique_size, transitive_closure(i));
		printf("%d\n", max_clique_size);
	}
	return 0;
}

