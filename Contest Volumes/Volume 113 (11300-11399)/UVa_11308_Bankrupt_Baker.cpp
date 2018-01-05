
/*
	UVa 11308 - Bankrupt Baker

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11308_Bankrupt_Baker.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct recipe {
	string name_;
	int cost_;

	recipe(const string& name, int cost) : name_(name), cost_(cost) {}
	bool operator<(const recipe& r) const {
		if (cost_ < r.cost_)
			return true;
		else if (cost_ > r.cost_)
			return false;
		else
			return name_ < r.name_;
	}
};

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int t;
	iss >> t;
	iss.clear();
	while (t--) {
		string binder;
		getline(cin, binder);
		transform(binder.begin(), binder.end(), binder.begin(), (int(*)(int))toupper);
		getline(cin, s);
		iss.str(s);
		int m, n, b;
		iss >> m >> n >> b;
		iss.clear();
		map<string, int> ingredients;
		while (m--) {
			getline(cin, s);
			iss.str(s);
			string ingredient;
			int price;
			iss >> ingredient >> price;
			iss.clear();
			ingredients.insert(make_pair(ingredient, price));
		}
		vector<recipe> recipes;
		while (n--) {
			string name;
			getline(cin, name);
			getline(cin, s);
			iss.str(s);
			int k;
			iss >> k;
			iss.clear();
			int cost = 0;
			while (k--) {
				getline(cin, s);
				iss.str(s);
				string ingredient;
				int units;
				iss >> ingredient >> units;
				iss.clear();
				cost += ingredients[ingredient] * units;
			}
			if (cost <= b)
				recipes.push_back(recipe(name, cost));
		}
		sort(recipes.begin(), recipes.end());
		cout << binder << endl;
		if (recipes.empty())
			cout << "Too expensive!\n\n";
		else {
			for (vector<recipe>::const_iterator ri = recipes.begin(), re = recipes.end(); ri != re; ++ri)
				cout << ri->name_ << endl;
			cout << endl;
		}
	}
	return 0;
}

