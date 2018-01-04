
/*
	UVa 346 - Getting Chorded

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_346_Getting_Chorded.cpp

	from ACM North Central Regionals - 1996, Problem B
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1996/prob_b.html)
*/

#include <cstdio>
#include <cstring>
#include <cctype>

#ifdef ONLINE_JUDGE
#define _stricmp strcasecmp
#endif

const int nr_chars_max = 3, nr_notes = 3, index_max = 12;

struct note {
	char s_[nr_chars_max + 1];
	int ci_, i_;
};

const note chromatic_notes[] = {
	{"A", 0}, {"A#", 1}, {"Bb", 1}, {"B", 2}, {"Cb", 2}, {"B#", 3}, {"C", 3},{"C#", 4}, {"Db", 4}, {"D", 5}, {"D#", 6},
	{"Eb", 6}, {"E", 7}, {"Fb", 7}, {"E#", 8}, {"F", 8}, {"F#", 9}, {"Gb", 9}, {"G", 10}, {"G#", 11}, {"Ab", 11}
};

void get_index(note& n)
{
	int i;
	for (i = 0; i < sizeof(chromatic_notes) / sizeof(note); i++)
		if (!_stricmp(n.s_, chromatic_notes[i].s_))
			break;
	n.ci_ = chromatic_notes[i].ci_; n.i_ = i;
}

const char* get_key(const note& n)
{
	int i = n.i_;
	if (n.s_[1] == 'b')
		i--;
	else if (n.s_[1] == '#') {
		if (chromatic_notes[i].s_[0] == 'B' || chromatic_notes[i].s_[0] == 'E')
			i++;
	}
	return chromatic_notes[i].s_;
}

int main()
{
	const int perms[][nr_notes] = {
		{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
	};

	note notes[nr_notes];
	while (scanf("%s %s %s", notes[0].s_, notes[1].s_, notes[2].s_) != EOF) {
		for (int i = 0; i < nr_notes; i++)
			get_index(notes[i]);
		bool recognized = false;
		for (size_t i = 0; i < sizeof(perms) / sizeof(perms[0]); i++) {
			int third = notes[perms[i][1]].ci_ - notes[perms[i][0]].ci_, fifth = notes[perms[i][2]].ci_ - notes[perms[i][0]].ci_;
			char key[nr_chars_max + 1];
			if (third < 0)
				third += index_max;
			if (fifth < 0)
				fifth += index_max;
			if (third == 4 && fifth == 7) {
				recognized = true;
				printf("%s %s %s is a %s Major chord.\n", notes[0].s_, notes[1].s_, notes[2].s_, get_key(notes[perms[i][0]]));
				break;
			}
			else if (third == 3 && fifth == 7) {
				recognized = true;
				printf("%s %s %s is a %s Minor chord.\n", notes[0].s_, notes[1].s_, notes[2].s_, get_key(notes[perms[i][0]]));
				break;
			}
		}
		if (!recognized)
			printf("%s %s %s is unrecognized.\n", notes[0].s_, notes[1].s_, notes[2].s_);
	}
	return 0;
}

