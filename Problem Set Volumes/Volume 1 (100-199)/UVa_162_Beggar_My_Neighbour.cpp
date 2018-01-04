
/*
	UVa 162 - Beggar My Neighbour

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_162_Beggar_My_Neighbour.cpp
*/

#include <list>
#include <cstdio>
using namespace std;

int face_card(char c)
{
	switch (c) {
	case 'J':
		return 1;
	case 'Q':
		return 2;
	case 'K':
		return 3;
	case 'A':
		return 4;
	default:
		return 0;
	}
}

int play(int nc, list<char>& player, list<char>& played)
{
	if (!nc)
		nc = 1;
	while (nc--) {
		if (player.empty())
			return -1;
		char c = player.front();
		player.pop_front();
		played.push_back(c);
		int fc = face_card(c);
		if (fc)
			return fc;
	}
	return 0;
}

int main()
{
	const int nr_cards = 52;
	while (true) {
		list<char> players[2], played;
			// players[0] is the non-dealer, players[1] is the dealer
	    char card[2 + 1];
    	scanf("%s", card);
		if (card[0] == '#')
			break;
		players[0].push_front(card[1]);
		for (int i = 1; i < nr_cards; i++) {
			scanf("%s", card);
			players[i % 2].push_front(card[1]);
		}
		bool done = false;
		int pi = 0, nc = 0;
		while (true) {
			int fc = play(nc, players[pi], played);
			pi = (pi + 1) % 2;
			if (fc == -1)
				break;
			if (!fc && nc)
				players[pi].splice(players[pi].end(), played);
			nc = fc;
		}
		printf("%d%3d\n", 2 - pi, static_cast<int>(players[pi].size()));
	}
	return 0;
}

