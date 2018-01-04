
/*
	UVa 11586 - Train Tracks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11586_Train_Tracks.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int t;
	iss >> t;
	iss.clear();
	while (t--) {
		getline(cin, line);
		iss.str(line);
		string s;
		int n = 0, m = 0, f = 0;
		while (iss >> s) {
			n++;
			if (s[0] == 'M')
				m++;
			else
				f++;
			if (s[1] == 'M')
				m++;
			else
				f++;
		}
		iss.clear();
		cout << ((n > 1 && m == f) ? "LOOP\n" : "NO LOOP\n");
	}
	return 0;
}

