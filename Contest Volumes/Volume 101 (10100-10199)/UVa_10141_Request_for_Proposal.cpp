
/*
	UVa 10141 - Request for Proposal

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10141_Request_for_Proposal.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	for (int nr = 1; ; nr++) {
		int n, p;
		cin >> n >> p;
		if (!n && !p)
			break;
		string s;
		getline(cin, s);
		if (nr > 1)
			cout << endl;
		for (int i = 0; i < n; i++)
			getline(cin, s);
		cout << "RFP #" << nr << endl;
		if (p) {
			string best_name;
			double best_price;
			int best_compliance;
			for (int i = 0; i < p; i++) {
				string name;
				double price;
				int compliance;
				getline(cin, name);
				cin >> price >> compliance;
				getline(cin, s);
				if (!i || compliance > best_compliance ||
					compliance == best_compliance && price < best_price) {
					best_name = name; best_price = price; best_compliance = compliance;
				}
				for (int j = 0; j < compliance; j++)
					getline(cin, s);
			}
			cout << best_name << endl;
		}
	}
	return 0;
}

