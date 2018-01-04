
/*
	UVa 11709 - Trust groups

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11709_Trust_groups.cpp
*/

#include <vector>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int p_max = 1000, nr_name_chars_max = 31;
struct person {
	char name_[nr_name_chars_max + 1];
} persons[p_max];

void dfs1(int i, vector< vector<int> >& edges, vector<bool>& visited, vector<int>& vstack) // depth-first seach for a directed graph
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

void dfs2(int i, vector< vector<int> >& redges, vector<bool>& visited) // depth-first search for the transposed graph
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

int compare_person(const void* p, const void* q)
{
	return strcmp(reinterpret_cast<const person*>(p)->name_, reinterpret_cast<const person*>(q)->name_);
}

int main()
{
	while (true) {
		int p, t;
		scanf("%d %d", &p, &t);
		while (getchar() != '\n') // discard the rest of the line
			;
		if (!p && !t)
			break;
		for (int i = 0; i < p; i++)
			gets(persons[i].name_);
		qsort(persons, p, sizeof(person), compare_person);

		vector < vector<int> > edges(p); // edges of directed graph
		vector < vector<int> > redges(p); // edges of transposed graph
		vector<bool> visited(p, false);
		vector <int> vstack;
		while (t--) {
			person pu, pv;
			gets(pu.name_);
			gets(pv.name_);
			int u = reinterpret_cast<person*>(bsearch(&pu, persons, p, sizeof(person), compare_person)) - persons,
				v = reinterpret_cast<person*>(bsearch(&pv, persons, p, sizeof(person), compare_person)) - persons;
			edges[u].push_back(v);
			redges[v].push_back(u);
		}
		// calculate number of strongly connected components
		for (int i = 0; i < p; i++)
			if (!visited[i])
				dfs1(i, edges, visited, vstack);
		int nr_scc = 0;
		for (int i = vstack.size() - 1; i >= 0; i--)
			if (visited[vstack[i]]) {
				nr_scc++;
                dfs2(vstack[i], redges, visited);
			}
		printf("%d\n", nr_scc);
	}
	return 0;
}

