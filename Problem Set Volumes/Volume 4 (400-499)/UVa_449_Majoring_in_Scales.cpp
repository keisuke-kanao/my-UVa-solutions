
/*
	UVa 449 - Majoring in Scales

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_449_Majoring_in_Scales.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_keys = 12, nr_notes = 7, nr_intervals = 7;

const char* major_keys[nr_keys][nr_notes] = {
	{"C",	"D",	"E",	"F",	"G",	"A",	"B"},
	{"Db",	"Eb",	"F",	"Gb",	"Ab",	"Bb",	"C"},
	{"D",	"E",	"F#",	"G",	"A",	"B",	"C#"},
	{"Eb",	"F",	"G",	"Ab",	"Bb",	"C",	"D"},
	{"E",	"F#",	"G#",	"A",	"B",	"C#",	"D#"},
	{"F",	"G",	"A",	"Bb",	"C",	"D",	"E"},
	{"Gb",	"Ab",	"Bb", 	"Cb",	"Db",	"Eb",	"F"},
	{"G",	"A",	"B",	"C",	"D",	"E",	"F#"},
	{"Ab",	"Bb",	"C",	"Db",	"Eb",	"F",	"G"},
	{"A",	"B",	"C#",	"D",	"E",	"F#",	"G#"},
	{"Bb",	"C",	"D",	"Eb",	"F",	"G",	"A"},
	{"B",	"C#",	"D#",	"E",	"F#",	"G#",	"A#"}
};

const char* intervals[nr_intervals] = {
	"OCTAVE", "SECOND", "THIRD", "FOURTH", "FIFTH", "SIXTH", "SEVENTH"
};

int main()
{
	int i, n;
	char scale[4];
	while (scanf("%s", scale) != EOF) {
		const char* (*pkey)[nr_notes];
		for (i = 0; i < nr_keys; i++)
			if (!strcmp(scale, major_keys[i][0])) {
				pkey = &major_keys[i];
				break;
			}
		printf("Key of %s\n", scale);
		char note[4], dir[8], interval[16];
		scanf("%s %s %s", note, dir, interval);
		while (true) {
			char* p = strchr(interval, ';');
			bool next = false;
			if (p) {
				*p = '\0';
				next = true;
			}
			for (n = 0; n < nr_notes; n++)
				if (!strcmp(note, (*pkey)[n]))
					break;
			if (n == nr_notes)
				printf("%s: invalid note for this key\n", note);
			else {
				for (i = 0; i < nr_intervals; i++)
					if (!strcmp(interval, intervals[i]))
						break;
				if (dir[0] == 'U') {
					n += i;
					if (n >= nr_notes)
						n -= nr_notes;
				}
				else {
					n -= i;
					if (n < 0)
						n += nr_notes;
				}
				printf("%s: %s %s > %s\n", note, dir, interval, (*pkey)[n]);
			}
			if (next) {
				strcpy(note, p + 1);
				scanf("%s %s", dir, interval);
			}
			else
				break;
		}
		putchar('\n');
	}
	return 0;
}

