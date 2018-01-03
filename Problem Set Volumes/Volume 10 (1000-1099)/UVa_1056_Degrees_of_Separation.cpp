
/*
	UVa 1056 - Degrees of Separation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1056_Degrees_of_Separation.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	for (int n = 1; ; n++) {
		int P, R;
		cin >> P >> R;
		if (!P)
			break;
		vector< vector<int> > matrix(P, vector<int>(P, P));
		map<string, size_t> names;
		while (R--) {
			string s, t;
			pair<map<string, size_t>::iterator, bool> result;
			cin >> s >> t;
			int i, j;
			result = names.insert(make_pair(s, names.size()));
			i = result.first->second;
			result = names.insert(make_pair(t, names.size()));
			j = result.first->second;
			matrix[i][j] = matrix[j][i] = 1;
		}
		for (int k = 0; k < P; k++)
			for (int i = 0; i < P; i++)
				for (int j = 0; j < P; j++)
					matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
		int min_degrees = 0;
		for (int i = 0; i < P - 1; i++)
			for (int j = i + 1; j < P; j++)
				min_degrees = max(min_degrees, matrix[i][j]);
		cout << "Network " << n << ": ";
		if (min_degrees < P)
			cout << min_degrees << endl << endl;
		else
			cout << "DISCONNECTED\n\n";
	}
	return 0;
}

