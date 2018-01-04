
/*
	UVa 386 - Perfect Cubes

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_386_Perfect_Cubes.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int a_max = 200;
	// a^3 = b^3 + c^3 + d^3, a, b, c, d > 1
	for (int a = 2; a <= a_max; a++) {
		int as = a * a * a;
		for (int b = 2; ; b++) {
			int bc = b * b * b;
			int bs = as - bc;
			if (bs < bc * 2)
				break;
			for (int c = b; ; c++) {
				int cc = c * c * c;
				int cs = bs - cc;
				if (cs < cc)
					break;
				for (int d = c; ; d++) {
					int ds = cs - d * d * d;
					if (ds <= 0) {
						if (!ds)
							cout << "Cube = " << a << ", Triple = (" << b << ',' << c << ',' << d << ")\n";
						break;
					}
				}
			}
		}
	}
	return 0;
}

