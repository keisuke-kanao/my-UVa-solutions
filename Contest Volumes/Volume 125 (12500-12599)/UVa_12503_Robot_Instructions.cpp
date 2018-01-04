
/*
	UVa 12503 - Robot Instructions

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12503_Robot_Instructions.cpp
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> instructions(n);
		int p = 0;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			if (s[0] == 'L')
				instructions[i] = -1;
			else if (s[0] == 'R')
				instructions[i] = 1;
			else {
				cin >> s;
				int j;
				cin >> j;
				instructions[i] = instructions[j - 1];
			}
			p += instructions[i];
		}
		cout << p << endl;
	}
	return 0;
}

