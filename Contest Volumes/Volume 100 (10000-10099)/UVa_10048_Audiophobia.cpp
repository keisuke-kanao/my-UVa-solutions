
/*
	UVa 10048 - Audiophobia

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10048_Audiophobia.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

void floyd(int n, vector< vector<int> >& matrix) // the minmax Floyd-Warshall algorithm
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], max(matrix[i][k], matrix[k][j]));
}

int main(int /* argc */, char** /* argv */)
{
	for (int t = 1; ; t++) {
		int n /* number of crossings */, s /* number of streets */, q /* number of queries */;
		cin >> n >> s >> q;
		if (!n && !s && !q)
			break;
		vector< vector<int> > matrix(n, vector<int>(n, numeric_limits<int>::max()));
		for (int i = 0; i < n; i++)
			matrix[i][i] = 0;
		for (int i = 0; i < s; i++) {
			int c1, c2, d;
			cin >> c1 >> c2 >> d;
			c1--; c2--;
			matrix[c1][c2] = matrix[c2][c1] = d;
		}
		floyd(n, matrix); // the minmax Floyd-Warshall algorithm
		if (t > 1)
			cout << endl;
		cout << "Case #" << t << endl;
		for (int i = 0; i < q; i++) {
			int c1, c2;
			cin >> c1 >> c2;
			c1--; c2--;
			if (matrix[c1][c2] == numeric_limits<int>::max())
				cout << "no path\n";
			else
				cout << matrix[c1][c2] << endl;
		}
	}
	return 0;
}

