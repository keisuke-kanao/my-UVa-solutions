
/*
	UVa 10903 - Rock-Paper-Scissors Tournament

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10903_Rock-Paper-Scissors_Tournament.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
using namespace std;

int main()
{
	const int n_max = 100;
	pair<int, int> games[n_max + 1];
		// games[i].first is the number of wins, games[i].second is the number of loses, of i-th player
	bool printed = false;
	while (true) {
		int n, k;
		cin >> n;
		if (!n)
			break;
		if (printed)
			cout << endl;
		else
			printed = true;
		for (int i = 1; i <= n; i++)
			games[i].first = games[i].second = 0;
		cin >> k;
		for (int i = 0, j = k * n * (n - 1) / 2; i < j; i++) {
			int ia, ib;
			string sa, sb;
			cin >> ia >> sa >> ib >> sb;
			int a_wins = 0;
			if (sa == "rock") {
				if (sb == "paper")
					a_wins = -1;
				else if (sb == "scissors")
					a_wins = 1;
			}
			else if (sa == "paper") {
				if (sb == "rock")
					a_wins = 1;
				else if (sb == "scissors")
					a_wins = -1;
			}
			else { // scissors
				if (sb == "rock")
					a_wins = -1;
				else if (sb == "paper")
					a_wins = 1;
			}
			if (a_wins == 1) {
				games[ia].first++; games[ib].second++;
			}
			else if (a_wins == -1) {
				games[ia].second++; games[ib].first++;
			}
		}
		for (int i = 1; i <= n; i++) {
			const pair<int, int>& g = games[i];
			if (g.first || g.second) {
				cout << fixed << setprecision(3) <<
					static_cast<double>(g.first) / static_cast<double>(g.first + g.second) << endl;
			}
			else
				cout << "-\n";
		}
	}
	return 0;
}

