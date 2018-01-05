
/*
	UVa 11350 - Stern-Brocot Tree

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11350_Stern-Brocot_Tree.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

pair<long long, long long> fraction(const string& s)
{
	pair<long long, long long> l(0, 1), m(1, 1), r(1, 0);
	for (const char* p = s.c_str(); *p; p++) {
		if (*p == 'R')
			l = m; 
		else
			r = m;
		m = make_pair(l.first + r.first, l.second + r.second);
	}
	return m;
}

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int N;
	iss >> N;
	while (N--) {
		getline(cin, line);
		pair<long long, long long> f = fraction(line);
		cout << f.first << '/' << f.second << endl;

	}
	return 0;
}

/*

{0/1, 1/0}
{0/1, 1/1, 1/0}
{0/1, 1/2, 1/1, 2/1, 1/0}
{0/1, 1/3, 1/2, 2/3, 1/1, 3/2, 2/1, 3/1, 1/0}


RL
{1/1, 1/0}			{1/1, 2/1, 1/0}
{1/1, 2/1}			{1/1, 3/2, 2/1}

RLR
{1/1, 1/0}			{1/1, 2/1, 1/0}
{1/1, 2/1}			{1/1, 3/2, 2/1}
{3/2, 2/1}			{3/2, 5/3, 2/1}

RRL
{1/1, 1/0}			{1/1, 2/1, 1/0}
{2/1, 1/0}			{2/1, 3/1, 1/0}
{2/1, 3/1}			{2/1, 5/2, 3/1}

*/
