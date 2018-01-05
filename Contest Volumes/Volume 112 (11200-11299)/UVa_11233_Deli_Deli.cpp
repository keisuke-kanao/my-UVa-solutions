
/*
	UVa 11233 - Deli Deli

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11233_Deli_Deli.cpp

	from University of Ulm Local Contest 2007
		(http://www.informatik.uni-ulm.de/acm/Locals/2007/)
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

bool is_end_with(const string&s, const string &t)
{
	size_t slength = s.length(), tlength = t.length();
	if (slength < tlength)
		return false;
	return tlength == 1 && s[slength - 1] == t[0] ||
		tlength == 2 && s[slength - 2] == t[0] && s[slength - 1] == t[1];
}

int main()
{
	int l, n;
	cin >> l >> n;
	string s, t;
	map<string, string> words;
	for (int i = 0; i < l; i++) {
		cin >> s >> t;
		words[s] = t;
	}
	for (int i = 0; i < n; i++) {
		cin >> s;
		map<string, string>::iterator wi = words.find(s);
		if (wi != words.end())
			cout << wi->second << endl;
		else if (is_end_with(s, "y") && s.length() > 1 && s[s.length() - 2] != 'a' &&
			s[s.length() - 2] != 'e' && s[s.length() - 2] != 'i' && s[s.length() - 2] != 'o' && s[s.length() - 2] != 'u')
			cout << s.substr(0, s.length() - 1) << "ies\n";
		else if (is_end_with(s, "o") || is_end_with(s, "s") || is_end_with(s, "ch") ||
			is_end_with(s, "sh") || is_end_with(s, "x"))
			cout << s << "es\n";
		else
			cout << s << "s\n";
	}
	return 0;
}

