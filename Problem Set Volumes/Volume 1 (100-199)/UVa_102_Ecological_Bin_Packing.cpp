
/*
	UVa 102 - Ecological Bin Packing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_102_Ecological_Bin_Packing.cpp
*/

#include <iostream>
#include <limits>
using namespace std;

const int nr_bins = 3, nr_colors = 3;
int bottles[nr_bins][nr_colors];
const char colors[] = "BGC";
const int color_permutations[][nr_colors] = {
	{0, 2, 1}, // BCG
	{0, 1, 2}, // BGC
	{2, 0, 1}, // CBG
	{2, 1, 0}, // CGB
	{1, 0, 2}, // GBC
	{1, 2, 0}  // GCB
};

bool read_bottles()
{
	for (int i = 0; i < nr_bins; i++)
		for (int j = 0; j < nr_colors; j++)
			if (!(cin >> bottles[i][j]))
				return false;
	return true;
}

int main()
{
	while (read_bottles()) {
		int min_c, min_nr_moves = numeric_limits<int>::max();
		for (int c = 0; c < sizeof(color_permutations) / sizeof(color_permutations[0]); c++) {
			int nr_moves = 0;
			// i-th bin is filled with the bottles of j-th colors
			for (int i = 0; i < nr_bins; i++)
				for (int j = 0; j < nr_colors; j++)
					if (j != color_permutations[c][i])
						nr_moves += bottles[i][j];
			if (nr_moves < min_nr_moves) {
				min_c = c;
				min_nr_moves = nr_moves;
			}
		}
		cout << colors[color_permutations[min_c][0]] <<
			colors[color_permutations[min_c][1]] <<
			colors[color_permutations[min_c][2]] << ' ' << min_nr_moves << endl;
	}
	return 0;
}

