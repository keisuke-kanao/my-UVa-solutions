
/*
	UVa 523 - Minimum Transport Cost

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_523_Minimum_Transport_Cost.cpp
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int M;
	iss >> M;
	iss.clear();
	getline(cin, line);
	while (M--) {
		vector< vector<int> > matrix;
		getline(cin, line);
		iss.str(line);
		matrix.push_back(vector<int>());
		int n = 0, c;
		while (iss >> c) {
			matrix[0].push_back((c != -1) ? c : numeric_limits<int>::max());
			n++;
		}
		iss.clear();
		for (int i = 1; i < n; i++) {
			matrix.push_back(vector<int>());
			getline(cin, line);
			iss.str(line);
			while (iss >> c)
				matrix[i].push_back((c != -1) ? c : numeric_limits<int>::max());
			iss.clear();
		}
		vector<int> taxes(n);
		getline(cin, line);
		iss.str(line);
		for (int i = 0; i < n; i++) {
			iss >> c;
			taxes[i] = c;
		}
		iss.clear();
		vector< vector<int> > nexts(n, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				nexts[i][j] = j;
		// apply the Floyd-Warshall algorithm
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				if (matrix[i][k] != numeric_limits<int>::max())
					for (int j = 0; j < n; j++)
						if (matrix[k][j] != numeric_limits<int>::max() &&
							matrix[i][j] > matrix[i][k] + taxes[k] + matrix[k][j]) {
							matrix[i][j] = matrix[i][k] + taxes[k] + matrix[k][j];
							nexts[i][j] = nexts[i][k];
						}
		bool printed = false;
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			int s, e;
			iss >> s >> e;
			iss.clear();
			if (printed)
				cout << endl;
			else
				printed = true;
			cout << "From " << s << " to " << e << " :\n";
			s--, e--;
			cout << "Path: " << s + 1;
//			if (s != e) {
				int u = s;
				do {
					u = nexts[u][e];
					cout << "-->" << u + 1;
				} while (u != e);
//			}
			cout << endl;
			cout << "Total cost : " << matrix[s][e] << endl;
		}
		if (M)
			cout << endl;
	}
	return 0;
}

