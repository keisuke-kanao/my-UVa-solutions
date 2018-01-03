
/*
	UVa 737 - Gleaming the Cubes

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_737_Gleaming_the_Cubes.cpp
*/

#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

bool get_overlapped_range(const pair<int, int>& i, const pair<int, int>& j, pair<int, int>& k)
{
	k.first = max(i.first, j.first);
	k.second = min(i.second, j.second);
	return (k.first < k.second) ? true : false;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int d;
		pair<int, int> px, py, pz, cx, cy, cz, nx, ny, nz;
		cin >> px.first >> py.first >> pz.first >> d;
		px.second = px.first + d; py.second = py.first + d; pz.second = pz.first + d;
		bool intersection = true;
		while (--n) {
			cin >> cx.first >> cy.first >> cz.first >> d;
			if (intersection) {
				cx.second = cx.first + d; cy.second = cy.first + d; cz.second = cz.first + d;
				if (get_overlapped_range(px, cx, nx) && get_overlapped_range(py, cy, ny) && get_overlapped_range(pz, cz, nz)) {
					px = nx; py = ny; pz = nz;
				}
				else
					intersection = false;
			}
		}
		if (intersection)
			cout << (px.second - px.first) * (py.second - py.first) * (pz.second - pz.first) << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}

