
/*
	12.6.1 Ant on a Chessboard
	PC/UVa IDs: 111201/10161, Popularity: B, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10161_Ant_on_a_Chessboard.cpp
*/

/*

/*

7 |	49 48 47 46 45 44 43
6 |	26 27 28 29 30 31 42
5 |	25 24 23 22 21 32 41
4 |	10 11 12 13 20 33 40
3 |	 9  8  7 14 19 34 39
2 |	 2  3  6 15 18 35 38
1 |	 1  4  5 16 17 36 37
  +---------------------
	 1  2  3  4  5  6  7
*/

#include <iostream>
#include <utility>
#include <cmath>
using namespace std;

pair<int, int> get_square(int n)
{
	int square_root = static_cast<int>(sqrt(static_cast<double>(n)));
	pair<int, int> square;
	if (square_root * square_root == n)
		square = pair<int, int>(square_root, 1);
	else {
		int next_square_root = square_root + 1;
		if (n - square_root * square_root > square_root)
			square = pair<int, int>(next_square_root * next_square_root - n + 1, next_square_root);
		else
			square = pair<int, int>(next_square_root, n - square_root * square_root);
	}
	if (square_root & 1)
		swap(square.first, square.second);
	return square;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		pair<int, int> square = get_square(n);
		cout << square.first << ' ' << square.second << endl;
	}
	return 0;
}

