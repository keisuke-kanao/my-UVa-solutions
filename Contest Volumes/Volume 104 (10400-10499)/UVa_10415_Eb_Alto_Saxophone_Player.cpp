
/*
	UVa 10415 - Eb Alto Saxophone Player

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10415_Eb_Alto_Saxophone_Player.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_fingers = 10, nr_notes_max = 200;

int notes[] = {0x006, 0x002, 0x3ce, 0x1ce, 0x0ce, 0x04e, 0x00e};
	// notes[i] is the finger pattern for i - 'a'
int high_notes[] = {0x007, 0x003, 0x004, 0x1cf, 0x0cf, 0x004f, 0x00f};
	// high_notes[i] is the finger pattern for i - 'A'

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		int nr_presses[nr_fingers];
		memset(nr_presses, 0, sizeof(nr_presses));
		char s[nr_notes_max + 1];
		gets(s);
		int finger_pattern = 0;
		for (const char* p = s; *p; p++)
			if (isalpha(*p)) {
				int note = (isupper(*p)) ? high_notes[*p - 'A'] : notes[*p - 'a'];
				int d = finger_pattern ^ note;
				int f = d & note;
				for (int i = 0, b = 1; i < nr_fingers; i++, b <<= 1)
					if (f & b)
						nr_presses[i]++;
				finger_pattern = note;
			}
		for (int i = 0; i < nr_fingers; i++)
			printf("%d%c", nr_presses[i], ((i == nr_fingers - 1) ? '\n' : ' '));
	}
	return 0;
}

