
/*
	UVa 12555 - Baby Me

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12555_Baby_Me.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int T;
	iss >> T;
	for (int t = 1; t <= T; t++) {
		getline(cin, line);
		int a = -1, b = 0;
		for (const char *p = line.c_str(), *q = p; *p; ) {
			if (*p++ < 0) {
				int n = static_cast<int>(strtol(q, NULL, 10));
				if (a == -1) {
					a = n;
					p += 2;
					q = p;
				}
				else {
					b = n;
					break;
				}
			}
		}
		int w = 50 * a + 5 * b;
		cout << "Case " << t << ": ";
		if (w % 10)
			cout << fixed << setprecision(2) << static_cast<double>(w) / 100.0 << endl;
		else if (w % 100)
			cout << fixed << setprecision(1) << static_cast<double>(w) / 100.0 << endl;
		else
			cout << fixed << setprecision(0) << static_cast<double>(w) / 100.0 << endl;
	}
	return 0;
}

