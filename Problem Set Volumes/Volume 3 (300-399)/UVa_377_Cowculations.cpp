
/*
	UVa 377 - Cowculations

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_377_Cowculations.cpp

	from ACM  Mid-Atlantic Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidAtl/1996/index.html)
*/

#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_symbols = 4;
const int nr_chars = 5, nr_result_chars = 8;

const pair<char, char> addition_table[nr_symbols][nr_symbols] = {
	{make_pair('V', '\0'), make_pair('U', '\0'), make_pair('C', '\0'), make_pair('D', '\0')},
	{make_pair('U', '\0'), make_pair('C', '\0'), make_pair('D', '\0'), make_pair('V', 'U')},
	{make_pair('C', '\0'), make_pair('D', '\0'), make_pair('V', 'U'), make_pair('U', 'U')},
	{make_pair('D', '\0'), make_pair('V', 'U'), make_pair('U', 'U'), make_pair('C', 'U')}
};

int symbol_to_index(char s)
{
	switch (s) {
	case 'V':
		return 0;
	case 'U':
		return 1;
	case 'C':
		return 2;
	default:
		return 3;
	}
}

pair<char, char> add_symbols(char i, char j)
{
	return addition_table[symbol_to_index(i)][symbol_to_index(j)];
}

void add_numbers(char number_1[], char number_2[])
{
	int i, j;
	char carry = '\0';
	pair<char, char> result;
	for (i = strlen(number_1) - 1, j = strlen(number_2) - 1; i >= 0 && j >= 0; i--, j--) {
		result = add_symbols(number_1[i], number_2[j]);
		char s = result.first, c = result.second;
		if (carry) {
			result = add_symbols(s, carry);
			s = result.first;
			if (result.second) {
				if (c) {
					result = add_symbols(c, result.second);
					c = result.first;
				}
				else
					c = result.second;
			}
		}
		number_2[j] = s;
		carry = c;
	}
	for (; j >= 0; j--) {
		if (carry) {
			result = add_symbols(number_2[j], carry);
			number_2[j] = result.first;
			carry = result.second;
		}
	}
	if (carry) {
		int length = strlen(number_2);
		memmove(number_2 + 1, number_2, length);
		number_2[length + 1] = '\0';
		number_2[0] = carry;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("COWCULATIONS OUTPUT\n");
	while (n--) {
		char number_1[nr_chars + 1], number_2[nr_result_chars + 1], result[nr_result_chars + 1];
		scanf("%s", number_1);
		scanf("%s", number_2);
		int length;
		for (int i = 0; i < 3; i++) {
			char operation[nr_chars];
			scanf("%s", operation);
			switch (operation[0]) {
			case 'A':
				add_numbers(number_1, number_2);
				break;
			case 'R':
				length = strlen(number_2);
				memmove(number_2 + 1, number_2, length - 1);
				number_2[0] = 'V';
				break;
			case 'L':
				length = strlen(number_2);
				number_2[length] = 'V'; number_2[length + 1] = '\0';
			default:
				break;
			}
		}
		if ((length = strlen(number_2)) < nr_result_chars) {
			int plength = nr_result_chars - length;
			memmove(number_2 + plength, number_2, length);
			memset(number_2, 'V', plength);
			number_2[nr_result_chars] = '\0';
		}
		scanf("%s", result);
		printf("%s", (strcmp(number_2, result)) ? "NO\n" : "YES\n");
	}
	printf("END OF OUTPUT\n");
	return 0;
}

