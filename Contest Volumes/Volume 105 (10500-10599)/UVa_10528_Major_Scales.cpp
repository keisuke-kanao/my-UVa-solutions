
/*
	UVa 10528 - Major Scales

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10528_Major_Scales.cpp

	from Waterloo ACM Programming Contest, July 5, 2003, Problem C
		(http://acm.student.cs.uwaterloo.ca/~acm00/030705/data/)
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_notes = 12;

const char* notes[nr_notes] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

const bool scales[nr_notes][nr_notes] = { // scales[i][j] is true if i-th scale has j-th note
//	C 		C#		D		D#		E		F		F#		G		G#		A		A#		B
	{true,	false,	true,	false,	true,	true,	false,	true,	false,	true,	false,	true},	// C
	{true,	true,	false,	true,	false,	true,	true,	false,	true,	false,	true,	false},	// C#
	{false,	true,	true,	false,	true,	false,	true,	true,	false,	true,	false,	true},	// D
	{true,	false,	true,	true,	false,	true,	false,	true,	true,	false,	true,	false},	// D#
	{false,	true,	false,	true,	true,	false,	true,	false,	true,	true,	false,	true},	// E
	{true,	false,	true,	false,	true,	true,	false,	true,	false,	true,	true,	false},	// F
	{false,	true,	false,	true,	false,	true,	true,	false,	true,	false,	true,	true},	// F#
	{true,	false,	true,	false,	true,	false,	true,	true,	false,	true,	false,	true},	// G
	{true,	true,	false,	true,	false,	true,	false,	true,	true,	false,	true,	false},	// G#
	{false,	true,	true,	false,	true,	false,	true,	false,	true,	true,	false,	true},	// A
	{true,	false,	true,	true,	false,	true,	false,	true,	false,	true,	true,	false},	// A#
	{false,	true,	false,	true,	true,	false,	true,	false,	true,	false,	true,	true}	// B
};

int get_note(const char* s)
{
	for (int i = 0; i < nr_notes; i++)
		if (!strcmp(s, notes[i]))
			return i;
	return -1;
}

int main()
{
	while (true) {
		const int nr_chars_max = 1000;
		char s[nr_chars_max + 1];
		gets(s);
		if (!strcmp(s, "END"))
			break;
		bool impossible_scales[nr_notes];
		memset(impossible_scales, 0, sizeof(impossible_scales));
		for (char *p = s, *q = s; *q; q = p) {
			for ( ; *p && !isspace(*p); p++)
				;
			if (p - q) {
				if (*p) {
					*p++ = '\0';
					for ( ; *p && isspace(*p); p++)
						;
				}
				int n = get_note(q);
				for (int i = 0; i < nr_notes; i++)
					if (!scales[i][n])
						impossible_scales[i] = true;
			}
		}
		bool printed = false;
		for (int i = 0; i < nr_notes; i++)
			if (!impossible_scales[i]) {
				if (printed)
					putchar(' ');
				else
					printed = true;
				printf("%s", notes[i]);
			}
		putchar('\n');
	}
	return 0;
}

