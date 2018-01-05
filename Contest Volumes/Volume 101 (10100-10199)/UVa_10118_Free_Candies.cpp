
/*
	UVa 10118 - Free Candies

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10118_Free_Candies.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_piles = 4, n_max = 40, color_max = 20, backet_max = 5;

int candies[nr_piles][n_max];
int n, piles[nr_piles], nr_colors;
bool colors[color_max + 1];
int results[n_max + 1][n_max + 1][n_max + 1][n_max + 1];
bool visited[n_max + 1][n_max + 1][n_max + 1][n_max + 1];

#ifdef DEBUG
int game(int indent)
#else
int game()
#endif
{
#ifdef DEBUG
	for (int i = 0; i < indent; i++)
		putchar(' ');
	printf("[%d][%d][%d][%d] %d\n", piles[0], piles[1], piles[2], piles[3], nr_colors);
#endif
	if (visited[piles[0]][piles[1]][piles[2]][piles[3]])
		return results[piles[0]][piles[1]][piles[2]][piles[3]];
	int result = 0;
	for (int i = 0; i < nr_piles; i++)
		if (piles[i] < n) {
			int c = candies[i][piles[i]];
			if (colors[c]) {
				piles[i]++, nr_colors--, colors[c] = false;
#ifdef DEBUG
				result = max(result, 1 + game(indent + 1));
#else
				result = max(result, 1 + game());
#endif
				piles[i]--, nr_colors++, colors[c] = true;
			}
			else if (nr_colors < backet_max - 1) {
				piles[i]++, nr_colors++, colors[c] = true;
#ifdef DEBUG
				result = max(result, game(indent + 1));
#else
				result = max(result, game());
#endif
				piles[i]--, nr_colors--, colors[c] = false;
			}
		}
#ifdef DEBUG
	for (int i = 0; i < indent; i++)
		putchar(' ');
	printf("[%d][%d][%d][%d] %d: %d\n", piles[0], piles[1], piles[2], piles[3], nr_colors, result);
#endif
	visited[piles[0]][piles[1]][piles[2]][piles[3]] = true;
	return results[piles[0]][piles[1]][piles[2]][piles[3]] = result;
}

int main()
{
	while (true) {
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < nr_piles; j++)
					scanf("%d", &candies[j][i]);
		memset(piles, 0, sizeof(piles));
		nr_colors = 0;
		memset(colors, 0, sizeof(colors));
		memset(visited, 0, sizeof(visited));
		visited[n][n][n][n] = true, results[n][n][n][n] = 0;
#ifdef DEBUG
		printf("%d\n", game(0));
#else
		printf("%d\n", game());
#endif
	}
	return 0;
}

