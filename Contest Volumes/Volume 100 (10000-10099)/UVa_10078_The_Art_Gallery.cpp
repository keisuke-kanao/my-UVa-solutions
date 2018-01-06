
/*
	UVa 10078 - The Art Gallery

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10078_The_Art_Gallery.cpp
*/

#include <iostream>
#include <utility>
using namespace std;

const int n_max = 50;
pair<int, int> points[n_max];

/*
	Three points are a counter-clockwise turn if ccw > 0, clockwise if # ccw < 0, and collinear if ccw = 0
*/
int counter_clockwise(const pair<int, int>& p1, const pair<int, int>& p2, const pair<int, int>& p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> points[i].first >> points[i].second;
		bool yes = false;
		int ccw = 0;
		for (int i = 0; i < n; i++) {
			int result = counter_clockwise(points[i], points[(i + 1) % n], points[(i + 2) % n]);
			if (result) {
				if (ccw) {
					if (ccw * result < 0) {
						yes = true;
						break;
					}
				}
				else
					ccw = result;
			}
		}
		cout << ((yes) ? "Yes\n" : "No\n");
	}
	return 0;
}

