
/*
	UVa 10282 - Babelfish

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10282_Babelfish.cpp

	from 22 September 2001 - Waterloo local contest Problem C
		(http://plg1.cs.uwaterloo.ca/~acm00/010922/)
*/

#include <iostream>
#include <string>
#include <string>
#include <sstream>
#include <map>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	map<string, string> dictionary;
	string line;
	while (true) {
		getline(cin, line);
		if (line.empty())
			break;
		istringstream iss(line);
		string word, foreign_word;
		iss >> word >> foreign_word;
		dictionary.insert(make_pair(foreign_word, word));
	}
	map<string, string>::iterator e = dictionary.end();
	while (getline(cin, line)) {
		map<string, string>::iterator i = dictionary.find(line);
		if (i != e)
			cout << i->second << endl;
		else
			cout << "eh\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

