
/*
	UVa 1220 - Party at Hali-Bula

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1220_Party_at_Hali-Bula.cpp
*/

/*
Applied dynamic programming.
The number of guests that can be invited by an employee is calculated recursively 
either by inviting their immediate subordinates 
or by inviting the subordinates of each of their immediate subordinate.
For the latter case, the employee can attend the party too.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int n_max =  200;

map<string, int> employees;
vector<int> subordinates[n_max];
int nr_guests[n_max]; // nr_guests[i] is the number of guests that can be invited by the i-th employee
bool uniques[n_max];// uniques[i] is whether the list of guests that can be invited by the i-th employee of is unique or not

int register_employee(const string& s)
{
	pair<map<string, int>::iterator, bool> result = employees.insert(make_pair(s, static_cast<int>(employees.size())));
	return result.first->second;
}

pair<int, bool> invite_employees(int ei)
{
	int& nr = nr_guests[ei];
	if (nr != -1)
		return make_pair(nr, uniques[ei]);
	const vector<int>& sbs = subordinates[ei];
	if (sbs.empty())
		return make_pair(nr = 1, uniques[ei] = true);
	int nr_s = 0, nr_ss = 1;
	bool unique_s = true, unique_ss = true;
	for (size_t i = 0; i < sbs.size(); i++) {
		pair<int, bool> result = invite_employees(sbs[i]); // invite immediate subordinates
		nr_s += result.first, unique_s &= result.second;
		const vector<int>& ssbs = subordinates[sbs[i]];
		for (size_t j = 0; j < ssbs.size(); j++) {
			result = invite_employees(ssbs[j]); // invite subordinates of each immediate subordinate
			nr_ss += result.first, unique_ss &= result.second;
		}
	}
	if (nr_s > nr_ss)
		nr = nr_s, uniques[ei] = unique_s;
	else if (nr_s < nr_ss)
		nr = nr_ss, uniques[ei] = unique_ss;
	else
		nr = nr_s, uniques[ei] = false;
	return make_pair(nr, uniques[ei]);
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		employees.clear();
		for (int i = 0; i < n; i++) {
			nr_guests[i] = -1;
			subordinates[i].clear();
		}
		string s, b;
		cin >> b;
		register_employee(b);
		for (int i = 1; i < n; i++) {
				cin >> s >> b;
			int si = register_employee(s), bi = register_employee(b);
			subordinates[bi].push_back(si);
		}
		pair<int, bool> result = invite_employees(0);
		cout << result.first << ((result.second) ?  " Yes\n" : " No\n");
	}
	return 0;
}

