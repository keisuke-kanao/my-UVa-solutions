
/*
	UVa 10703 - Free spots

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10703_Free_spots.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int max_width = 500, max_height = 500;
bool matrix[max_height + 1][max_width + 1];

int main()
{
	while (true) {
		int w, h, n;
		cin >> w >> h >> n;
		if (!w && !h && !n)
			break;
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				matrix[i][j] = false;
		for (int k = 0; k < n; k++) {
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 > x2)
				swap(x1, x2);
			if (y1 > y2)
				swap(y1, y2);
			for (int i = y1; i <= y2; i++)
				for (int j = x1; j <= x2; j++)
					matrix[i][j] = true;
		}
		int nr_free_spots = 0;
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				if (!matrix[i][j])
					nr_free_spots++;
		if (!nr_free_spots)
			cout << "There is no empty spots.\n";
		else if (nr_free_spots == 1)
			cout << "There is one empty spot.\n";
		else
			cout << "There are " << nr_free_spots << " empty spots.\n";
	}
	return 0;
}

