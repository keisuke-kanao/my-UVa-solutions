
/*
	UVa 214 - Code Generation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_214_Code_Generation.cpp

	form 1991 ACM Scholastic Programming Contest Finals, Problem G
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/A_FINALS/1991/prob_g.html)

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

int stack[65536], top;
bool use[256];
char fmt[256][16];

int store()
{
	int i;
	for (i = '0'; i <= '9'; i++)
		if (!use[i])
			break;
	use[i] = true;
	cout << "ST $" << static_cast<char>(i) << endl;
	return i;
}

void take(int k)
{
	int i;
	top -= k;
	for (i = 0; i < top; i++)
		if (!stack[i]) {
			stack[i] = store();
			break;
		}
	for (i = 0; i < top; i++)
		if (isalpha(stack[i]))
			break;
	if (i >= top)
		return;
	for (i = 0; i < k; i++)
		if (!stack[top + i]) {
			stack[top + i] = store();
			break;
		}
	for (i = 0; i < top; i++)
		if (isalpha(stack[i])) {
			cout << "L " << fmt[stack[i]] << endl;
			stack[i] = store();
		}
}

void commut(char op)
{
	take(2);
	int x = stack[top], y = stack[top + 1];
	if (!x)
		cout << op << ' ' << fmt[y] << endl;
	else if (!y)
		cout << op << ' ' << fmt[x] << endl;
	else
		cout << "L " << fmt[x] << endl << op << ' ' << fmt[y] << endl;
	use[x] = use[y] = false;
	stack[top++] = 0;
}

void sub()
{
	take(2);
	int x = stack[top], y = stack[top + 1];
	if (!x)
		cout << "S " << fmt[y] << endl;
	else if (!y)
		cout << "N\nA " << fmt[x] << endl;
	else
		cout << "L " << fmt[x] << "\nS " << fmt[y] << endl;
	use[x] = use[y] = false;
	stack[top++] = 0;
}

void div()
{
	take(2);
	int x = stack[top], y = stack[top + 1];
	if (!x)
		cout << "D " << fmt[y] << endl;
	else if (!y) {
		/* reg <- x / reg */
		y = store();
		cout << "L " << fmt[x] << "\nD " << fmt[y] << endl;
	}
	else
		cout << "L " << fmt[x] << "\nD " << fmt[y] << endl;
	use[x] = use[y] = false;
	stack[top++] = 0;
}

void neg()
{
	take(1);
	if (!stack[top])
		cout << "N\n";
	else
		cout << "L " << fmt[stack[top]] << "\nN\n";
	use[stack[top]] = false;
	stack[top++] = 0;
}

int main()
{
	for (int i = 0; i < 256; i++)
		sprintf(fmt[i], "%c", i);
	for (int i = '0'; i <= '9'; i++)
		sprintf(fmt[i], "$%c", i);
	bool printed = false;
	string s;
	while (cin >> s) {
		if (printed)
			cout << endl;
		else
			printed = true;
		top = 0;
		memset(use, 0, sizeof(use));
		for (const char* p = s.c_str(); *p; p++) {
			switch (*p) {
			case '+':
				commut('A'); break;
			case '*':
				commut('M'); break;
			case '-':
				sub(); break;
			case '/':
				div(); break;
			case '@':
				neg(); break;
			default:
				stack[top++] = *p; break;
			}
		}
		if (top > 0 && stack[top - 1])
			cout << "L " << static_cast<char>(stack[top - 1]) << endl;
	}
	return 0;
}
/*
Sample input

AB+CD+EF++GH+++
AB+CD+-

Sample output

L A
A B
ST $1
L C
A D
ST $2
L E
A F
A $2
ST $2
L G
A H
A $2
A $1

L A
A B
ST $1
L C
A D
N
A $1

*/

