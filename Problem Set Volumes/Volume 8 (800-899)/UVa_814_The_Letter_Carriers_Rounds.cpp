
/*
	UVa 814 - The Letter Carrier's Rounds

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_814_The_Letter_Carriers_Rounds.cpp

	An accespted solution.
*/

#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main()
{
	set<string> mta_users;
	while (true) {
		string mta;
		int n;
		cin >> mta;
		if (mta == "*")
			break;
		cin >> mta >> n;
		while (n--) {
			string user;
			cin >> user;
			mta_users.insert(user + "@" + mta);
		}
	}
	string address;
	while (cin >> address) {
		if (address == "*")
			break;
		string::size_type p = address.find('@');
		pair<string, string> sender = make_pair(address.substr(0, p), address.substr(p + 1));
		vector< pair<string, string> > recipients;
		while (cin >> address && address != "*") {
			string::size_type p = address.find('@');
			pair<string, string> recipient = make_pair(address.substr(0, p), address.substr(p + 1));
			if (find(recipients.begin(), recipients.end(), recipient) == recipients.end())
				recipients.push_back(recipient);
		}
		string message;
		getline(cin, message); // discard '\n'
		vector<string> messages;
		while (getline(cin, message) && message != "*")
			messages.push_back(message);
		vector<bool> sent(recipients.size(), false);
		for (size_t i = 0; i < recipients.size(); i++) {
			if (sent[i])
				continue;
			cout << "Connection between " << sender.second.c_str() << " and " << recipients[i].second.c_str() << endl;
			cout << "     HELO " << sender.second.c_str() << "\n     250\n";
			cout << "     MAIL FROM:<" << sender.first.c_str() << '@' << sender.second.c_str() << ">\n     250\n";
			bool ok = false;
			for (size_t j = i; j < recipients.size(); j++) {
				if (recipients[j].second == recipients[i].second) {
					sent[j] = true;
					cout << "     RCPT TO:<" << recipients[j].first.c_str() << '@' << recipients[j].second.c_str() << ">\n";
					if (mta_users.find(recipients[j].first + "@" + recipients[j].second) != mta_users.end()) {
						ok = true;
						cout << "     250\n";
					}
					else
						cout << "     550\n";
				}
			}
			if (ok) {
				cout << "     DATA\n     354\n";
				for (size_t j = 0; j < messages.size(); j++)
					cout << "     " << messages[j].c_str() << endl;
				cout << "     .\n     250\n";
			}
			cout << "     QUIT\n     221\n";
		}
	}
	return 0;
}

