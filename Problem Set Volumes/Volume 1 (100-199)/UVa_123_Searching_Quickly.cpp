
/*
	UVa 123 - Searching Quickly

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_123_Searching_Quickly.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

int main()
{
	set<string> words_to_ignore;
	while (true) {
		string s;
		cin >> s;
		if (s == "::")
			break;
		words_to_ignore.insert(s);
	}
	int nr_titles = 0;
	vector<string> titles;
	multimap< string, pair<int, int> > words;
		// key is a word in a titile, 
		// and its values are pair of an index to the vector of titles and its position in a title
	string t;
	while (getline(cin, t)) {
		transform(t.begin(), t.end(), t.begin(), (int(*)(int))tolower);
		const char* p = t.c_str();
		for (const char* q = p; *q; ) {
			while (*q == ' ')
				q++;
			const char* r = q;
			while (*r && *r != ' ')
				r++;
			string w(q, r - q);
			set<string>::iterator i = words_to_ignore.find(w);
			if (i == words_to_ignore.end())
				words.insert(make_pair(w, make_pair(nr_titles, q - p)));
			q = r;
		}
		titles.push_back(t);
		nr_titles++;
	}
	for (multimap< string, pair<int, int> >::const_iterator i = words.begin(), e = words.end(); i != e; ++i) {
		int length = i->first.length();
		pair<int, int> p = i->second;
		string t(titles[p.first]);
		// convert the keyword to upper-case letters
		string::iterator j = t.begin(), k = t.begin();
		advance(j, p.second);
		advance(k, p.second + length);
		transform(j, k, j, (int(*)(int))toupper);
/*
		string w = t.substr(p.second, length);
		transform(w.begin(), w.end(), w.begin(), (int(*)(int))toupper);
		t.replace(p.second, length, w);
*/
		cout << t << endl;
	}
	return 0;
}

