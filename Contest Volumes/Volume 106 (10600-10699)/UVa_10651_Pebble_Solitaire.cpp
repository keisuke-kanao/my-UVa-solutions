
/*
	UVa 10651 - Pebble Solitaire

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10651_Pebble_Solitaire.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_cavities = 12;
const int nr_boards = 4096; // 2^12
int cache[nr_boards];
	// cache[i] is the minimum number of pebbles left on the board represented by i

int pebble_solitaire(int board)
{
	if (cache[board] != -1)
		return cache[board];
	int min_pebbles = nr_cavities;
	for (int i = 0, mask = 0x1ff1ff, cavities = 0x000e00,
		removable_011 = 0x000600, removable_110 = 0x000c00, removed_100 = 0x000800, removed_001 = 0x000200;
		i < nr_cavities - 2;
		i++, mask >>= 1, cavities >>= 1, removable_011 >>= 1, removable_110 >>= 1, removed_100 >>= 1, removed_001 >>= 1) {
		int c = board & cavities;
		if (c == removable_011)
			min_pebbles = min(min_pebbles, pebble_solitaire((board & mask) | removed_100));
		else if (c == removable_110)
			min_pebbles = min(min_pebbles, pebble_solitaire((board & mask) | removed_001));
	}
	if (min_pebbles == nr_cavities) { // no pebbles have been removed
		min_pebbles = 0;
		for (int i = 0, cavity = 0x000800; i < nr_cavities; i++, cavity >>= 1)
			if (board & cavity)
				min_pebbles++;
	}
	cache[board] = min_pebbles;
	return min_pebbles;
}

int main()
{
	for (int i = 0; i < nr_boards; i++)
		cache[i] = -1;
	int n;
	cin >> n;
	while (n--) {
		int board = 0;
			// A board is represented as twelve bits in which a cavity with a pebble in it is marked as '1'.
		for (int i = 0; i < nr_cavities; i++) {
			char c;
			cin >> c;
			if (i)
				board <<= 1;
			if (c == 'o')
				board |= 1;
		}
		cout << pebble_solitaire(board) << endl;
	}
	return 0;
}

