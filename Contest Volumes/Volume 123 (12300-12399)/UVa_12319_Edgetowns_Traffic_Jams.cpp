
/*
	UVa 12319 - Edgetown's Traffic Jams

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12319_Edgetowns_Traffic_Jams.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;

void floyd_warshall(int n, vector< vector<int> >& matrix)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			if (matrix[i][k] != numeric_limits<int>::max())
				for (int j = 1; j <= n; j++)
					if (matrix[k][j] != numeric_limits<int>::max())
						matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	while (true) {
		string s;
		getline(cin, s);
		istringstream iss(s);
		int n;
		iss >> n;
		iss.clear();
		if (!n)
			break;
		vector< vector<int> > matrix(n + 1, vector<int>(n + 1, numeric_limits<int>::max())),
			pmatrix(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));
		for (int i = 0; i < n; i++) {
			getline(cin, s);
			iss.str(s);
			int j, k;
			iss >> j;
			while (iss >> k)
				matrix[j][k] = 1;
			iss.clear();
		}
		for (int i = 0; i < n; i++) {
			getline(cin, s);
			iss.str(s);
			int j, k;
			iss >> j;
			while (iss >> k)
				pmatrix[j][k] = 1;
			iss.clear();
		}
		int A, B;
		getline(cin, s);
		iss.str(s);
		iss >> A >> B;
		iss.clear();
		floyd_warshall(n, matrix);
		floyd_warshall(n, pmatrix);
		bool yes = true;
		for (int i = 1; i <= n && yes; i++)
			for (int j = 1; j <= n && yes; j++)
				if (i != j)
					if (matrix[i][j] < numeric_limits<int>::max()) {
						if (pmatrix[i][j] == numeric_limits<int>::max() ||
							pmatrix[i][j] > matrix[i][j] * A + B)
							yes = false;
					}
		cout << ((yes) ? "Yes\n" : "No\n");
	}
	return 0;
}

