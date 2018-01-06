
/*
	UVa 10058 - Jimmi's Riddles

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10058_Jimmis_Riddles.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

/*
STATEMENT = ACTION | STATEMENT , ACTION
ACTION = ACTIVE_LIST VERB ACTIVE_LIST
ACTIVE_LIST = ACTOR | ACTIVE_LIST and ACTOR
ACTOR = NOUN | ARTICLE NOUN
ARTICLE = a | the
NOUN = tom | jerry | goofy | mickey | jimmy | dog | cat | mouse
VERB = hate | love | know | like | VERBs
*/

const char *ps, *pws, *pwe;

bool get_word(const char** s, const char** e)
{
	while (isspace(*ps))
		ps++;
	*s = ps;
	while (*ps && !isspace(*ps))
		ps++;
	*e = ps;
	return *s < *e;
}

enum {COMMA, AND, ARTICLE, NOUN, VERB};

struct word {
	int length_;
	const char* s_;
};

word articles[] = {
	{1, "a"}, {3, "the"}
};
const size_t nr_articles = sizeof(articles) / sizeof(word);

word nouns[] = {
	{3, "tom"}, {5, "jerry"}, {5, "goofy"}, {6, "mickey"},
	{5, "jimmy"}, {3, "dog"}, {3, "cat"}, {5, "mouse"}
};
const size_t nr_nouns = sizeof(nouns) / sizeof(word);

word verbs[] = {
	{4, "hate"}, {4, "love"}, {4, "know"}, {4, "like"}
};
const size_t nr_verbs = sizeof(verbs) / sizeof(word);

bool accept(int wn)
{
	if (pws == pwe) {
		if (!get_word(&pws, &pwe))
			return false;
	}
	size_t nr_chars = pwe - pws, i;
	bool result = false;
	switch (wn) {
	case COMMA:
		result = nr_chars == 1 && *pws == ',';
		break;
	case AND:
		result = nr_chars == 3 && !strncmp(pws, "and", 3);
		break;
	case ARTICLE:
		for (i = 0; i < nr_articles; i++)
			if (nr_chars == articles[i].length_ && !strncmp(pws, articles[i].s_, articles[i].length_))
				break;
		result = i < nr_articles;
		break;
	case NOUN:
		for (i = 0; i < nr_nouns; i++)
			if (nr_chars == nouns[i].length_ && !strncmp(pws, nouns[i].s_, nouns[i].length_))
				break;
		result = i < nr_nouns;
		break;
	case VERB:
		for (i = 0; i < nr_verbs; i++)
			if (!strncmp(pws, verbs[i].s_, verbs[i].length_)) {
				if (nr_chars == verbs[i].length_)
					break;
				const char* p = pws + verbs[i].length_;
				for ( ; p < pwe; p++)
					if (*p != 's')
						break;
				if (p == pwe)
					break;
			}
		result = i < nr_verbs;
		break;
	}
	if (result)
		pws = pwe;
	return result;
}

void statement(), action(), active_list(), actor();

void statement()
{
	action();
	while (accept(COMMA))
		action();
}

void action()
{
	active_list();
	if (accept(VERB))
		active_list();
	else
		throw -1;
}

void active_list()
{
	actor();
	while (accept(AND))
		actor();
}

void actor()
{
	if (accept(ARTICLE))
		;
	if (accept(NOUN))
		;
	else
		throw -1;
}

int main()
{
	string riddle;
	while (getline(cin, riddle)) {
		ps = pws = pwe = riddle.c_str();
		bool yes = false;
		try {
			statement();
			while (isspace(*pws))
				pws++;
			if (!*pws)
				yes = true;
			else
				throw -1;
		}
		catch (int) {
		}
		cout << ((yes) ? "YES I WILL\n" : "NO I WON'T\n");
	}
	return 0;
}

