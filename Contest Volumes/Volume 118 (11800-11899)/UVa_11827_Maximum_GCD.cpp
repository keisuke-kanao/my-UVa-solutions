
/*
	UVa 11827 - Maximum GCD

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11827_Maximum_GCD.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	const int m_max = 100;
	vector<int> integers(m_max);
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int n;
	iss >> n;
	iss.clear();
	while (n--) {
		getline(cin, line);
		iss.str(line);
		int i, m = 0;
		while (iss >> i)
			integers[m++] = i;
		iss.clear();
		int g = 0;
		for (int i = 0; i < m - 1; i++)
			for (int j = i + 1; j < m; j++)
				g = max(g, gcd(integers[i], integers[j]));
		cout << g << endl;
	}
	return 0;
}

