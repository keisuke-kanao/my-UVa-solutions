
/*
	UVa 10672 - Marbles on a tree

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10672_Marbles_on_a_tree.cpp

	from Waterloo ACM Programming Contest, June 12, 2004, Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/040612/data/)
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

void count_marbles(int u, const vector< vector<int> >& children, vector<int>& marbles, vector<bool>& visited)
{
	if (!visited[u]) {
		visited[u] = true;
		const vector<int>& c = children[u];
		for(size_t i = 0, j = c.size(); i < j; i++) {
			count_marbles(c[i], children, marbles, visited);
			marbles[u] += marbles[c[i]];
		}
#ifdef DEBUG
		printf("%d %d\n", u, marbles[u]);
#endif
	}
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		vector< vector<int> > children(n + 1);
		vector<int> marbles(n + 1, 0);
		for (int i = 0; i < n; i++) {
			int v, nr, d;
			scanf("%d %d %d", &v, &nr, &d);
			marbles[v] = nr - 1;
			while (d--) {
				int j;
				scanf("%d", &j);
				children[v].push_back(j);
			}
		}
		vector<bool> visited(n + 1, false);
		for(int i = 1; i <= n; i++)
			count_marbles(i, children, marbles, visited);
		int nr_marbles = 0;
		for(int i = 1; i <= n; i++)
			nr_marbles += abs(marbles[i]);
		printf("%d\n", nr_marbles);
	}
	return 0;
}

