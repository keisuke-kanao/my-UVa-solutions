
/*
	8.6.6 Garden of Eden
	PC/UVa IDs: 110806/10001, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10001_Garden_of_Eden.cpp
*/

#include <iostream>
#include <string>
using namespace std;

#ifdef DEBUG
void print_cr(int li, int lcr)
{
	for (int i = 0; i < li; i++)
		cout << "  ";
	for (int i = 1; i >= 0; i--)
		cout << ((lcr & (1 << i)) ? '1' : '0');
	cout << endl;
}
#endif

bool find_ancestor(int n /* number of bits in the lattice */, int li /* lattice index */, unsigned int lattice,
	int identifier, int fcr /* cell and right bits of the first cell */, int plc /* left and cell bits of the previous cell */)
{
	int id = (lattice & (static_cast<unsigned int>(1) << li)) /* the value of current cell is 1 */ ?
		identifier : ~identifier;
	for (int i = 0; i < 4; i++, id >>= 2)
		if (id & 3) {
			int lc_0 = -1, lc_1 = -1; // left, cell, and right bits whose new state is equal to the current value
			if (id & 1)
				lc_0 = i * 2;
			if (id & 2)
				lc_1 = i * 2 + 1;
			if (!li) { // for the first cell
#ifdef DEBUG
				print_cr(li, i);
#endif
				// pass the cell and right bits of the first cell
				if (id & 1 && find_ancestor(n, li + 1, lattice, identifier, lc_0 & 3, i) ||
					id & 2 && find_ancestor(n, li + 1, lattice, identifier, lc_1 & 3, i))
					return true;
			}
			else if (li == n - 1) { // for the last cell
#ifdef DEBUG
				print_cr(li, i);
#endif
				if (lc_0 != -1 && (lc_0 >> 1) == fcr && (lc_0 & 3) == plc ||
					lc_1 != -1 && (lc_1 >> 1) == fcr && (lc_1 & 3) == plc)
					return true;
			}
			else if (lc_0 != -1 && (lc_0 & 3) == plc || lc_1 != -1 && (lc_1 & 3) == plc) {
#ifdef DEBUG
				print_cr(li, i);
#endif
				if (find_ancestor(n, li + 1, lattice, identifier, fcr, i))
					// cell and right bits of the current cell are equal to the left ant cell bits of the previous cell
					return true;
			}
		}
	return false;
}

int main(int /* argc */, char** /* argv */)
{
	int identifier, n;
	string s;
	while (cin >> identifier >> n >> s) {
		unsigned int lattice = 0; // for the 32-bit unsigned int, the value of the i-th cell (i >= 0) is stored in i-th bit
		for (int i = 0; i < n; i++)
			if (s[i] == '1')
				lattice |= static_cast<unsigned int>(1) << (n - i - 1);
		cout << ((find_ancestor(n, 0, lattice, identifier, -1, -1)) ? "REACHABLE\n" : "GARDEN OF EDEN\n");
	}
	return 0;
}

