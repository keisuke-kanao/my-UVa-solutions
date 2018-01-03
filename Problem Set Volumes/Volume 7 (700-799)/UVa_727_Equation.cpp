
/*
	UVa 727 - Equation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_727_Equation.cpp
*/

#include <stack>
#include <cstdio>
using namespace std;

int get_operator_priority(char c)
{
	int p = 0;
	switch (c) {
	case '*': case '/':
		return 2;
	case '+': case '-':
		return 1;
	default:
		return 0;
	}
}

void infix2postfix(const char* i)
{
	char c, d;
	stack<char> st;
	for ( ; *i; i++) {
		c = *i;
		if (c >= '0' && c <= '9')
			putchar(c);
		else if (c == '(')
			st.push(c);
		else if (c == ')') {
			d = st.top();
			st.pop();
			while (d != '(') {
				putchar(d);
				d = st.top();
				st.pop();
			}
		}
		else { // operators
			if (st.empty())
				st.push(c);
			else {
				while (!st.empty() && get_operator_priority(st.top()) >= get_operator_priority(c)) {
					putchar(st.top());
					st.pop();
				}
				st.push(c);
			}
		}
	}
	while (!st.empty()) {
		putchar(st.top());
		st.pop();
	}
	putchar('\n');
}

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	getchar();
	while (t--) {
		const int nr_chars_max = 50;
		char c, s[nr_chars_max + 1];
		char* ps = s;
		while ((c = getchar()) != EOF && c != '\n') {
			*ps++ = c;
			getchar();
		}
		*ps = '\0';
		infix2postfix(s);
		if (t)
			putchar('\n');
	}
	return 0;
}

