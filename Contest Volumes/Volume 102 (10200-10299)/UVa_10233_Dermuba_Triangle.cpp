
/*
	12.6.7 Dermuba Triangle
	PC/UVa IDs: 111207/10233, Popularity: C, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10233_Dermuba_Triangle.cpp
*/

/*
	Apply the triangular coordinates to Dermuba Triangle.
	Use the row and column dimensions (row, column) to define the coordinate system:
		The top vertex the triangular region is (0, 0).
		The left side of the triangular region is mappted to column = 1.
		The base of the triangle in which the house 0 resides is mapped to row = -1, 
			the bases of the triangles in which the house 1, 2, and 3 is mapped to row = -2, and so on.
	Then:
		The left-most triangle of each row has the house number of n^2 (n >= 0) and 
			succesive triangles have the house number of n^2, n^2 + 1, n^2 +3, ..., n^2 + 2 * n.
		Those triangles have the top vertices of (-n, 0), (-n, 1), ...(-n, n) and 
		base vertices of (-(n + 1), 0), (-(n + 1), 1), .... (-(n + 1), n + 1).

	For the triangles of house number = n^2 + 2 * i (i = 0, 1, ..., n)
		the incenter of the triangle = (i - n / 2, - sqrt(3) * n / 2 - sqrt(3) / 3).
	For the triangles of house number = n^2 + 2 * i + 1 (i = 0, 1, ..., n - 1)
		the incenter of the triangle = (i + 1 - (n + 1) / 2, - sqrt(3) * (n + 1) / 2 + sqrt(3) / 3).
*/

#include <iostream>
#include <utility>
#include <cstdio>
#include <cmath>
using namespace std;

pair<double, double> get_incenter_of_triangle(int hn /* house number */)
{
	int n = static_cast<int>(sqrt(static_cast<double>(hn)));
	int i = (hn - n * n) / 2;
	double x, y;
	if ((hn - n) & 1) { // hn = n^2 + 2 * i + 1 (i = 0, 1, ..., n - 1)
		x = static_cast<double>(i) + 1.0 - (static_cast<double>(n) + 1.0) / 2.0;
		y = -sqrt(3.0) * (static_cast<double>(n) + 1.0) / 2.0 + sqrt(3.0) / 3.0;
	}
	else { // hn =  = n^2 + 2 * i (i = 0, 1, ..., n)
		x = static_cast<double>(i) - static_cast<double>(n) / 2.0;
		y = -sqrt(3.0) * static_cast<double>(n) / 2.0 - sqrt(3.0) / 3.0;
	}
	return pair<double, double>(x, y);
}

int main(int /* argc */, char** /* argv */)
{
	int n, m;
	while (cin >> n >> m) {
		pair<double, double> ni = get_incenter_of_triangle(n);
#ifdef DEBUG
		printf("(%.3f, %.3f)\n", ni.first, ni.second);
#endif
		pair<double, double> mi = get_incenter_of_triangle(m);
#ifdef DEBUG
		printf("(%.3f, %.3f)\n", mi.first, mi.second);
#endif
		double d = sqrt(pow(ni.first - mi.first, 2) + pow(ni.second - mi.second, 2));
		printf("%.3f\n", d);
	}
	return 0;
}

