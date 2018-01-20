
/*
	12.6.4 Bee Maja
	PC/UVa IDs: 111204/10182, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10182_Bee_Maja.cpp
*/

/*
	A honeycomb can be seen as layers of hexagonal circles.
	According to the Willi's coordinate system, the first layer has only one cell, 
	the second layer is numbered between 2 and 7, the third is numbered between 8 and 19, etc.
	The n-th (n >= 2) layer has 6 * (n - 1) cells and the sum of cells is
		1 + Σ 6 * (k - 1) (k = 1 to n) = 3 * n * (n - 1) + 1.

	For a given number m in the Willi's coordinate system, the layer number n is calculated using the below 
	inequality expressioins:
		3 * (n - 1) * (n - 2) + 1 <= m < 3 * n * (n - 1) + 1
	Or,
		(3 + sqrt(D)) / 6 < n <= (9 + sqrt(D)) / 6, where D = 3 * (4 * m - 1).

	The cells that belongs to the the n-th layer of circle have the coordinates of (x, y) in the Maja's 
	system, where -n < x, y < n.
*/

#include <iostream>
#include <cmath>
using namespace std;

int calculate_layer_number(int m)
{
	double sqrt_d = sqrt(static_cast<double>(3 * (4 * m - 1)));
	return static_cast<int>(ceil((3.0 + sqrt_d) / 6.0));
}

int main(int /* argc */, char** /* argv */)
{
	int m;
	while (cin >> m) {
		if (m == 1)
			cout << "0 0\n";
		else {
			int nr_layer = calculate_layer_number(m); // get the layer number
			int min_n = 3 * (nr_layer - 1) * (nr_layer - 2) + 2; // min. number in the layer
			m -= min_n;
			// the bottom hexagonal is the (layer - 1)-th number in the layer
			m -= nr_layer - 2;
			if (m < 0)
				m += 6 * (nr_layer - 1);
			int x = 0, y = nr_layer - 1;
			for (int i = 0; i < nr_layer - 1 && m; i++, m--)
				x--;
			for (int i = 0; i < nr_layer - 1 && m; i++, m--)
				y--;
			for (int i = 0; i < nr_layer - 1 && m; i++, m--) {
				x++; y--;
			}
			for (int i = 0; i < nr_layer - 1 && m; i++, m--)
				x++;
			for (int i = 0; i < nr_layer - 1 && m; i++, m--)
				y++;
			for (int i = 0; i < nr_layer - 1 && m; i++, m--) {
				x--; y++;
			}
			cout << x << ' ' << y << endl;
		}
	}
	return 0;
}

