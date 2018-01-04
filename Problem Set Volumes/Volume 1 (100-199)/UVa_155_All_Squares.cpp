
/*
	UVa 155 - All Squares

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_155_All_Squares.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

int how_many_squres(int k, int cx, int cy, int px, int py)
{
	if (!k)
		return 0;
	int ns = (px >= cx - k && px <= cx + k && py >= cy - k && py <= cy + k) ? 1 : 0;
	return ns + how_many_squres(k / 2, cx - k, cy - k, px, py) +
		how_many_squres(k / 2, cx + k, cy - k, px, py) +
		how_many_squres(k / 2, cx + k, cy + k, px, py) +
		how_many_squres(k / 2, cx - k, cy + k, px, py);
}

int main()
{
	while (true) {
		int k, px, py;
		cin >> k >> px >> py;
		if (!k && !px && !py)
			return 0;
		cout << setfill(' ') << setw(3) << how_many_squres(k, 1024, 1024, px, py) << endl;
	}
	return 0;
}

