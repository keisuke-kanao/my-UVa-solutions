
/*
	UVa 628 - Passwords

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_628_Passwords.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int nr_words_max = 100, nr_word_chars_max = 256;
const int nr_rule_chars_max = 256;
char words[nr_words_max][nr_word_chars_max];
char password[nr_word_chars_max * nr_rule_chars_max];

void print_password(int ri, int rlength, const char* rule, int wi, int wlength, int pi)
{
	if (ri == rlength)
		printf("%s\n", password);
	else if (rule[ri] == '#') {
		strcpy(password + pi, words[wi]);
		print_password(ri + 1, rlength, rule, wi, wlength, pi + wlength);
	}
	else {
		for (int i = 0; i < 10; i++) {
			password[pi] = i + '0';
			password[pi + 1] = '\0';
			print_password(ri + 1, rlength, rule, wi, wlength, pi + 1);
		}
	}
}

int main()
{
	while (true) {
		int nr_words;
		if (scanf("%d\n", &nr_words) == EOF)
			break;
		for (int i = 0; i < nr_words; i++)
			gets(words[i]);
		int nr_rules;
		scanf("%d\n", &nr_rules);
		printf("--\n");
		for (int ri = 0; ri < nr_rules; ri++) {
			char rule[nr_rule_chars_max];
			gets(rule);
			int rlength = strlen(rule);
			for (int wi = 0; wi < nr_words; wi++) {
				int wlength = strlen(words[wi]);
				print_password(0, rlength, rule, wi, wlength, 0);
			}
		}
	}
	return 0;
}

