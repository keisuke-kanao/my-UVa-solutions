
/*
	UVa 10935 - Throwing cards away I

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10935_Throwing_cards_away_I.cpp
*/

#include <iostream>
#include <queue>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		queue<int> cards, discarded_cards;
		for (int i = 1; i <= n; i++)
			cards.push(i);
		int last;
		while (!cards.empty()) {
			last = cards.front();
			cards.pop();
			if (cards.empty())
				break;
			discarded_cards.push(last);
			int c = cards.front();
			cards.pop();
			cards.push(c);
		}
		cout << "Discarded cards:";
		while (!discarded_cards.empty()) {
			cout << ' ' << discarded_cards.front();
			discarded_cards.pop();
			if (discarded_cards.empty())
				break;
			cout << ',';
		}
		cout << endl;
		cout << "Remaining card: " << last << endl;
	}
	return 0;
}

