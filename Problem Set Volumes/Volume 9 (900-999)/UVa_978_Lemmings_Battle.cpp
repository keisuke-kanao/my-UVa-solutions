
/*
	UVa 978 - Lemmings Battle!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_978_Lemmings_Battle.cpp

	An accepted solution.
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int B, SG, SB;
		cin >> B >> SG >> SB;
		priority_queue<int> pqsg, pqsb;
		while (SG--) {
			int i;
			cin >> i;
			pqsg.push(i);
		}
		while (SB--) {
			int i;
			cin >> i;
			pqsb.push(i);
		}
		queue<int> qsg, qsb;
		while (!pqsg.empty() && !pqsb.empty()) {
			int b = min(B, min(static_cast<int>(pqsg.size()), static_cast<int>(pqsb.size())));
			while (b--) {
				int g = pqsg.top(), b = pqsb.top();
				pqsg.pop(); pqsb.pop();
				if (g > b)
					qsg.push(g - b);
				else if (g < b)
					qsb.push(b - g);
			}
			while (!qsg.empty()) {
				pqsg.push(qsg.front());
				qsg.pop();
			}
			while (!qsb.empty()) {
				pqsb.push(qsb.front());
				qsb.pop();
			}
		}
		if (pqsg.empty() && pqsb.empty())
			cout << "green and blue died\n";
		else if (pqsg.empty()) {
			cout << "blue wins\n";
			do {
				cout << pqsb.top() << endl;
				pqsb.pop();
			} while (!pqsb.empty());
		}
		else {
			cout << "green wins\n";
			do {
				cout << pqsg.top() << endl;
				pqsg.pop();
			} while (!pqsg.empty());
		}
		if (N)
			cout << endl;
	}
	return 0;
}

