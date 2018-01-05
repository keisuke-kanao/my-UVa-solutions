
/*
	UVa 10731 - Test

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10731_Test.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_vertices = 26;
bool edges[nr_vertices][nr_vertices]; // edges of directed graph
bool redges[nr_vertices][nr_vertices]; // edges of transposed graph
bool exists[nr_vertices], visited[nr_vertices];
vector <int> vstack;
int indices[nr_vertices]; // indices[i] is the strongly connected component index of vertex i

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
	while (true) {
		int nr_questions;
		cin >> nr_questions;
		if (!nr_questions)
			break;
		if (printed)
			cout << endl;
		else
			printed = true;
		memset(edges, 0, sizeof(edges));
		memset(redges, 0, sizeof(redges));
		vstack.clear();
		memset(exists, 0, sizeof(exists));
		memset(visited, 0, sizeof(visited));
		while (nr_questions--) {
			const int nr_activities = 5;
			char activities[nr_activities], answer;
			for (int i = 0; i < nr_activities; i++)
				cin >> activities[i];
			cin >> answer;
			for (int i = 0, v = answer - 'A'; i < nr_activities; i++) {
				int u = activities[i] - 'A';
				exists[u] = true;
				edges[u][v] = redges[v][u] = true;
			}
		}
		for (int i = 0; i < nr_vertices; i++)
			if (exists[i] && !visited[i])
				dfs1(nr_vertices, i);
		int index = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]])
                dfs2(nr_vertices, vstack[i], ++index);
		vector< vector<int> > activity_sets;
		for (int i = 1; i <= index; i++) {
			vector<int> as;
			for (int j = 0; j < nr_vertices; j++)
				if (exists[j] && indices[j] == i)
					as.push_back(j);
			sort(as.begin(), as.end());
			activity_sets.push_back(as);
		}
		sort(activity_sets.begin(), activity_sets.end());
		for (int i = 0; i < activity_sets.size(); i++) {
			const vector<int>& as = activity_sets[i];
			for (int j = 0; j < as.size(); j++) {
				if (j)
					cout << ' ';
				cout << static_cast<char>('A' + as[j]);
			}
			cout << endl;
		}
	}
	return 0;
}

