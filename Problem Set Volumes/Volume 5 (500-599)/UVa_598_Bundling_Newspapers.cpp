
/*
	UVa 598 - Bundling Newspapers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_598_Bundling_Newspapers.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void print_newspapers(int n, int ni, int ns, int si, const vector<string>& newspapers, vector<bool>& subsets)
{
	if (si == ns) {
		bool printed = false;
		for (int i = 0; i < n; i++)
			if (subsets[i]) {
				if (printed)
					cout << ", ";
				else
					printed = true;
				cout << newspapers[i];
			}
		cout << endl;
	}
	else if (n - ni >= ns - si) {
		subsets[ni] = true;
		print_newspapers(n, ni + 1, ns, si + 1, newspapers, subsets);
		subsets[ni] = false;
		print_newspapers(n, ni + 1, ns, si, newspapers, subsets);
	}
}

int main()
{
	const int n_max = 12;
	string s;
	istringstream iss;
	getline(cin, s);
	iss.str(s);
	int m;
	iss >> m;
	iss.clear();
	getline(cin, s);
	while (m--) {
		getline(cin, s);
		int a = -1, b = -1;
		if (s[0] == '*') {
			a = 1;
		}
		else {
			iss.str(s);
			iss >> a >> b;
			iss.clear();
			if (b == -1)
				b = a;
		}
		int n = 0;
		vector<string> newspapers(n_max);
		while (getline(cin, s) && !s.empty())
			newspapers[n++] = s;
		if (b == -1)
			b = n;
		for (int ns = a; ns <= b; ns++) {
			cout << "Size " << ns << endl;
			vector<bool> subsets(n, false);
			print_newspapers(n, 0, ns, 0, newspapers, subsets);
			cout << endl;
		}
		if (m)
			cout << endl;
	}
	return 0;
}

