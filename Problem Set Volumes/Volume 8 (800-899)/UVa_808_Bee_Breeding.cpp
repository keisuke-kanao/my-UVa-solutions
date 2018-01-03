
/*
	UVa 808 - Bee Breeding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_808_Bee_Breeding.cpp

	an accepted soluton, ranking = 383.
*/

#include <iostream>
#include <utility>
#include <cstdlib>
#include <cmath>
using namespace std;

/*
	For conversion betwwn cell numbers and hexagonal coordinates, see the solution of Uva 10182 - Bee Maja.
*/

int calculate_layer_number(int m)
{
	double sqrt_d = sqrt(static_cast<double>(3 * (4 * m - 1)));
	return static_cast<int>(ceil((3.0 + sqrt_d) / 6.0));
}

pair<int, int> cell_to_hex(int m)
{
	if (m == 1)
		return make_pair(0, 0);
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
		return make_pair(x, y);
	}
}

int main()
{
	while (true) {
		int a, b;
		cin >> a >> b;
		if (!a && !b)
			break;
		pair<int, int> ha = cell_to_hex(a), hb = cell_to_hex(b);
		int dx = ha.first - hb.first, dy = ha.second - hb.second;
		int d = (abs(dx) + abs(dy) + abs(dx + dy)) /2;
		cout << "The distance between cells " << a << " and " << b << " is " << d << ".\n";
	}
	return 0;
}

