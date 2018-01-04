
/*
	UVa 118 - Mutant Flatworld Explorers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_118_Mutant_Flatworld_Explorers.cpp

	from Duke Internet Programming Contest 1993
		(http://contest.mff.cuni.cz/old/archive/duke1993/)
*/

#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	const int coordinate_max = 50;
	bool losts[coordinate_max + 1][coordinate_max + 1]; // losts[i][j] is true if a robot has been lost at (i, j)
	memset(losts, 0, sizeof(losts));
	int x_max, y_max;
	scanf("%d %d", &x_max, &y_max);
	int x, y;
	char d;
	while (scanf("%d %d %c", &x, &y, &d) != EOF) {
		const int nr_instructions_max = 100;
		char instructions[nr_instructions_max + 1];
		scanf("%s", instructions);
		bool lost = false;
		for (int i = 0, l = strlen(instructions); i < l && !lost; i++) {
			switch (instructions[i]) {
			case 'R':
				switch (d) {
				case 'N':
					d = 'E'; break;
				case 'S':
					d = 'W'; break;
				case 'E':
					d = 'S'; break;
				case 'W':
					d = 'N'; break;
				}
				break;
			case 'L':
				switch (d) {
				case 'N':
					d = 'W'; break;
				case 'S':
					d = 'E'; break;
				case 'E':
					d = 'N'; break;
				case 'W':
					d = 'S'; break;
				}
				break;
			default: // 'F'
				switch (d) {
				case 'N':
					if (y < y_max)
						y++;
					else if (!losts[x][y])
						lost = losts[x][y] = true;
					break;
				case 'S':
					if (y > 0)
						y--;
					else if (!losts[x][y])
						lost = losts[x][y] = true;
					break;
				case 'E':
					if (x < x_max)
						x++;
					else if (!losts[x][y])
						lost = losts[x][y] = true;
					break;
				case 'W':
					if (x > 0)
						x--;
					else if (!losts[x][y])
						lost = losts[x][y] = true;
					break;
				}
			}
		}
		if (lost)
			printf("%d %d %c LOST\n", x, y, d);
		else
			printf("%d %d %c\n", x, y, d);
	}
	return 0;
}

