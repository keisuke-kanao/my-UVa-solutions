
/*
	UVa 352 - The Seasonal War

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_352_The_Seasonal_War.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int dimension_max = 25;
bool pixels[dimension_max][dimension_max];

void bfs(int i, int j, int n)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	queue< pair<int, int> > q;
	pixels[i][j] = false;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (i < 0 || i >= n || j < 0 || j >= n || !pixels[i][j])
				;
			else {
				pixels[i][j] = false;
				q.push(make_pair(i, j));
			}
		}
	}
}

int main()
{
	int n;
	for (int image_nr = 1; cin >> n; image_nr++) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				char p;
				cin >> p;
				pixels[i][j] = (p == '1') ? true : false;
			}
		int nr_eagles = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (pixels[i][j]) {
					nr_eagles++;
					bfs(i, j, n);
				}
		cout << "Image number " << image_nr << " contains " << nr_eagles <<" war eagles.\n";
	}
	return 0;
}

