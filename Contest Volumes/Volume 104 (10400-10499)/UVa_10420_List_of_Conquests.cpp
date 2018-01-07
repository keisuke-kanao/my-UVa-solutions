
/*
	UVa 10420 - List of Conquests

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10420_List_of_Conquests.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main()
{
	string line;
	istringstream iss(line);
	getline(cin, line);
	iss.str(line);
	int n;
	iss >> n;
	iss.clear();
	map<string, int> countries;
		// key is a country name, value is the number of womens Giovanni loved in the country
	while (n--) {
		getline(cin, line);
		iss.str(line);
		string country;
		iss >> country;
		iss.clear();
		map<string, int>::iterator i = countries.find(country);
		if (i == countries.end())
			countries.insert(make_pair(country, 1));
		else
			i->second++;
	}
	map<string, int>::const_iterator e = countries.end();
	for (map<string, int>::const_iterator i = countries.begin(); i != e; ++i)
		cout << i->first << ' ' << i->second << endl;
	return 0;
}

