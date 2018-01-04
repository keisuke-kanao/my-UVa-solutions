
/*
	UVa 497 - Strategic Defense Initiative

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_497_Strategic_Defense_Initiative.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

pair<int, int> lis(int n, const vector<int>& altitudes, vector<int>& l, vector<int>& prev)
{
	int length = 1, iend = 0;
	l[0] = 1;
	prev[0] = -1;
	for (int i = 1; i < n; i++) {
		l[i] = 1;
		prev[i] = -1;
		for (int j = 0; j < i; j++)
			if (altitudes[j] < altitudes[i]) {
				if (l[i] < 1 + l[j]) {
					l[i] = 1 + l[j];
					prev[i] = j;
				}
			}
		if (length < l[i]) {
			length = l[i];
			iend = i;
		}
	}
	return make_pair(length, iend);
}

void print_altitudes(const vector<int>& altitudes, const vector<int>& prev, int i, int iend)
{
	if (prev[i] != -1)
		print_altitudes(altitudes, prev, prev[i], iend);
	cout << altitudes[i] << endl;
}

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	getline(cin, line); // skip a blank line
	while (nr_cases--) {
		int n = 0;
		vector<int> altitudes;
		while (true) {
			if (!getline(cin, line) || line.empty())
				break;
			iss.str(line);
			int a;
			iss >> a;
			altitudes.push_back(a);
			iss.clear();
			n++;
		}
		cout << "Max hits: ";
		if (n) {
			vector<int> l(n), prev(n);
			pair<int, int> result = lis(n, altitudes, l, prev);
			cout << result.first << endl;
			print_altitudes(altitudes, prev, result.second, result.second);
		}
		else
			cout << 0 << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

