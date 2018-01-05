
/*
	UVa 11220 - Decoding the message.

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11220_Decoding_the_message.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int t;
	iss >> t;
	iss.clear();
	getline(cin, line); // skip a blank line
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		cout << "Case #" << case_nr << ":\n";
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			int i = 0;
			string s;
			while (iss >> s)
				if (i < s.length()) {
					cout << s[i];
					i++;
				}
			iss.clear();
			cout << endl;
		}
		if (case_nr < t)
			cout << endl;
	}
	return 0;
}

