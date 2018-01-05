
/*
	UVa 10295 - Hay Points

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10295_Hay_Points.cpp

	from Waterloo local contest 1 June, 2002 Problem A
		(http://acm.student.cs.uwaterloo.ca/~acm00/020601/data/)
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	map<string, int> words;
	for (int i = 0; i < m; i++) {
		pair<string, int> w;
		cin >> w.first >> w.second;
		words.insert(w);
	}
	for (int i = 0; i < n; i++) {
		int hay_point = 0;
		while (true) {
			string s;
			cin >> s;
			if (s == ".")
				break;
			map<string, int>::const_iterator i = words.find(s);
			if (i != words.end())
				hay_point += i->second;
		}
		cout << hay_point << endl;
	}
	return 0;
}

