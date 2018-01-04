
/*
	UVa 11697 - Playfair Cipher

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11697_Playfair_Cipher.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_letters = 26, nr_chars_max = 1000;
bool letters[nr_letters];
char s[nr_chars_max + 1];
const int nr_rows = 5, nr_columns = 5;
char table[nr_rows][nr_columns];

void get_pos(char l, int& r, int& c)
{
	for (r = 0; r < nr_rows; r++)
		for (c = 0; c < nr_columns; c++)
			if (table[r][c] == l)
				return;
}

void encrypt(char l1, char l2)
{
	int r1, c1, r2, c2;
	get_pos(l1, r1, c1);
	get_pos(l2, r2, c2);
	if (r1 == r2) {
		if (++c1 == nr_columns)
			c1 = 0;
		putchar(table[r1][c1]);
		if (++c2 == nr_columns)
			c2 = 0;
		putchar(table[r1][c2]);
	}
	else if (c1 == c2) {
		if (++r1 == nr_rows)
			r1 = 0;
		putchar(table[r1][c1]);
		if (++r2 == nr_rows)
			r2 = 0;
		putchar(table[r2][c1]);
	}
	else {
		putchar(table[r1][c2]);
		putchar(table[r2][c1]);
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	while (N--) {
		memset(letters, 0, sizeof(letters));
		letters['Q' - 'A'] = true;
		memset(table, 0, sizeof(table));
		gets(s);
		int r = 0, c = 0;
		for (const char* p = s; *p; p++)
			if (isalpha(*p)) {
				char l = toupper(*p);
				if (!letters[l - 'A']) {
					letters[l - 'A'] = true;
					table[r][c++] = l;
					if (c == nr_columns) {
						c = 0; r++;
					}
				}
			}
		for (int i = 0; i < nr_letters; i++)
			if (!letters[i]) {
				table[r][c++] = 'A' + i;
				if (c == nr_columns) {
					c = 0; r++;
				}
			}

#ifdef DEBUG
	for (int r = 0; r < nr_rows; r++)
		for (int c = 0; c < nr_columns; c++)
			printf("%c%c", table[r][c], ((c < nr_columns - 1) ? ' ' : '\n'));
#endif

		gets(s);
		char pl = 0;
		for (const char* p = s; *p; p++)
			if (isalpha(*p)) {
				char l = toupper(*p);
				if (pl) {
					if (pl == l) {
						encrypt(pl, 'X');
						pl = l;
					}
					else {
						encrypt(pl, l);
						pl = 0;
					}
				}
				else
					pl = l;
			}
		if (pl)
			encrypt(pl, 'X');
		putchar('\n');
	}
	return 0;
}

