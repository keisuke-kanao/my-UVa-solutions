
/*
	UVa 10062 - Tell me the frequencies!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10062_Tell_me_the_frequencies.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

struct ascii_character {
	int value_;
	int frequencies_;
};

bool compare_frequencies(const ascii_character& i, const ascii_character& j)
{
	if (i.frequencies_ < j.frequencies_)
		return true;
	else if (i.frequencies_ > j.frequencies_)
		return false;
	else
		return i.value_ > j.value_;
}

int main()
{
	const int nr_chars_max = 1000;
	char line[nr_chars_max + 1];
	bool printed = false;
	while (gets(line)) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		int length = strlen(line);
		const int nr_ascii_characters = 96; // 128 - 32
		ascii_character	ascii_chars[nr_ascii_characters];
		for (int i = 0; i < nr_ascii_characters; i++) {
			ascii_chars[i].value_ = 32 + i;
			ascii_chars[i].frequencies_ = 0;
		}
		for (int i = 0; i < length; i++)
			if (line[i] >= 32 && line[i] < 128)
				ascii_chars[line[i] - 32].frequencies_++;
		sort(ascii_chars, ascii_chars + nr_ascii_characters, compare_frequencies);
		for (int i = 0; i < nr_ascii_characters; i++)
			if (ascii_chars[i].frequencies_)
				printf("%d %d\n", ascii_chars[i].value_, ascii_chars[i].frequencies_);
	}
	return 0;
}

