
/*
	UVa 12554 - A Special "Happy Birthday" Song!!!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12554_A_Special_Happy_Birthday_Song.cpp
*/

#include <cstdio>

const int nr_words = 16;

const char* words[nr_words] = {
	"Happy", "birthday", "to", "you", 
	"Happy", "birthday", "to", "you", 
	"Happy", "birthday", "to", "Rujia", 
	"Happy", "birthday", "to", "you" 
};

const int n_max = 128, nr_chars_max = 127;

char names[n_max][nr_chars_max + 1];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", names[i]);
	for (int i = 0, repeat = ((n + nr_words - 1) / nr_words) * nr_words; i < repeat; i++)
		printf("%s: %s\n", names[i % n], words[i % nr_words]);
	return 0;
}

