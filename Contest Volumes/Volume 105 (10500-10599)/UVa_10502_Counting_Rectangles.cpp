
/*
	UVa 10502 - Counting Rectangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10502_Counting_Rectangles.cpp

	An accepted solution.
*/

#include <iostream>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 100, m_max = 100;
int matrix[n_max + 1][m_max + 1]; // dominance matrix

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		cin >> m;
		// generate a dominance matrix
		for (int y = 1; y <= n; y++)
			for (int x = 1, s = 0; x <= m; x++) {
				char c;
				cin >> c;
				if (c == '0')
					s++;
				matrix[y][x] = s + matrix[y - 1][x];
			}
		int nr_rectangles = 0;
		for (int ys = 1; ys <= n; ys++)
			for (int xs = 1; xs <= m; xs++) {
				int s = matrix[ys - 1][xs - 1];
				for (int ye = ys; ye <= n; ye++)
					for (int xe = xs; xe <= m; xe++)
						if (!(matrix[ye][xe] - matrix[ys - 1][xe] - matrix[ye][xs - 1] + s))
							nr_rectangles++;
			}
		cout << nr_rectangles << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

