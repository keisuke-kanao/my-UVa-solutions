
/*
	13.6.6 The Largest/Smallest Box ...
	PC/UVa IDs: 111306/10215, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10215_The_Largest_Smallest_Box.cpp
*/

/*
	Let f(x) be the volume of the box, then:
		f(x) = x(W - 2x)(L - 2x) = 4x^3 - 2(W + L)x^2 + WLx
	And its derived function:
		f'(x) = 12x^2 - 4(W + L)x + WL
	According to calculus, f(x) has its local maximum and minimum values at
	x = a, b where a < b and f'(a) = f'(b) = 0, respectively.
	Solving f'(x) = 0, we get x = (1 / 6){(W + L) +/- sqrt(W^2 - WL + L^2)}.
	Then, f(x) has its maximum value at x = (1 / 6){(W + L) - sqrt(W^2 - WL + L^2)}.
	For its minimum values, x = 0, the smaller of either W / 2 or L / 2.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	const double epsilon = 1.0e-6; // to work around the rounding problem
	double l, w;
	while(cin >> l >> w) {
		double d = sqrt(w * w - w * l + l * l);
		double maximum = ((w + l) - d) / 6.0;
		double minimum = (l > w) ? w / 2 : l / 2;
		printf("%.3f 0.000 %.3f\n", maximum + epsilon, minimum + epsilon);
	}
	return 0;
}

