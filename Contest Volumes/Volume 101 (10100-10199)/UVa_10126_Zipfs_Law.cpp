
/*
	UVa 10126 - Zipf's Law

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10126_Zipfs_Law.cpp

	from Waterloo - Alberta Programming Contest, June 2, 2001, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/010602/data/)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

int main ()
{
	string line;
	istringstream iss;

	bool printed = false;
	while (getline(cin, line)) {
		if (printed)
			cout << endl;
		else
			printed = true;
		istringstream iss(line);
		int n;
		iss >> n;
		map<string, int> words;
		while (true) {
			getline(cin, line);
			if (line == "EndOfText")
				break;
			transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);
			for (const char* p =  line.c_str(); *p; ) {
				for ( ; *p && !isalpha(*p); p++)
					;
				const char* q = p;
				for ( ; *p && isalpha(*p); p++)
					;
				if (p - q) {
					pair<map<string, int>::iterator, bool> result = words.insert(make_pair(string(q, p - q), 1));
					if (!result.second)
						result.first->second++;
				}
			}
		}
		bool found = false;
		for (map<string, int>::const_iterator i = words.begin(), e = words.end(); i != e; ++i)
			if (i->second == n) {
				found = true;
				cout << i->first << endl;
			}
		if (!found)
			cout << "There is no such word.\n";
	}
	return 0;
}

