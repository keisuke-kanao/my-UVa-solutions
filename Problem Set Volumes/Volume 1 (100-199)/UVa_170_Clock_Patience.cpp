
/*
	UVa 170 - Clock Patience

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_170_Clock_Patience.cpp

	from ACM South Pacific Regionals - 1991
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <iostream>
#include <iomanip>
using namespace std;

struct card {
	char rank_;
	char suit_;
};

const int nr_piles = 13, nr_cards_per_pile = 4;
card cards[nr_piles][nr_cards_per_pile];
int top_cards[nr_piles];

int main()
{
	while (true) {
		char r;
		cin >> r;
		if (r == '#')
			break;
		cin.unget();
		for (int i = 0; i < nr_cards_per_pile; i++)
			for (int j = nr_piles - 1; j >= 0 ; j--)
				cin >> cards[j][i].rank_ >> cards[j][i].suit_;
		for (int i = 0; i < nr_piles; i++)
			top_cards[i] = 0;
		int nr_exposed = 0, cp = nr_piles - 1, pp;
		while (true) {
			if (top_cards[cp] == nr_cards_per_pile)
				break;
			nr_exposed++;
			pp = cp;
			char r = cards[pp][top_cards[pp]].rank_;
			top_cards[pp]++;
#ifdef DEBUG
			cout << cards[pp][top_cards[pp] - 1].rank_ << cards[pp][top_cards[pp] - 1].suit_ << endl;
#endif
			switch (r) {
			case 'A':
				cp = 0; break;
			case 'T':
				cp = 9; break;
			case 'J':
				cp = 10; break;
			case 'Q':
				cp = 11; break;
			case 'K':
				cp = 12; break;
			default:
				cp = r - '1'; break;
			}
		}
		cout << setfill('0') << setw(2) << nr_exposed << ',' <<
			cards[pp][top_cards[pp] - 1].rank_ << cards[pp][top_cards[pp] - 1].suit_ << endl;
	}
	return 0;
}

