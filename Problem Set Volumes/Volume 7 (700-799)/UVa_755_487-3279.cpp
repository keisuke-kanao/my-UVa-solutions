
/*
	UVa 755 - 487-3279

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_755_487-3279.cpp

	from 1999 ACM East Central Programming Contest Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1999/index.html)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	const int letters[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
	string line;
	istringstream iss(line);
	getline(cin, line);
	iss.str(line);
	int s;
	iss >> s;
	iss.clear();
	while (s--) {
		getline(cin, line); // skip a blank line
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		map<int, int> tns;
			// key is a telephone number, value is its number of occurrences
		for (int i = 0; i < n; i++) {
			getline(cin, line);
			int tn = 0, j = 0;
			for (const char* p = line.c_str(); *p && j < 7; p++)
				if (isalnum(*p)) {
					if (j++)
						tn *= 10;
					if (isdigit(*p))
						tn += *p - '0';
					else
						tn += letters[*p - 'A'];
				}
			map<int, int>::iterator k = tns.find(tn);
			if (k == tns.end())
				tns.insert(make_pair(tn, 1));
			else
				k->second++;
		}
		bool duplicates = false;
		for (map<int, int>::const_iterator i = tns.begin(), e = tns.end(); i != e; ++i)
			if (i->second > 1) {
				duplicates = true;
				cout << setfill('0') << setw(3) << i->first / 10000 << '-' << setw(4) << i->first % 10000 <<
					' ' << i->second << endl;
			}
		if (!duplicates)
			cout << "No duplicates.\n";
		if (s)
			cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

