
/*
	UVa 10115 - Automatic Editing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10115_Automatic_Editing.cpp

	from ACM Mid Central Regionals 1999 Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1999/index.html)
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rules_max = 10;
const int nr_rule_chrs_max = 80, nr_text_chrs_max = 255;

struct find_replace_rule {
	char find_[nr_rule_chrs_max + 1];
	char replace_[nr_rule_chrs_max + 1];
} rules[nr_rules_max];

void apply_rule(const find_replace_rule* rule, char* text)
{
	const char *f = rule->find_, *r = rule->replace_;
	int fl = strlen(rule->find_), rl = strlen(rule->replace_);
	for ( ; *text; )
		if (!strncmp(text, f, fl)) {
			memmove(text + rl, text + fl, strlen(text + fl) + 1);
			memcpy(text, r, rl);
		}
		else
			text++;
}

int main()
{
	while (true) {
		char text[nr_text_chrs_max + 1];
		gets(text);
		int nr_rules;
		sscanf(text, "%d", &nr_rules);
		if (!nr_rules)
			break;
		for (int i = 0; i < nr_rules; i++) {
			gets(rules[i].find_);
			gets(rules[i].replace_);
		}
		gets(text);
		for (int i = 0; i < nr_rules; i++)
			apply_rule(rules + i, text);
		printf("%s\n", text);
	}
	return 0;
}

