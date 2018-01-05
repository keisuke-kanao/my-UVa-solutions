
/*
	UVa 10284 - Chessboard in FEN

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10284_Chessboard_in_FEN.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_rows = 8, nr_columns = 8;
char chessboard[nr_rows][nr_columns], fen[nr_rows * (nr_columns + 1) + 1];

bool attack(int r, int c)
{
	if (r < 0 || r >= nr_rows || c < 0 || c >= nr_columns || isalpha(chessboard[r][c]))
		return false;
	chessboard[r][c] = '+';
	return true;
}

void king_attack(int r, int c)
{
	for (int ri = r - 1; ri <= r + 1; ri++)
		for (int ci = c - 1; ci <= c + 1; ci++)
			if (ri != r || ci != c)
				attack(ri, ci);
}

void rook_attack(int r, int c)
{
	int ri, ci;
	for (ri = r - 1; ; ri--)
		if (!attack(ri, c))
			break;
	for (ri = r + 1; ; ri++)
		if (!attack(ri, c))
			break;
	for (ci = c - 1; ; ci--)
		if (!attack(r, ci))
			break;
	for (ci = c + 1; ; ci++)
		if (!attack(r, ci))
			break;
}

void bishop_attack(int r, int c)
{
	int ri, ci;
	for (ri = r - 1, ci = c - 1; ; ri--, ci--)
		if (!attack(ri, ci))
			break;
	for (ri = r - 1, ci = c + 1; ; ri--, ci++)
		if (!attack(ri, ci))
			break;
	for (ri = r + 1, ci = c - 1; ; ri++, ci--)
		if (!attack(ri, ci))
			break;
	for (ri = r + 1, ci = c + 1; ; ri++, ci++)
		if (!attack(ri, ci))
			break;
}

void knight_attack(int r, int c)
{
	attack(r - 2, c - 1);
	attack(r - 2, c + 1);
	attack(r - 1, c - 2);
	attack(r - 1, c + 2);
	attack(r + 1, c - 2);
	attack(r + 1, c + 2);
	attack(r + 2, c - 1);
	attack(r + 2, c + 1);
}

#ifdef DEBUG
void print_chessboard()
{
	for (int r = 0; r < nr_rows; r++)
		for (int c = 0; c < nr_columns; c++)
		printf("%c%c", chessboard[r][c], ((c == nr_columns - 1) ? '\n' : ' '));
}
#endif

int main()
{
	while (scanf("%s", fen) != EOF) {
		memset(chessboard, '-', sizeof(chessboard));
		int r = 0, c = 0;
		for (const char* p = fen; *p; p++) {
			if (*p == '/') {
				r++; c = 0;
			}
			else if (isdigit(*p))
				c += *p - '0';
			else
				chessboard[r][c++] = *p;
		}
		for (r = 0; r < nr_rows; r++)
			for (c = 0; c < nr_columns; c++) {
				switch (chessboard[r][c]) {
				case 'k': case 'K':
					king_attack(r, c);
					break;
				case 'q': case 'Q':
					rook_attack(r, c);
					bishop_attack(r, c);
					break;
				case 'b': case 'B':
					bishop_attack(r, c);
					break;
				case 'n': case 'N':
					knight_attack(r, c);
					break;
				case 'r': case 'R':
					rook_attack(r, c);
					break;
				case 'p':
					attack(r + 1, c - 1);
					attack(r + 1, c + 1);
					break;
				case 'P':
					attack(r - 1, c - 1);
					attack(r - 1, c + 1);
					break;
				}
#ifdef DEBUG
				if (isalpha(chessboard[r][c])) {
					printf("%d %d: %c\n", r, c, chessboard[r][c]);
					print_chessboard();
				}
#endif
			}
		int nr_unoccupied = 0;
		for (r = 0; r < nr_rows; r++)
			for (c = 0; c < nr_columns; c++)
				if (chessboard[r][c] == '-')
					nr_unoccupied++;
		printf("%d\n", nr_unoccupied);
	}
	return 0;
}

