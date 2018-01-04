
/*
	UVa 455 - Periodic Strings

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_455_Periodic_Strings.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int n;
	iss >> n;
	while (n--) {
		getline(cin, s); // skip a blank line
		getline(cin, s);
		int i, j, k, length = s.length();
		for (k = 1; k < length; k++) {
			if (length % k)
				continue;
			for (i = 0; i < k; i++) {
				char c = s[i];
				for (j = i + k; j < length; j += k)
					if (s[j] != c)
						break;
				if (j < length)
					break;
			}
			if (i == k)
				break;
		}
		cout << k << endl;
		if (n)
			cout << endl;
	}
	return 0;
}

