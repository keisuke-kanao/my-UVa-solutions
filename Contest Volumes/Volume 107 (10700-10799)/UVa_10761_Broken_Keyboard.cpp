
/*
	UVa 10761 - Broken Keyboard

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10761_Broken_Keyboard.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

int main()
{
	puts("+----------+----------------+-----------------------------+");
	puts("| Keyboard | # of printable | Additionally, the following |");
	puts("|          |      lines     |  letter keys can be broken  |");
	puts("+----------+----------------+-----------------------------+");
	for (int k = 1; ; k++) {
		const int nr_chars_max = 80;
		char s[nr_chars_max + 1];
		gets(s);
		if (!strcmp(s, "finish"))
			break;
		const int nr_letters = 128;
		bool broken_letters[nr_letters], can_be_broken_letters[nr_letters];
		memset(broken_letters, 0, sizeof(broken_letters));
		memset(can_be_broken_letters, -1, sizeof(can_be_broken_letters));
		for (const char* p = s; *p; p++) {
			int c = tolower(*p);
			broken_letters[c] = true;
			can_be_broken_letters[c] = false;
		}
		int nr_printable_lines = 0;
		do {
			gets(s);
			bool printable = true;
			for (const char* p = s; *p; p++)
				if (broken_letters[tolower(*p)]) {
					printable = false;
					break;
				}
			if (printable) {
				nr_printable_lines++;
				for (const char* p = s; *p; p++)
					can_be_broken_letters[tolower(*p)] = false;
			}
		} while (strcmp(s, "END"));
		sprintf(s, "|   %3d    |      %3d       |                             |", k, nr_printable_lines);
		char* p = &s[30];
		for (int i = 'a'; i <= 'z'; i++)
			if (can_be_broken_letters[i])
				*p++ = i;
		puts(s);
		puts("+----------+----------------+-----------------------------+");
	}
	return 0;
}

