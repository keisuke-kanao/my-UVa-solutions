
/*
	UVa 433 - Bank (Not Quite O.C.R.)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_433_Bank.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_digit_columns = 3, nr_digit_rows = 3, nr_digits = 10, nr_account_digits = 9;
	char segs[nr_digit_rows][nr_digit_columns * nr_account_digits + 1];
const int digit_patterns[nr_digits] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
/*
individual segments of seven-segment display
   GFEDCBA
0: 0111111 3f
1: 0000110 06
2: 1011011 5b
3: 1001111 4f
4: 1100110 66
5: 1101101 6d
6: 1111101 7d
7: 0000111 07
8: 1111111 7f
9: 1101111 6f
*/

struct digit {
	int pattern_, number_, deduced_;
} digits[nr_account_digits];


int read_digit(int di, int ci)
{
	int p = 0;
	if (segs[0][ci + 1] == '_')
		p |= 0x01;
	if (segs[1][ci + 2] == '|')
		p |= 0x02;
	if (segs[2][ci + 2] == '|')
		p |= 0x04;
	if (segs[2][ci + 1] == '_')
		p |= 0x08;
	if (segs[2][ci] == '|')
		p |= 0x10;
	if (segs[1][ci] == '|')
		p |= 0x20;
	if (segs[1][ci + 1] == '_')
		p |= 0x40;
	digits[di].pattern_ = p;
	digits[di].number_ = -1;
	for (int i = 0; i < nr_digits; i++)
		if (digit_patterns[i] == p) {
			digits[di].number_ = i;
			break;
		}
	return digits[di].number_;
}

bool checksum()
{
	int s = 0;
	for (int i = 0, j = 9; i < nr_account_digits; i++, j--) {
		if (digits[i].number_ == -1)
			return false;
		s += digits[i].number_ * j;
	}
	return (s % 11) ? false : true;
}

void print_digits()
{
	for (int i = 0; i < nr_account_digits; i++)
		printf("%c", ((digits[i].number_ != -1) ? '0' + digits[i].number_ : '?'));
	putchar('\n');
}

int main()
{
	int nr_numbers;
	scanf("%d", &nr_numbers);
	while (getchar() != '\n')
		;
	while (nr_numbers--) {
		memset(segs, 0, sizeof(segs));
		for (int i = 0; i < nr_digit_rows; i++)
			gets(segs[i]);
		int garbled = -1;
		for (int i = 0; i < nr_account_digits; i++)
			if (read_digit(i, i * nr_digit_columns) == -1)
				garbled = i;
#ifdef DEBUG
		print_digits();
#endif
		int ctr = 0;
		if (garbled != -1) {
			digit& d = digits[garbled];
			for (int i = 0; i < nr_digits; i++)
				if (!d.pattern_ ||
					d.pattern_ & digit_patterns[i] && !(d.pattern_ & ~digit_patterns[i])) {
					d.number_ = i;
					if (checksum()) {
						d.deduced_ = i;
						ctr++;
					}
				}
			if (ctr == 1)
				d.number_ = d.deduced_;
		}
		else if (checksum())
			ctr = 1;
		else {
			int di;
			for (int i = 0; i < nr_account_digits && ctr < 2; i++) {
				digit&d = digits[i];
				if (digits[i].pattern_ == 0x7f)
					continue;
				int n = d.number_;
				for (int j = 0; j < nr_digits && ctr < 2; j++)
					if (d.pattern_ & digit_patterns[j] && !(d.pattern_ & ~digit_patterns[j])) {
						d.number_ = j;
						if (checksum()) {
							di = i;
							d.deduced_ = j;
							ctr++;
						}
					}
				d.number_ = n;
			}
			if (ctr == 1)
				digits[di].number_ = digits[di].deduced_;
		}
		if (ctr > 1)
			puts("ambiguous");
		else if (ctr == 1)
			print_digits();
		else
			puts("failure");
	}
	return 0;
}

