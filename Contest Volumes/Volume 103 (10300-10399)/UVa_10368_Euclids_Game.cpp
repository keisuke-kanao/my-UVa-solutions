
/*
	UVa 10368 - Euclid's Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10368_Euclids_Game.cpp

	from Waterloo local contest, 21 September, 2002, Problem B
		(http://acm.student.cs.uwaterloo.ca/~acm00/020928/data/)
*/

#include <iostream>
#include <algorithm>
using namespace std;

bool euclid_game(int x, int y)
{
	if (x < y)
		return euclid_game(y, x);
	else if (!(x % y))
		return true;
	else if (x - y < y)
		return !euclid_game(y, x - y);
	else
		return true;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		cout << ((euclid_game(n, m)) ? "Stan" : "Ollie")  << " wins\n";
	}
	return 0;
}

