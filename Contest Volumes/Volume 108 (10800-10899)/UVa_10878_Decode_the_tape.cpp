
/*
	UVa 10878 - Decode the tape

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10878_Decode_the_tape.cpp
*/

#include <cstdio>

int main()
{
	const int nr_chrs = 16;
	char line[nr_chrs];
/*
	bool start = false;
*/
	while (gets(line)) {
		if (line[0] != '|') {
/*
			if (start)
				break;
			start = true;
*/
			continue;
		}
		char c = 0;
		for (int i = 1; i < 10; i++) {
			if (i > 1 && line[i] != '.')
				c <<= 1;
			if (line[i] == 'o')
				c |= 1;
		}
		putchar(c);
	}
	return 0;
}

