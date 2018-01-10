
/*
	UVa 185 - Roman Numerals

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_185_Roman_Numerals.cpp

	from ACM South Pacific Regionals - 1993 Problem G
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1993/index.html)
*/

#include <cstdio>
#include <cstring>
#include <cmath>

const int nr_digits = 10, nr_letters = 26;
const int nr_numerals = 3, nr_chars_max = 9;
const int numeral_values[nr_letters] = {0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10, 0, 0};

char line[(nr_chars_max + 1) * nr_numerals];
const char* numerals[nr_numerals]; // numerals[i] is the pointer to the i-th numeral string
int numeral_lengths[nr_numerals]; // lengths[i] is the numeral string length in chars of i-th numeral

bool assigned_digits[nr_digits];
	// assigned_digits[i] is true if '0' + i-th digit has been assigned
int assigned_values[nr_letters];
	// assigned_values[i] is the assined value (0 - 9) for 'A' + i-th letters
int roman_values[nr_numerals], arabic_values[nr_numerals];

int parse_roman_numeral(const char* s, int length)
{
	int r = 0, p = -1;
	do {
		int c = numeral_values[*s++ - 'A'];
		if (p != -1 && p < c)
			r -= p * 2;
		r += c;
		p = c;
	} while (--length);
	return r;
}

int get_arabig_value(const char* p, int length)
{
	int n = 0;
	for (int i = 0; i < length; i++, p++) {
		if (i)
			n *= 10;
		n += assigned_values[*p - 'A'];
	}
	return n;
}

int encode_arabic_sum(const char* p, int* nr_encodings)
{
	char c = *p;
	if (c == '+') {
		arabic_values[0] = get_arabig_value(numerals[0], numeral_lengths[0]);
		if (encode_arabic_sum(p + 1, nr_encodings)> 1)
			return *nr_encodings;
	}
	else if (c == '=') {
		arabic_values[1] = get_arabig_value(numerals[1], numeral_lengths[1]);
		// see whether we should parse the third numeral (pruning)
		int s = arabic_values[0] + arabic_values[1];
		if (static_cast<int>(log10(static_cast<double>(s))) + 1 != numeral_lengths[2])
			return *nr_encodings;
		if (encode_arabic_sum(p + 1, nr_encodings) > 1)
			return *nr_encodings;
	}
	else if (c == '\0') {
		arabic_values[2] = get_arabig_value(numerals[2], numeral_lengths[2]);
		if (arabic_values[0] + arabic_values[1] == arabic_values[2]) {
			(*nr_encodings)++;
#ifdef DEBUG
			printf("%d+%d=%d\n", arabic_values[0], arabic_values[1], arabic_values[2]);
#endif
		}
		return *nr_encodings;
	}
	else {
		int ci = c - 'A';
		if (assigned_values[ci] == -1) {
			int i = 0;
			if (p == numerals[0] || p == numerals[1] || p == numerals[2]) // first character of a numeral
				i++;
			for ( ; i < nr_digits; i++)
				if (!assigned_digits[i]) {
					assigned_digits[i] = true;
					assigned_values[ci] = i;
					encode_arabic_sum(p + 1, nr_encodings);
					assigned_digits[i] = false;
					if (*nr_encodings > 1)
						break;
				}
			assigned_values[ci] = -1;
			if (*nr_encodings > 1)
				return *nr_encodings;
		}
		else {
			if (!assigned_values[ci] && (p == numerals[0] || p == numerals[1] || p == numerals[2]))
				return *nr_encodings; // zero should not be assigned to the first character of a numeral
			else {
				if (encode_arabic_sum(p + 1, nr_encodings) > 1)
					return *nr_encodings;
			}
		}
	}
	return *nr_encodings;
}

int main()
{
	while (true) {
		gets(line);
		if (line[0] == '#')
			break;
		char* p = line;
		numerals[0] = p;
		p = strchr(p, '+');
		numeral_lengths[0] = p - numerals[0];
		numerals[1] = ++p;
		p = strchr(p, '=');
		numeral_lengths[1] = p - numerals[1];
		numerals[2] = ++p;
		numeral_lengths[2] = strlen(p);
		for (int i = 0; i < nr_numerals; i++)
			roman_values[i] = parse_roman_numeral(numerals[i], numeral_lengths[i]);
		bool correct = roman_values[0] + roman_values[1] == roman_values[2];
		memset(assigned_digits, 0, sizeof(assigned_digits));
		memset(assigned_values, -1, sizeof(assigned_values));
		int nr_encodings = 0;
		encode_arabic_sum(line, &nr_encodings);
		printf((correct) ? "Correct " : "Incorrect ");
		if (nr_encodings > 1)
			printf("ambiguous\n");
		else if (!nr_encodings)
			printf("impossible\n");
		else
			printf("valid\n");
	}
	return 0;
}

