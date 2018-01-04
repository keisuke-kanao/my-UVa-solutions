
/*
	UVa 121 - Pipe Fitters

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_121_Pipe_Fitters.cpp

	For this implementation, see "Programming Challenges" page 275 
	"12.3 Program Design Example: Plate Weight".
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int dense_layers(double w, double h, double r)
{
	if ((2.0 * r) > h)
		return 0;
	double gap = 2.0 * r * (sqrt(3.0) / 2.0); // distance between layers
	return 1 + floor((h - 2.0 * r) / gap);
}

int plates_per_row(int row, double w, double r)
{
	int plates_per_full_row = floor(w / (2.0 * r)); // number of plates in full/even row
	if ((row % 2) == 0)
		return(plates_per_full_row);
	if (((w / (2.0 * r)) - plates_per_full_row) >= 0.5) // odd row full, too
		return plates_per_full_row;
	else
		return plates_per_full_row - 1;
}

int dense_plates(double w, double l, double r)
{
	int layers = dense_layers(w,l,r); // number of layers of balls
	return ceil(layers / 2.0) * plates_per_row(0, w, r) +
		floor(layers / 2.0) * plates_per_row(1, w , r);
}

int grid_plates(double w, double h, double r)
{
	int layers = floor(h / (2.0 * r));// number of layers of balls
	return layers * plates_per_row(0, w, r);
}

int main()
{
	double a, b;
	while (cin >> a >> b) {
		int nr_pipes_for_grid = max(grid_plates(a, b, 0.5), grid_plates(b, a, 0.5));
		int nr_pipes_for_skew = max(dense_plates(a, b, 0.5), dense_plates(b, a, 0.5));
		if (nr_pipes_for_grid >= nr_pipes_for_skew)
			cout << nr_pipes_for_grid << " grid\n";
		else
			cout << nr_pipes_for_skew << " skew\n";
	}
	return 0;
}

