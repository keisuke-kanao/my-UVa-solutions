
/*
	UVa 10855 - Rotated square

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10855_Rotated_square.cpp
*/

#include <vector>
#include <cstdio>
using namespace std;

void rotate_square(const vector< vector<char> >& s, vector< vector<char> >& t) // rotate clockwise by 90 degrees
{
	size_t n = s.size();
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			t[i][j] = s[n - j - 1][i];
#ifdef DEBUG
	for (size_t i = 0; i < n; i++)
		printf("%s\n", &t[i][0]);
#endif
}

int count_squares(const vector< vector<char> >&big_square, const vector< vector<char> >&small_square)
{
	int count = 0;
	size_t N = big_square.size(), n = small_square.size();
	for (size_t i = 0; i < N - n + 1; i++)
		for (size_t j = 0; j < N - n + 1; j++) {
			size_t k, l;
			for (k = 0; k < n; k++) {
				for (l = 0; l < n; l++)
					if (big_square[i + k][j + l] != small_square[k][l])
						break;
				if (l < n)
					break;
			}
			if (k == n && l == n)
				count++;
		}
	return count;
}

int main()
{
	while (true) {
		int N, n;
		scanf("%d %d", &N, &n);
		if (!N && !n)
			break;
		vector< vector<char> > big_square(N, vector<char>(N + 1)), small_square(n, vector<char>(n + 1));
		for (int i = 0; i < N; i++)
			scanf("%s", &big_square[i][0]);
		for (int i = 0; i < n; i++)
			scanf("%s", &small_square[i][0]);
		int counts[4];
		counts[0] = count_squares(big_square, small_square);
		vector< vector<char> > rotated_square(n, vector<char>(n + 1));
		rotate_square(small_square, rotated_square);
		counts[1] = count_squares(big_square, rotated_square);
		rotate_square(rotated_square, small_square);
		counts[2] = count_squares(big_square, small_square);
		rotate_square(small_square, rotated_square);
		counts[3] = count_squares(big_square, rotated_square);
		printf("%d %d %d %d\n", counts[0], counts[1], counts[2], counts[3]);
	}
	return 0;
}

