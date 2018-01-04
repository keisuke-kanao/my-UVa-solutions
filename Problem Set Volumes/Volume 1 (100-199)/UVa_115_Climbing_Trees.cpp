
/*
	UVa 115 - Climbing Trees

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_115_Climbing_Trees.cpp
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int nr_names_max = 300;
int parents[nr_names_max + 1]; // parents[i] is the index ofi's parent
int iparents; // max. index to parents[]

int register_name(const string& name, map<string, int>& names)
{
	map<string, int>::iterator i = names.find(name);
	if (i != names.end())
		return i->second;
	else {
		names.insert(make_pair(name, ++iparents));
		return iparents;
	}
}

int get_name(const string& name, map<string, int>& names)
{
	map<string, int>::iterator i = names.find(name);
	return (i != names.end()) ? i->second : 0;
}

int is_parent(int pi, int qi) // see if pi is an ancestor of qi
{
	for (int k = 0; parents[qi]; k++, qi = parents[qi])
		if (parents[qi] == pi)
			return k;
	return -1;
}

bool are_cousins(int pi, int qi, int& k, int& j) // see if p and q are cousins
{
	for (int kp = 0; parents[pi]; kp++, pi = parents[pi]) {
		int ri = qi;
		for (int kq = 0 ; parents[ri]; kq++, ri = parents[ri])
			if (parents[pi] == parents[ri]) {
				k = min(kp, kq);
				j = abs(kp - kq);
				return true;
			}
	}
	return false;
}

int main()
{
	string p, q;
	map<string, int> names;
	while (true) {
		cin >> p >> q;
		if (p == "no.child")
			break;
		int pi = register_name(p, names), qi = register_name(q, names);
		parents[pi] = qi;
	}
	while (cin >> p >> q) {
		int k, j;
		int pi = get_name(p, names), qi = get_name(q, names);
		if (!pi || !qi)
			cout << "no relation\n";
		else if ((k = is_parent(pi, qi)) != -1) {
			while (k--)
				cout << ((k) ? "great " : "grand ");
			cout << "parent\n";
		}
		else if ((k = is_parent(qi, pi)) != -1) {
			while (k--)
				cout << ((k) ? "great " : "grand ");
			cout << "child\n";
		}
		else if (parents[pi] && parents[pi] == parents[qi])
			cout << "sibling\n";
		else if (are_cousins(pi, qi, k, j)) {
			cout << k << " cousin";
			if (j)
				cout <<" removed " << j;
			cout << endl;
		}
		else
			cout << "no relation\n";
	}
	return 0;
}

