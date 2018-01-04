
/*
	UVa 11629 - Ballot evaluation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11629_Ballot_evaluation.cpp
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
	int p, g;
	cin >> p >> g;
	map<string, int> votes;
	while (p--) {
		string party;
		char c;
		int vote, decimal;
		cin >> party >> vote >> c >> decimal;
		votes[party] = vote * 10 + decimal;
	}
	for (int i = 1; i <= g; i++) {
		int j = 0, n;
		string s;
		while (true) {
			cin >> s;
			j += votes[s];
			cin >> s;
			if (s == "+")
				continue;
			else {
				cin >> n;
				n *= 10;
				break;
			}
		}
		bool correct = false;
		if (s == "<") {
			if (j < n)
				correct = true;
		}
		else if (s == ">") {
			if (j > n)
				correct = true;
		}
		else if (s == "<=") {
			if (j <= n)
				correct = true;
		}
		else if (s == ">=") {
			if (j >= n)
				correct = true;
		}
		else {
			if (j == n)
				correct = true;
		}
		cout << "Guess #" << i << " was " << ((correct) ? "correct.\n" : "incorrect.\n");
	}
	return 0;
}

