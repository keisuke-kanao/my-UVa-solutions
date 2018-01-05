
/*
	UVa 11060 - Beverages

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11060_Beverages.cpps
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

void topological_sort(int n, const vector< vector<int> >& adjacency_list, vector<int>& sorted_list)
{
	vector<int> in_degrees(n, 0);
	for (int i = 0; i < n; i++) {
		const vector<int>& l = adjacency_list[i];
		for (size_t j = 0, e = l.size(); j < e; j++)
			in_degrees[l[j]]++;
	}
	priority_queue< int, vector<int>, greater<int> > q;
	for (int i = 0; i < n; i++)
		if (!in_degrees[i])
			q.push(i);
	while (!q.empty()) {
		int i = q.top(); q.pop();
		sorted_list.push_back(i);
		const vector<int>& l = adjacency_list[i];
		for (size_t j = 0, e = l.size(); j < e; j++) {
			int k = l[j];
			if (!--in_degrees[k])
				q.push(k);
		}
	}
}

int main()
{
	int n;
	for (int case_nr = 1; cin >> n; case_nr++) {
		map<string, int> vertices;
		map<int, string> beverages;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			vertices.insert(make_pair(s, i));
			beverages.insert(make_pair(i, s));
		}
		vector< vector<int> > adjacency_list(n);
		int m;
		cin >> m;
		while (m--) {
			string s, t;
			cin >> s >> t;
			adjacency_list[vertices[s]].push_back(vertices[t]);
		}
		vector<int> sorted_list;
		topological_sort(n, adjacency_list, sorted_list);
		cout << "Case #" << case_nr <<": Dilbert should drink beverages in this order:";
		for (vector<int>::const_iterator si = sorted_list.begin(), se = sorted_list.end(); si != se; ++si)
			cout << ' ' << beverages[*si];
		cout << ".\n\n";
	}
	return 0;
}

