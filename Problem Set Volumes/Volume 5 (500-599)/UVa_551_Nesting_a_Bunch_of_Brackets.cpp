
/*
	UVa 551 - Nesting a Bunch of Brackets

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_551_Nesting_a_Bunch_of_Brackets.cpp
*/

#include <stack>
#include <cstdio>
using namespace std;

bool is_properly_nested(char c, stack<char>& st)
{
	if (st.empty())
		return false;
	switch (st.top()) {
	case '(':
		if (c != ')')
			return false;
		break;
	case '[':
		if (c != ']')
			return false;
		break;
	case '{':
		if (c != '}')
			return false;
		break;
	case '<':
		if (c != '>')
			return false;
		break;
	case '*':
		if (c != '*')
			return false;
		break;
	}
#ifdef DEBUG
	printf("%c popped\n", cs);
#endif
	st.pop();
	return true;
}

int main()
{
	const int nr_chars_max = 3000;
	char expression[nr_chars_max + 1];
	while (gets(expression)) {
		stack<char> st;
		int i = 0, ei = -1;
		for (const char* p = expression; ei == -1 && *p; p++, i++) {
			switch (*p) {
			case '(':
				if (*(p + 1) == '*')
					p++;
				// go through
			case '[': case '{': case '<':
#ifdef DEBUG
				printf("%c pushed\n", *p);
#endif
				st.push(*p);
				break;
			case '*':
				if (*(p + 1) == ')') {
					if (is_properly_nested(*p, st))
						p++;
					else
						ei = i;
				}
				break;
			case ')': case ']': case '}': case '>':
				if (!is_properly_nested(*p, st))
					ei = i;
				break;
			}
		}
		if (ei == -1 && !st.empty())
			ei = i;
		if (ei == -1)
			puts("YES");
		else
			printf("NO %d\n", ei + 1);
	}
	return 0;
}

