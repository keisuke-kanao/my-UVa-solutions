
/*
	UVa 11489 - Integer Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11489_Integer_Game.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_digits_max = 1000;
char n[nr_digits_max + 1];
int digit_counts['9' - '0' + 1];

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		scanf("%s", n);
		int s = 0;
		memset(digit_counts, 0, sizeof(digit_counts));
		for (const char* p = n; *p; p++) {
			int d = *p - '0';
			s += d;
			digit_counts[d]++;
		}
		int nr_turns = 0;
		switch (s % 3) {
		case 0:
			nr_turns = digit_counts[3] + digit_counts[6] + digit_counts[9];
			break;
		case 1:
			if (digit_counts[1] || digit_counts[4] || digit_counts[7])
				nr_turns = digit_counts[3] + digit_counts[6] + digit_counts[9] + 1;
			break;
		case 2:
			if (digit_counts[2] || digit_counts[5] || digit_counts[8])
				nr_turns = digit_counts[3] + digit_counts[6] + digit_counts[9] + 1;
			break;
		}
		printf("Case %d: %c\n", cn, ((nr_turns & 1) ? 'S' : 'T'));
	}
	return 0;
}

