
/*
	UVa 825 - Walking on the Safe Side

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_825_Walking_on_the_Safe_Side.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*
	Let isections[i][j] be the intersections of i-th street from north and j-th street from west, and
	p[i][j] be the number of different paths from the park to the isections[i][j], then:
		p[i][j] = p[i - 1][j] + p[i][j - 1] if both isections[i - 1][j] and isections[i][j - 1] are safe
				= p[i - 1][j]				if only isections[i - 1][j] is safe
				= p[i][j - 1]				if only isections[i][j - 1] is safe
*/

int count_paths(int w, int n, const vector< vector<bool> >& isections)
{
	int i, j;
	vector< vector<int> > p(w + 1, vector<int>(n + 1, 0));
	p[1][1] = 1;
	for (int i = 2; i <= w; i++)
		if (!isections[i][1])
			p[i][1] = p[i - 1][1];
	for (int j = 2; j <= n; j++)
		if (!isections[1][j])
			p[1][j] = p[1][j - 1];
	for (int i = 2; i <= w; i++)
		for (int j = 2; j <= n; j++)
			if (!isections[i][j])
				p[i][j] += p[i - 1][j] + p[i][j - 1];
	return p[w][n];
}

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	while (nr_cases--) {
		getline(cin, line); // skip a blank line
		getline(cin, line);
		iss.str(line);
		int w, n;
		iss >> w >> n;
		iss.clear();
		vector< vector<bool> > isections(w + 1, vector<bool>(n + 1, false));
			// isections[i][j] is true if the intersection of i-th street from north and j-th street from west is unsafe
		for (int i = 0; i < w; i++) {
			getline(cin, line);
			iss.str(line);
			int j, k;
			iss >> j;
			while (iss >> k)
				isections[j][k] = true;
			iss.clear();
		}
		cout << ((!isections[1][1]) ? count_paths(w, n, isections) : 0) << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

