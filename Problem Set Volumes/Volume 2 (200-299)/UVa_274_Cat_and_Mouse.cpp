
/*
	UVa 274 - Cat and Mouse

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_274_Cat_and_Mouse.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;

const int infinite = numeric_limits<int>::max();

void floyd_warshall(int n, vector< vector<bool> >& matrix)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			if (matrix[i][k])
				for (int j = 0; j < n; j++)
					matrix[i][j] = matrix[i][j] || matrix[k][j];
}

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int nr_cases;
	iss >> nr_cases;
	getline(cin, s); // skip a blank line
	while (nr_cases--) {
		getline(cin, s);
		istringstream iss(s);
		int n, cat_home, mouse_home;
		iss >> n >> cat_home >> mouse_home;
		cat_home--; mouse_home--;
		vector< vector<bool> > cat(n, vector<bool>(n, false)),
			mouse(n, vector<bool>(n, false)), paths(n, vector<bool>(n, false));
		while (true) {
			getline(cin, s);
			istringstream iss(s);
			int u, v;
			iss >> u >> v;
			if (u == -1)
				break;
			u--; v--;
			cat[u][v] = true;
		}
		while (getline(cin, s) && !s.empty()) {
			istringstream iss(s);
			int u, v;
			iss >> u >> v;
			if (u == -1)
				break;
			u--; v--;
			mouse[u][v] = paths[u][v] = true;
		}
		for (int i = 0; i < n; i++)
			cat[i][i] = mouse[i][i] = true;
		floyd_warshall(n, cat);
		floyd_warshall(n, mouse);
		for (int i = 0; i < n; i++)
			if (cat[cat_home][i])
				for (int j = 0; j < n; j++)
					paths[i][j] = false;
		floyd_warshall(n, paths);
		bool can_meet = false;
		for (int i = 0; i < n; i++)
			if (cat[cat_home][i] && mouse[mouse_home][i]) {
				can_meet = true; break;
			}
		bool can_walk = !cat[cat_home][mouse_home] && paths[mouse_home][mouse_home];
		cout << ((can_meet) ? 'Y' : 'N') << ' ' << ((can_walk) ? 'Y' : 'N') << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

