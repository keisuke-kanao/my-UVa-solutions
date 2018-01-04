
/*
	UVa 499 - What's The Frequency, Kenneth?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_499_Whats_The_Frequency_Kenneth.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

int main()
{
	const int nr_letters = 26;
	int upper_letters[nr_letters], lower_letters[nr_letters];
	string s;
	while (getline(cin, s)) {
		memset(upper_letters, 0, sizeof(upper_letters));
		memset(lower_letters, 0, sizeof(lower_letters));
		for (const char* p = s.c_str(); *p; p++) {
			if (isupper(*p))
				upper_letters[*p - 'A']++;
			else if (islower(*p))
				lower_letters[*p - 'a']++;
		}
		int max_nr_occurrences = 0;
		for (int i = 0; i < nr_letters; i++)
			max_nr_occurrences = max(max_nr_occurrences, upper_letters[i]);
		for (int i = 0; i < nr_letters; i++)
			max_nr_occurrences = max(max_nr_occurrences, lower_letters[i]);
		for (int i = 0; i < nr_letters; i++)
			if (upper_letters[i] == max_nr_occurrences)
				cout << static_cast<char>('A' + i);
		for (int i = 0; i < nr_letters; i++)
			if (lower_letters[i] == max_nr_occurrences)
				cout << static_cast<char>('a' + i);
		cout << ' ' << max_nr_occurrences << endl;
	}
	return 0;
}

