
/*
	UVa 213 - Message Decoding

	To build using Visucal Studio 2010:
		cl -EHsc UVa_213_Message_Decoding.cpp

	from ACM ICPC World Finals - 1991 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/A_FINALS/1991/index.html)
*/

#include <cstdio>

int read_digits(int n)
{
	int d = 0, c;
	while (n--) {
		d <<= 1;
		while ((c = getchar()) == '\n')
			;
		d += c - '0';
	}
	return d;
}

int main()
{
	char chars_map[1 + 3 + 7 + 15 + 31 + 63 + 127];
	const int chars_map_indices[] = {-1, 0, 1, 4, 11, 26, 57, 120};
		// chars_map_indices[i] is the index to chars_map[] for the key length of i (i = 1, 2, 3, 4, 5, 6, 7)
	const int terminaters[] = {0, 1, 3, 7, 15, 31, 63, 127};
		// terminaters[i] is the terminater for the key length of i (i = 1, 2, 3, 4, 5, 6, 7)
	while (true) {
		int c = getchar();
		if (c == EOF)
			break;
		else if (c == '\n')
			continue;
		// read a header
		char* p = chars_map;
		do
			*p++ = static_cast<char>(c);
		while ((c = getchar()) != '\n');
		int length;
		while (length = read_digits(3)) {
			char* q = &chars_map[chars_map_indices[length]];
			int i, t = terminaters[length];
			while ((i = read_digits(length)) != t)
				putchar(*(q + i));
		}
		putchar('\n');
	}
	return 0;
}

