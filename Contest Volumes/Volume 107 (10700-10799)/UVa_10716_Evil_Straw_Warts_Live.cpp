
/*
	UVa 10716 - Evil Straw Warts Live

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10716_Evil_Straw_Warts_Live.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int nr_letters = 26, nr_chars_max = 100;

bool can_be_palindrome(const char* s, int length)
{
	int occurrences[nr_letters];
	memset(occurrences, 0, sizeof(occurrences));
	for ( ; length; length--, s++)
		occurrences[*s - 'a']++;
	bool odd_occurrence = false;
	for (int i = 0; i < nr_letters; i++)
		if (occurrences[i] & 1) {
			if (odd_occurrence)
				return false;
			else
				odd_occurrence = true;
		}
	return true;
}

void select_swap_letter_positions(const char* s, int length, int* pli, int* pri)
{
	// for each letter, find it's first and last occurence in current string
	int leftmost_occurrences[nr_letters], rightmost_occurrences[nr_letters];
	memset(leftmost_occurrences, -1, sizeof(leftmost_occurrences));
	memset(rightmost_occurrences, -1, sizeof(rightmost_occurrences));
	for (int i = 0; i < length; i++, s++) {
		int j = *s - 'a';
		if (leftmost_occurrences[j] == -1)
			leftmost_occurrences[j] = i;
		rightmost_occurrences[j] = i;
	}
	// select letter for which sum of distances from it's first occurence to beginning and from last one to the end is smallest
	int min_i, min_s = length * 2;
	for (int i = 0; i < nr_letters; i++)
		if (leftmost_occurrences[i] != -1) {
			int s = leftmost_occurrences[i] + length - 1 - rightmost_occurrences[i];
			if (s < min_s) {
				min_i = i;
				min_s = s;
			}
		}
	*pli = leftmost_occurrences[min_i]; *pri = rightmost_occurrences[min_i];
}

int transform_to_palindrome(char* s, int length)
{
	if (length < 2)
		return 0;
	int li, ri;
	select_swap_letter_positions(s, length, &li, &ri);
	// "move it" I mean swap it's first occurence to beginning and last to the end.
	if (li) {
		char c = s[li];
		memmove(&s[1], &s[0], li);
		s[0] = c;
	}
	if (ri < length - 1) {
		char c = s[ri];
		memmove(&s[ri], &s[ri + 1], length - ri - 1);
		s[length - 1] = c;
	}
	// and "eliminate" them --> now you have the word which is shorter.
	return li + (length - ri - 1) + transform_to_palindrome(s + 1, length - 2);
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int length = strlen(s);
		if (can_be_palindrome(s, length)) {
			int nr_swaps = transform_to_palindrome(s, length);
#ifdef DEBUG
			printf("%d %s\n", nr_swaps, s);
#else
			printf("%d\n", nr_swaps);
#endif
		}
		else
			printf("Impossible\n");
	}
	return 0;
}

