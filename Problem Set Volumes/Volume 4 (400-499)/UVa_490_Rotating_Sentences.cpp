
/*
	UVa 490 - Rotating Sentences

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_490_Rotating_Sentences.cpp
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	const int nr_chars_max = 100, nr_lines_max = 100;
	char sentences[nr_lines_max][nr_chars_max + 1];
	int lengths[nr_lines_max], max_lengths[nr_lines_max];
	int nr_lines = 0;
	int max_length = 0;
	while (gets(sentences[nr_lines])) {
		lengths[nr_lines] = strlen(sentences[nr_lines]);
		max_length = max(max_length, lengths[nr_lines]);
		max_lengths[nr_lines] = max_length;
		nr_lines++;
	}
	for (int c = 0; c < max_length; c++) {
		for (int l = nr_lines - 1; l >= 0; l--) {
/*
			if (max_lengths[l] <= c)
				break;
*/
			putchar((c < lengths[l]) ? sentences[l][c] : ' ');
		}
		putchar('\n');
	}
	return 0;
}

