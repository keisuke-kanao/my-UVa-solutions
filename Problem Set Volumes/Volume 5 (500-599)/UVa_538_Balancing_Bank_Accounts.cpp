
/*
	UVa 538 - Balancing Bank Accounts

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_538_Balancing_Bank_Accounts.cpp

	from University of Ulm Local Contest 1998 Problem B
		(http://www.informatik.uni-ulm.de/acm/Locals/1998/)
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct traveller {
	string name_;
	int account_;

	bool operator<(const traveller& t) const {return account_ < t.account_;}
};

int main()
{
	for (int cn = 1; ; cn++) {
		int n, t;
		cin >> n >> t;
		if (!n && !t)
			break;
		map<string, int> names;
		vector<traveller> travellers(n);
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			travellers[i].name_ = s; travellers[i].account_ = 0;
			names[s] = i;
		}
		while (t--) {
			string s, t;
			int a;
			cin >> s >> t >> a;
			travellers[names[s]].account_ -= a;
			travellers[names[t]].account_ += a;
		}
		sort(travellers.begin(), travellers.end());
		cout << "Case #" << cn << endl;
		for (int i = 0, j = n - 1; i < j && travellers[i].account_; ) {
			int d = travellers[i].account_ + travellers[j].account_;
			cout << travellers[j].name_ << ' ' << travellers[i].name_ << ' ';
			if (d > 0) {
				cout << -travellers[i].account_ << endl;
				i++;
				travellers[j].account_ = d;
			}
			else if (d < 0) {
				cout << travellers[j].account_ << endl;
				travellers[i].account_ = d;
				j--;
			}
			else {
				cout << travellers[j].account_ << endl;
				i++; j--;
			}
		}
		cout << endl;
	}
	return 0;
}

