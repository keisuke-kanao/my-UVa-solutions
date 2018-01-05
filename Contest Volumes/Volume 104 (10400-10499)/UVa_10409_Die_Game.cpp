
/*
	UVa 10409 - Die Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10409_Die_Game.cpp
*/

#include <cstdio>
using namespace std;

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int top = 1, north = 2, south = 5, east = 4, west = 3;
		while (n--) {
			char direction[8];
			scanf("%s", direction);
			int t = top; 
			switch (direction[0]) {
			case 'n':
				top = south;
				north = t; south = 7 - t;
				break;
			case 's':
				top = north;
				south = t; north = 7 - t;
				break;
			case 'e':
				top = west;
				east = t; west = 7 - t;
				break;
			case 'w':
				top = east;
				west = t; east = 7 - t;
				break;
			}
		}
		printf("%d\n", top);;
	}
	return 0;
}

