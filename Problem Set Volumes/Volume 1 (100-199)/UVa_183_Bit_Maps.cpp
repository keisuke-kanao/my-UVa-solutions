
/*
	UVa 183 - Bit Maps

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_183_Bit_Maps.cpp

	from ACM South Pacific Regionals 1993 Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1993/index.html)
*/

#include <cstdio>

const int rows_max = 200, columns_max = 200;
int bitmap[rows_max][columns_max];
int sums[rows_max][columns_max];
	// sum[i][j] is the sum of bitmap[bi][bj] (0 <= bi <= i, 0 <= bj <= j)
const int nr_chars_max = 50;
int nr_chars;

int zeros_ones(int top, int left, int bottom, int right)
{
	int s = sums[bottom][right];
	if (top && left)
		s += sums[top - 1][left - 1] - sums[top - 1][right] - sums[bottom][left - 1];
	else if (top)
		s -= sums[top - 1][right];
	else if (left)
		s -= sums[bottom][left - 1];
	if (!s)
		return 0; // all zeros
	else if (s == (bottom - top + 1) * (right - left + 1))
		return 1; // all ones
	else
		return -1;
}

void bitmap_putchar(char c)
{
	putchar(c);
	if (++nr_chars == nr_chars_max) {
		nr_chars = 0;
		putchar('\n');
	}
}

void quarters(int top, int left, int bottom, int right)
{
	int zo = zeros_ones(top, left, bottom, right);
	if (zo >= 0) // all zeros or ones
		bitmap_putchar(static_cast<char>(zo + '0'));
	else {
		bitmap_putchar('D');
		int rows = bottom - top + 1, columns = right - left + 1;
		if (rows > 1 && columns > 1) {
			quarters(top, left, top + (rows - 1) / 2, left + (columns - 1) / 2);
			quarters(top, left + (columns + 1) / 2, top + (rows - 1) / 2,  right);
			quarters(top + (rows + 1) / 2, left, bottom, left + (columns - 1) / 2);
			quarters(top + (rows + 1) / 2, left + (columns + 1) / 2, bottom, right);
		}
		else if (rows > 1) {
			quarters(top, left, top + (rows - 1) / 2, right);
			quarters(top + (rows + 1) / 2, left, bottom, right);
		}
		else {
			quarters(top, left, bottom, left + (columns - 1) / 2);
			quarters(top, left + (columns + 1) / 2, bottom,  right);
		}
	}
}

void decomposition(int rows, int columns)
{
	for (int r = 0; r < rows; r++) {
		int ones = 0;
		for (int c = 0; c < columns; c++) {
			char zero_or_one;
			do
				zero_or_one = getchar();
			while (zero_or_one == '\n');
			bitmap[r][c] = zero_or_one - '0';
			ones += bitmap[r][c];
			sums[r][c] = ones;
			if (r)
				sums[r][c] += sums[r - 1][c];
		}
	}
#ifdef DEBUG
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			fprintf(stderr, "%4d%c", bitmap[r][c], ((c == columns - 1) ? '\n' : ' '));
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			fprintf(stderr, "%4d%c", sums[r][c], ((c == columns - 1) ? '\n' : ' '));
#endif
	quarters(0, 0, rows - 1, columns - 1);
	if (nr_chars)
		putchar('\n');
}

void composition(int top, int left, int bottom, int right)
{
	char c;
	do
		c = getchar();
	while (c == '\n');
	if (c == '0' || c == '1') {
		c -= '0';
		for (int i = top; i <= bottom; i++)
			for (int j = left; j <= right; j++)
				bitmap[i][j] = c;
	}
	else { // 'D'
		int rows = bottom - top + 1, columns = right - left + 1;
		if (rows > 1 && columns > 1) {
			composition(top, left, top + (rows - 1) / 2, left + (columns - 1) / 2);
			composition(top, left + (columns + 1) / 2, top + (rows - 1) / 2,  right);
			composition(top + (rows + 1) / 2, left, bottom, left + (columns - 1) / 2);
			composition(top + (rows + 1) / 2, left + (columns + 1) / 2, bottom, right);
		}
		else if (rows > 1) {
			composition(top, left, top + (rows - 1) / 2, right);
			composition(top + (rows + 1) / 2, left, bottom, right);
		}
		else {
			composition(top, left, bottom, left + (columns - 1) / 2);
			composition(top, left + (columns + 1) / 2, bottom,  right);
		}
	}
}

int main()
{
	while (true) {
		char format[2];
		scanf("%s", format);
		if (format[0] == '#')
			break;
		int rows, columns;
		scanf("%d %d", &rows, &columns);
		nr_chars = 0;
		if (format[0] == 'B') {
			printf("%c%4d%4d\n", 'D', rows, columns);
			decomposition(rows, columns);
		}
		else {
			composition(0, 0, rows - 1, columns - 1);
			printf("%c%4d%4d\n", 'B', rows, columns);
			for (int r = 0; r < rows; r++)
				for (int c = 0; c < columns; c++)
					bitmap_putchar(static_cast<char>(bitmap[r][c] + '0'));
				if (nr_chars)
					putchar('\n');
		}
	}
	return 0;
}

