
/*
	UVa 12504 - Updating a Dictionary

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12504_Updating_a_Dictionary.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void get_dictionary(const string& s, map<string, string>& dic)
{
	const char* p = s.c_str();
	p++;
	if (*p == '}')
		return;
	while (true) {
		const char* q = p;
		while (*p != ':')
			p++;
		string key = string(q, p - q);
		q = ++p;
		while (*p != ',' && *p != '}')
			p++;
		dic[key] = string(q, p - q);
		if (*p++ == '}')
			break;
	}
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		map<string, string> old_dic, new_dic;
		string s;
		cin >> s;
		get_dictionary(s, old_dic);
		cin >> s;
		get_dictionary(s, new_dic);
		vector<string> added, removed, changed;
		map<string, string>::const_iterator oi = old_dic.begin(), oe = old_dic.end(),
			ni = new_dic.begin(), ne = new_dic.end();
		for ( ; oi != oe && ni != ne; ) {
			if (oi->first < ni->first) {
				removed.push_back(oi->first);
				++oi;
			}
			else if (oi->first > ni->first) {
				added.push_back(ni->first);
				++ni;
			}
			else {
				if (oi->second != ni->second)
					changed.push_back(oi->first);
				++oi; ++ni;
			}
		}
		for ( ; oi != oe; ++oi)
			removed.push_back(oi->first);
		for ( ; ni != ne; ++ni)
			added.push_back(ni->first);
		if (added.empty() && removed.empty() && changed.empty())
			cout << "No changes\n";
		else {
			if (!added.empty()) {
				for (size_t i = 0; i < added.size(); i++)
					cout << ((i) ? ',' : '+') << added[i];
				cout << endl;
			}
			if (!removed.empty()) {
				for (size_t i = 0; i < removed.size(); i++)
					cout << ((i) ? ',' : '-') << removed[i];
				cout << endl;
			}
			if (!changed.empty()) {
				for (size_t i = 0; i < changed.size(); i++)
					cout << ((i) ? ',' : '*') << changed[i];
				cout << endl;
			}
		}
		cout << endl;
	}
	return 0;
}

