
/*
	UVa 10165 - Stone Game

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10165_Stone_Game.cpp
*/

/*
	Rules of the Game of Nim:
	There are n piles of coins. When it is a player's turn he chooses one pile and takes at least one coin from it. 
	If someone is unable to move he loses (so the one who removes the last coin is the winner).

	Let n1, n2, Åc nk, be the sizes of the piles. 
	It is a losing position for the player whose turn it is if and only if n1 xor n2 xor .. xor nk = 0.
	Examples:
	  Position (1, 2, 3) is losing because 1 xor 2 xor 3 = (1)2 xor (10)2 xor (11)2 = 0.
	  Position (7, 4, 1) is winning because 7 xor 4 xor 1 = (111)2 xor (10)2 xor (1)2 = (10)2 = 2.
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int nim_sum = 0;
		for (int i = 0; i < n; i++) {
			int p;
			cin >> p;
			nim_sum ^= p;
		}
		cout << ((nim_sum) ? "Yes\n" : "No\n");
	}
	return 0;
}

