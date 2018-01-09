
/*
	UVa 10562 - Undraw the Trees

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10562_Undraw_the_Trees.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int nr_lines_max = 200, nr_chrs_max = 200;
string prof_tree[nr_lines_max + 1];

void print_tree(int nr_lines, int i, int j)
{
	if (i == nr_lines)
		cout << "()";
	else {
		const string& pt = prof_tree[i];
		if (j >= pt.length())
			cout << "()";
		else if (pt[j] == ' ')
			cout << "()";
		else if (pt[j] == '|')
			print_tree(nr_lines, i + 1, j);
		else if (pt[j] == '-') {
			while (j && pt[j - 1] == '-')
				j--;
			cout << '(';
			for ( ; pt[j] == '-'; j++) {
				if (j < prof_tree[i + 1].length() && prof_tree[i + 1][j] != ' ')
					print_tree(nr_lines, i + 1, j);
			}
			cout << ')';
		}
		else {
			cout << pt[j];
			print_tree(nr_lines, i + 1, j);
		}
	}
}

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int t;
	iss >> t;
	while (t--) {
		int nr_lines = 0;
		while (true) {
			getline(cin, prof_tree[nr_lines]);
			if (prof_tree[nr_lines][0] == '#')
				break;
			nr_lines++;
		}
		cout << '(';
		if (nr_lines) {
			const string& pt = prof_tree[0];
			for (int j = 0, e = pt.length(); j < e; j++)
				if (pt[j] != ' ') {
					cout << pt[j];
					print_tree(nr_lines, 1, j);
				}
		}
		cout << ")\n";
	}
	return 0;
}


