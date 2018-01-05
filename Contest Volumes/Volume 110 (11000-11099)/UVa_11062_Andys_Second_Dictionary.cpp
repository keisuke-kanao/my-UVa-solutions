
/*
	UVa 11062 - Andy's Second Dictionary

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11062_Andys_Second_Dictionary.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

bool not_a_word_char(char c)
{
	return (isalpha(c) || isspace(c) || c == '-') ? false : true;
}

int main()
{
	string line, prefix;
	set<string> dictionary;
	while (getline(cin, line)) {
		if (line.empty())
			continue;
		replace_if(line.begin(), line.end(), not_a_word_char, ' ');
		transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);
		istringstream iss(line);
		string ps, cs;
		while (iss >> cs) {
			if (!prefix.empty()) {
				cs.insert(0, prefix);
				prefix.clear();
			}
			if (!ps.empty())
				dictionary.insert(ps);
			ps = cs;
		}
		if (!prefix.empty())
			dictionary.insert(prefix);
		if (ps[ps.length() - 1] == '-') // a hyphenationed word
			prefix = ps.substr(0, ps.length() - 1);
		else
			dictionary.insert(ps);
	}
	for (set<string>::const_iterator i = dictionary.begin(), e = dictionary.end(); i != e; ++i)
		cout << *i << endl;
	return 0;
}

