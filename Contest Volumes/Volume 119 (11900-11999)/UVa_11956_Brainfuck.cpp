
/*
	UVa 11956 - Brainfuck

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11956_Brainfuck.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_bytes = 100, nr_chars_max = 100000;
unsigned char memory[nr_bytes], s[nr_chars_max + 1];

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%s", s);
		memset(memory, 0, sizeof(memory));
		int mi = 0;
		for (const unsigned char* p = s; *p; p++)
			switch (*p) {
			case '>':
				mi = (mi + 1) % nr_bytes; break;
			case '<':
				mi = (mi + nr_bytes - 1) % nr_bytes; break;
			case '+':
				memory[mi]++; break;
			case '-':
				memory[mi]--; break;
			default:
				break;
			}
		printf("Case %d:", t);
		for (int i = 0; i < nr_bytes; i++)
			printf(" %02X", memory[i]);
		putchar('\n');
	}
	return 0;
}

