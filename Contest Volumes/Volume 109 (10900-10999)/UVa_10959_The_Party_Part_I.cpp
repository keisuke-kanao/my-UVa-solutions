
/*
	UVa 10959 - The Party, Part I

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10959_The_Party_Part_I.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(const vector< vector<int> >& adjacency_list, vector<int>& numbers)
{
	queue<int> q;
	numbers[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		int n = numbers[u] + 1;
		const vector<int>& al = adjacency_list[u];
		for (size_t i = 0, j = al.size(); i < j; i++) {
			int v = al[i];
			if (numbers[v] == -1) {
				numbers[v] = n;
				q.push(v);
			}
		}
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int p, d;
		cin >> p >> d;
		vector< vector<int> > adjacency_list(p);
		while (d--) {
			int i, j;
			cin >> i >> j;
			adjacency_list[i].push_back(j);
			adjacency_list[j].push_back(i);
		}
		vector<int> numbers(p, -1); // Giovanni numbers
		bfs(adjacency_list, numbers);
		for (int i = 1; i < p; i++)
			cout << numbers[i] << endl;
		if (t)
			cout << endl;
	}
	return 0;
}

