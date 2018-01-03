
/*
	UVa 830 - Shark

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_830_Shark.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

/*
All animals have a distinct rectangular shape, except sharks, as explained below. 
  Single square animals (i.e., animals which fill one square only) are sardines. 
  Two square animals (filling a 1 by 2 rectangle) are mackerels; 
    longer animals with width 1 are salmons. 
  Square animals larger than sardines are turtles (there can be 2 by 2, 3 by 3, etc., turtles). 
  Groupers are rectangular with width 2 and length greater than 2. 
  Dolphins are rectangular with width 3 and length greater than 3. 
  Whales are rectangular with width 4 and length greater than 4. 
  Finally sharks are similar to dolphins, having width 3, but their shape is not a rectangle. 
    As a matter of fact, the tail fin for dolphins is horizontal and 
    that is what gives dolphins a digitalized rectangular shape. 
    Sharks, on the other hand, have a vertical tail fin, 
    which is recognized by an extra square along the middle row of squares that represent the body of the shark.
*/

enum {sardine, mackerel, salmon, grouper, turtle, dolphin, whale, shark};
#ifdef DEBUG
const char* names[] = {"sardine", "mackerel", "salmon", "grouper", "turtle", "dolphin", "whale", "shark"};
#endif
const int nr_shapes = shark - sardine + 1;
const int L_max = 64, C_max = 64;
char grid[L_max][C_max + 1];

int clear_shape(int L, int C, int ls, int cs, int w, int c)
{
	int i, j, h = 0;
	for (i = ls; i < L; i++, h++)
		for (j = cs; j < cs + w; j++) {
			if (grid[i][j] != c)
				return h;
			grid[i][j] = '\0';
		}
	return h;
}

int shape(int L, int C, int ls, int cs)
{
	int j, w = 1, h;
	char c = grid[ls][cs];
	for (j = cs + 1; j < C; j++, w++)
		if (grid[ls][j] != c)
			break;
	switch (w) {
	case 1:
		if (ls + 1 < L && cs && cs + 1 < C && grid[ls + 1][cs - 1] == c &&
			grid[ls + 1][cs] == c && grid[ls + 1][cs + 1] == c) {
			grid[ls][cs] = '\0';
			clear_shape(L, C, ls + 1, cs - 1, 3, c);
			return shark;
		}
		else {
			h = clear_shape(L, C, ls, cs, 1, c);
			return (h > 2) ? salmon : ((h == 2) ? mackerel : sardine);
		}
	case 2:
		h = clear_shape(L, C, ls, cs, 2, c);
		return ((h > 2) ? grouper : (h == 2) ? turtle : mackerel);
	case 3:
		h = clear_shape(L, C, ls, cs, 3, c);
		if (h > 3) {
			if (ls + h < L && grid[ls + h][cs + 1] == c) {
				grid[ls + h][cs + 1] = '\0';
				return shark;
			}
			else
				return dolphin;
		}
		else
			return (h == 3) ? turtle : ((h == 2) ? grouper : salmon);
	case 4:
		h = clear_shape(L, C, ls, cs, 4, c);
		if (h > 4)
			return whale;
		else if (h == 3) {
			if (cs && grid[ls + 1][cs - 1] == c) {
				grid[ls + 1][cs - 1] = '\0';
				return shark;
			}
			else if (cs + 4 < C && grid[ls + 1][cs + 4] == c) {
				grid[ls + 1][cs + 4] = '\0';
				return shark;
			}
			else
				return dolphin;
		}
		else
			return (h == 4) ? turtle : ((h == 2) ? grouper : salmon);
	default:
		h = clear_shape(L, C, ls, cs, w, c);
		if (h > 4)
			return turtle;
		else if (h == 3) {
			if (cs && grid[ls + 1][cs - 1] == c) {
				grid[ls + 1][cs - 1] = '\0';
				return shark;
			}
			else if (cs + 4 < C && grid[ls + 1][cs + 4] == c) {
				grid[ls + 1][cs + 4] = '\0';
				return shark;
			}
			else
				return dolphin;
		}
		else
			return (h == 4) ? whale : ((h == 2) ? grouper : salmon);
	}
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int L, C;
		scanf("%d %d", &L, &C);
		for (int i = 0; i < L; i++)
			scanf("%s", grid[i]);
		int shapes[nr_shapes];
		memset(shapes, 0, sizeof(shapes));
		for (int i = 0; i < L; i++)
			for (int j = 0; j < C; j++)
				if (islower(grid[i][j])) {
					int s = shape(L, C, i, j);
#ifdef DEBUG
					printf("(%2d, %2d) %s\n", i, j, names[s]);
#endif
					shapes[s]++;

				}
		for (int i = 0; i < nr_shapes; i++)
			printf("%d%c", shapes[i], ((i < nr_shapes - 1) ? ' ' : '\n'));
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

