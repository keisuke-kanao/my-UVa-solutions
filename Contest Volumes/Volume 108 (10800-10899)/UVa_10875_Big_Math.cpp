
/*
	UVa 10875 - Big Math

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10875_Big_Math.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_sb_rows = 5, nr_sb_columns = 3, nr_sb_notations = 14, nr_sb_chars_max = 20;
char scoreboard[nr_sb_rows + 1][(nr_sb_columns + 1) * nr_sb_chars_max];
char sb[nr_sb_chars_max + 1];

const char* sb_signs[nr_sb_notations][nr_sb_rows] = {
	{"000", "0.0", "0.0", "0.0", "000"}, // 0
	{".0.", ".0.", ".0.", ".0.", ".0."}, // 1
	{"000", "..0", "000", "0..", "000"}, // 2
	{"000", "..0", "000", "..0", "000"}, // 3
	{"0.0", "0.0", "000", "..0", "..0"}, // 4
	{"000", "0..", "000", "..0", "000"}, // 5
	{"0..", "0..", "000", "0.0", "000"}, // 6
	{"000", "..0", "..0", "..0", "..0"}, // 7
	{"000", "0.0", "000", "0.0", "000"}, // 8
	{"000", "0.0", "000", "..0", "..0"}, // 9
	{".0.", ".0.", "000", ".0.", ".0."}, // +
	{"...", "...", "000", "...", "..."}, // -
	{"0.0", "0.0", ".0.", "0.0", "0.0"}, // *
	{".0.", "...", "000", "...", ".0."}, // /
};

const char sb_chars[nr_sb_notations] = {
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/'
};

char* token_p;
int token, token_n;

int next_token()
{
	while (true) {
		if (*token_p == '\0')
			return token = 0;
		if (isdigit(*token_p)) {
			for (token_n = 0; isdigit(*token_p); token_p++)
				token_n = token_n * 10 + *token_p - '0';
			return token = 'n';
		}
		return token = *token_p++;
	}
}

int next_term()
{
	int r = token_n;
	for (next_token(); ; ) {
		if (token == '*') {
			next_token();
			r *= token_n;
			next_token();
		}
		else if (token == '/') {
			next_token();
			r /= token_n;
			next_token();
		}
		else
			return r;
	}
}

int evaluate()
{
	int r = next_term();
	for (;;) {
		if (token == '+') {
			next_token();
			r += next_term();
		}
		else if (token == '-') {
			next_token();
			r -= next_term();
		}
		else
			return r;
	}
}

int main()
{
	while (true) {
		for (int i = 0; i <= nr_sb_rows; i++)
			gets(scoreboard[i]);
		int nr_sb_chars = 0;
		for (int si = 0, sj = strlen(scoreboard[0]); si < sj; si += nr_sb_columns + 1) {
			int i, j;
			for (i = 0; i < nr_sb_notations; i++) {
				for (j = 0; j < nr_sb_rows; j++)
					if (strncmp(&scoreboard[j][si], sb_signs[i][j], nr_sb_columns))
						break;
				if (j == nr_sb_rows)
					break;
			}
			sb[nr_sb_chars++] = sb_chars[i];
		}
		sb[nr_sb_chars] = '\0';
		if (nr_sb_chars == 1 && sb[0] == '0')
			break;
#ifdef DEBUG
		for (int i = 0; i < nr_sb_chars; i++)
			printf("%c%c", sb[i], ((i < nr_sb_chars - 1) ? ' ' : '\n'));
#endif
		token_p = sb;
		next_token();
		int n = evaluate();
#ifdef DEBUG
		printf("%d\n", n);
#endif
		bool negative = false;
		if (n < 0) {
			negative = true;
			n = -n;
		}
		int si = (nr_sb_columns + 1) * (nr_sb_chars_max - 1);
		while (true) {
			int d = n % 10;
			n /= 10;
			for (int i = 0; i < nr_sb_rows; i++)
				memcpy(&scoreboard[i][si], sb_signs[d][i], nr_sb_columns);
			if (!n && !negative)
				break;
			si--;
			for (int i = 0; i < nr_sb_rows; i++)
				scoreboard[i][si] = ' ';
			si -= nr_sb_columns;
			if (!n) { // negative
				for (int i = 0; i < nr_sb_rows; i++)
					memcpy(&scoreboard[i][si], sb_signs[11][i], nr_sb_columns);
				break;
			}
		}
		for (int i = 0; i < nr_sb_rows; i++)
			puts(&scoreboard[i][si]);
		putchar('\n');
	}
	return 0;
}

