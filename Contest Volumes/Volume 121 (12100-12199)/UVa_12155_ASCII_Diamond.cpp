
/*
	UVa 12155 - ASCII Diamond

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12155_ASCII_Diamond.cpp
*/

const int nr_letters = 'z' - 'a' + 1, col_max = 20000;
char buff[col_max + 2];

#include <cstdio>
#include <cstdlib>

int main()
{
	for (int serial = 1; ; serial++) {
		int N, row1, col1, row2, col2;
		scanf("%d %d %d %d %d", &N, &row1, &col1, &row2, &col2);
		if (!N)
			break;
		printf("Case %d:\n", serial);
		int size = 2 * N - 1, center = N - 1;
		buff[col2 - col1 + 1] = '\0';
		for (int r = row1; r <= row2; r++) {
			char* p = buff;
			for (int c = col1; c <= col2; c++, p++) {
				int i = abs(r % size - center) + abs(c % size - center);
				*p = (i < N) ? 'a' + i % nr_letters: '.';
			}
			puts(buff);
		}
	}
	return 0;
}

