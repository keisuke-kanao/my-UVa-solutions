
/*
	UVa 10887 - Concatenation of Languages

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10887_Concatenation_of_Languages.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

long long convert_to_ll(const string& s)
{
	long long ll = 0;
	for (int i = 0, j = s.length(); i < j; i++)
		ll |= static_cast<long long>(s[i] - 'a' + 1) << (i * 5);
	return ll;
}

pair<long long, long long> concatenate_to_ll(const pair<int, long long>& s, const string& t)
{
	long long ll = 0;
	int i = 0, j = min(10 - s.first, static_cast<int>(t.length()));
	for ( ; i < j; i++)
		ll |= static_cast<long long>(t[i] - 'a' + 1) << (i * 5);
	long long hl = 0;
	for (j = 0; i < t.length(); i++, j++)
		hl |= static_cast<long long>(t[i] - 'a' + 1) << (j * 5);
	return make_pair(s.second | (ll << (s.first * 5)), hl);
}

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int t;
	iss >> t;
	iss.clear();
	for (int c = 0; c < t; c++) {
		getline(cin, s);
		iss.str(s);
		int m, n;
		iss >> m >> n;
		iss.clear();
		vector< pair<int, long long> > vs(m);
		for (int i = 0; i < m; i++) {
			getline(cin, s);
			vs[i] = make_pair(s.length(), convert_to_ll(s));
		}
		set< pair<long long, long long> > ss;
		for (int i = 0; i < n; i++) {
			getline(cin, s);
			for (int j = 0; j < m; j++)
				ss.insert(concatenate_to_ll(vs[j], s));
		}
		cout << "Case " << c + 1 << ": " << ss.size() << endl;
	}
	return 0;
}

