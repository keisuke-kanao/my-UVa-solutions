
/*
	UVa 622 - Grammar Evaluation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_622_Grammar_Evaluation.cpp
*/

/*
< expression > := < component > | < component > + < expression >
< component > := < factor > | < factor > * < component >
< factor > := < positiveinteger > | (< expression >)
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_chars_max = 255;

char s[nr_chars_max + 1], *ps;

int positive_integer()
{
	if (isdigit(*ps)) {
		int n = 0;
		do
			n = n * 10 + *ps++ - '0';
		while (isdigit(*ps));
		return n;
	}
	else
		return -1;
}

int expression();
int component();
int factor();

int factor()
{
	int n = positive_integer();
	if (n != -1)
		return n;
	else if (*ps == '(') {
		ps++;
		n = expression();
		if (*ps == ')')
			ps++;
		else
			throw -1;
		return n;
	}
	else {
		throw -1;
		return -1;
	}
}

int component()
{
	int n = factor();
	if (*ps == '*') {
		ps++;
		n *= component();
	}
	return n;
}

int expression()
{
	int n = component();
	if (*ps == '+') {
		ps++;
		n += expression();
	}
	return n;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", ps = s);
		try {
			int n = expression();
			if (*ps)
				throw -1;
			printf("%d\n", n);
		}
		catch (int e) {
			puts("ERROR");
		}
	}
	return 0;
}

