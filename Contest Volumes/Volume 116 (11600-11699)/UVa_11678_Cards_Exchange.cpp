
/*
	UVa 11678 - Cards' Exchange

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11678_Cards_Exchange.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_cards_max = 10000;
int alice_cards[nr_cards_max], betty_cards[nr_cards_max];

int skip_cards(int nc, int ic, const int cards[])
{
	int c = cards[ic++];
	for ( ; ic < nc; ic++)
		if (cards[ic] != c)
				break;
	return ic;
}

int main()
{
	while (true) {
		int na, nb;
		scanf("%d %d", &na, &nb);
		if (!na & !nb)
			break;
		for (int i = 0; i < na; i++)
			scanf("%d", &alice_cards[i]);
		for (int i = 0; i < nb; i++)
			scanf("%d", &betty_cards[i]);
		int xa = 0, xb = 0;
		for (int ia = 0, ib = 0; ia < na || ib < nb; ) {
			if (ia < na && ib < nb) {
				if (alice_cards[ia] < betty_cards[ib]) {
					xa++;
					ia = skip_cards(na, ia, alice_cards);
				}
				else if (alice_cards[ia] > betty_cards[ib]) {
					xb++;
					ib = skip_cards(nb, ib, betty_cards);
				}
				else {
					ia = skip_cards(na, ia, alice_cards);
					ib = skip_cards(nb, ib, betty_cards);
				}
			}
			else if (ia < na) {
				xa++;
				ia = skip_cards(na, ia, alice_cards);
			}
			else {
				xb++;
				ib = skip_cards(nb, ib, betty_cards);
			}
		}
		printf("%d\n", min(xa, xb));
	}
	return 0;
}

