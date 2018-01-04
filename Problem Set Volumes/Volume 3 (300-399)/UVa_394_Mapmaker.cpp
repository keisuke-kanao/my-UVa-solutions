
/*
	UVa 394 - Mapmaker

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_394_Mapmaker.cpp

	from ACM Mid-Central Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1996/index.html)
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

const int nr_dimensions_max = 10;

struct array {
	int base_;
	int nr_dimensions_;
	int constants_[nr_dimensions_max + 1];
};

int main()
{
	int n, r;
	cin >> n >> r;
	map<string, array*> arrays;
	while (n--) {
		string s;
		cin >> s;
		array* a = new array();
		int cd;
		cin >> a->base_ >> cd >> a->nr_dimensions_;
		a->constants_[a->nr_dimensions_] = cd;
		pair<int, int> bounds[nr_dimensions_max + 1];
		for (int i = 1; i <= a->nr_dimensions_; i++)
			cin >> bounds[i].first >> bounds[i].second;
		a->constants_[0] = a->base_ - a->constants_[a->nr_dimensions_] * bounds[a->nr_dimensions_].first;
		for (int i = a->nr_dimensions_ - 1; i; i--) {
			a->constants_[i] = a->constants_[i + 1] * (bounds[i + 1].second - bounds[i + 1].first + 1);
			a->constants_[0] -= a->constants_[i] * bounds[i].first;
		}
		arrays.insert(make_pair(s, a));
	}
	while (r--) {
		string s;
		cin >> s;
		map<string, array*>::iterator ai = arrays.find(s);
		if (ai == arrays.end())
			continue;
		array* a = ai->second;
		int indices[nr_dimensions_max + 1];
		for (int i = 1; i <= a->nr_dimensions_; i++)
			cin >> indices[i];
		int address = a->constants_[0];
		for (int i = 1; i <= a->nr_dimensions_; i++)
			address += a->constants_[i] * indices[i];
		cout << s << '[';
		for (int i = 1; i <= a->nr_dimensions_; i++) {
			if (i > 1)
				cout << ", ";
			cout << indices[i];
		}
		cout << "] = " << address << endl;
	}
	return 0;
}

