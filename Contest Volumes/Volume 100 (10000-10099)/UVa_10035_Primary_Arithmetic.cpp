
/*
	5.9.1 Primary Arithmetic
	PC/UVa IDs: 110501/10035, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10035_Primary_Arithmetic.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	string n, m;
	while (cin >> n >> m) {
		if (n == "0" && m == "0")
			break;
		int nc = 0 /* number of carries */, c = 0 /* carry from previous digits */;
		for (int i = n.length() - 1, j = m.length() - 1; i >= 0 || j >= 0; i--, j--) {
			int k = (i >= 0) ? n[i] - '0' : 0;
			int l = (j >= 0) ? m[j] - '0' : 0;
			if (k + l + c >= 10) {
				c = 1; nc++;
			}
			else
				c = 0;
		}
		if (nc)
			cout << nc << " carry " << ((nc > 1) ? "operations.\n" : "operation.\n");
		else
			cout << "No carry operation.\n";
	}
	return 0;
}

