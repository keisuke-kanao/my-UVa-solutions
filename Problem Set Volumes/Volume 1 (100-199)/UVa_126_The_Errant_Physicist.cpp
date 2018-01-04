
/*
	UVa 126 - The Errant Physicist

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_126_The_Errant_Physicist.cpp
*/

#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_chars_max = 80, nr_terms_max = 80;

struct term {
	int x_exp_; // x exponent
	int y_exp_; // y exponent

	bool operator<(const term& t) const
	{
		if (x_exp_ > t.x_exp_) // descending order of x exponent
			return true;
		else if (x_exp_ < t.x_exp_)
			return false;
		else
			return y_exp_ < t.y_exp_; // ascending order of y exponent
	}
};

bool add_term(map<term, int>& terms, const term& t, int coef)
{
	pair<map<term, int>::iterator, bool> result = terms.insert(make_pair(t, coef));
	if (!result.second)
		result.first->second += coef;
	return result.second;
}

int parse_terms(const char* s, map<term, int>& terms)
{
	const char* p = s;
	term t;
	t.x_exp_ = t.y_exp_ = 0;
	int coef = 1;
	while (*p) {
		if (*p == '-' || *p == '+') {
			if (p > s)
				add_term(terms, t, coef);
			t.x_exp_ = t.y_exp_ = 0;
			coef = (*p == '-') ? -1 : 1;
			p++;
		}
		else if (isdigit(*p)) {
			char* q;
			int d = strtol(p, &q, 10);
			if (p > s) {
				if (*(p - 1) == 'x')
					t.x_exp_ = d;
				else if (*(p - 1) == 'y')
					t.y_exp_ = d;
				else
					coef *= d;
			}
			else
				coef = d;
			p = q;
		}
		else {
			if (*p == 'x' && !t.x_exp_)
				t.x_exp_ = 1;
			else if (*p == 'y' && !t.y_exp_)
				t.y_exp_ = 1;
			p++;
		}
	}
	if (p  > s)
		add_term(terms, t, coef);
	return static_cast<int>(terms.size());
}

#ifdef DEBUG
void print_terms(const map<term, int>& terms)
{
	bool printed = false;
	for (map<term, int>::const_iterator i = terms.begin(), e = terms.end(); i != e; ++i) {
		if (printed)
			putchar(' ');
		else
			printed = true;
		printf("%dx%dy%d", i->second, i->first.x_exp_, i->first.y_exp_);
	}
	putchar('\n');
}
#endif

int print_number(int n, char* p)
{
	char* q = p;
	do {
		*q++ = (n % 10) + '0';
		n /= 10;
	} while (n);
	int length = q - p;
	for (q--; p < q; p++, q--)
		swap(*p, *q);
	return length;
}

int main()
{
	while (true) {
		char s[nr_chars_max + 1];
		gets(s);
		if (s[0] == '#')
			break;
		map<term, int> one_terms, other_terms;
		int nr_one_terms = parse_terms(s, one_terms);
		gets(s);
		int nr_other_terms = parse_terms(s, other_terms);
#ifdef DEBUG
		print_terms(one_terms);
		print_terms(other_terms);
#endif
		map<term, int> result_terms;
		for (map<term, int>::const_iterator i = one_terms.begin(), ie = one_terms.end(); i != ie; ++i)
			for (map<term, int>::const_iterator j = other_terms.begin(), je = other_terms.end(); j != je; ++j) {
				term t;
				t.x_exp_ = i->first.x_exp_ + j->first.x_exp_; t.y_exp_ = i->first.y_exp_ + j->first.y_exp_;
				int coef = i->second * j->second;
				add_term(result_terms, t, coef);
			}
#ifdef DEBUG
		print_terms(result_terms);
#endif
		char es[nr_chars_max + 1], ts[nr_chars_max + 1];
		memset(es, ' ', nr_chars_max);
		memset(ts, ' ', nr_chars_max);
		int si = 0;
		for (map<term, int>::const_iterator i = result_terms.begin(), ie = result_terms.end(); i != ie; ++i) {
			int coef = i->second;
			if (!coef)
				continue;
			const term& t = i->first;
			// print the coefficient
			if (si) {
				ts[si++] = ' '; ts[si++] = (coef < 0) ? '-' : '+'; ts[si++] = ' ';
			}
			else if (coef < 0)
				ts[si++] = '-';
			coef = abs(coef);
			if (coef > 1 || !t.x_exp_ && !t.y_exp_)
				si += print_number(abs(coef), &ts[si]);
			if (t.x_exp_ || t.y_exp_) {
				if (t.x_exp_) {
					ts[si++] = 'x';
					if (t.x_exp_ > 1)
						si += print_number(t.x_exp_, &es[si]);
				}
				if (t.y_exp_) {
					ts[si++] = 'y';
					if (t.y_exp_ > 1)
						si += print_number(t.y_exp_, &es[si]);
				}
			}
		}
		es[si] = ts[si] = '\0';
		puts(es);
		puts(ts);
	}
	return 0;
}

