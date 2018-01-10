
/*
	UVa 657 - The die is cast

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_657_The_die_is_cast.cpp

	from ACM Western and Southwestern European Regionals 1998 Problem B
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1998/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void replace_die(int i, int j, int h, int w, int& nr_dots, vector< vector<char> >& pixels);
void replace_dots(int i, int j, int h, int w, int in_dots, int& nr_dots, vector< vector<char> >& pixels);

void replace_die(int i, int j, int h, int w, int& nr_dots, vector< vector<char> >& pixels)
{
	pixels[i][j] = '.';
	if (i) { // upper
		if (pixels[i - 1][j] == 'X')
			replace_dots(i - 1, j, h, w, 0, nr_dots, pixels);
		if (pixels[i - 1][j] == '*')
			replace_die(i - 1, j, h, w, nr_dots, pixels);
	}
	if (j) { // left
		if (pixels[i][j - 1] == 'X')
			replace_dots(i, j - 1, h, w, 0, nr_dots, pixels);
		if (pixels[i][j - 1] == '*')
			replace_die(i, j - 1, h, w, nr_dots, pixels);
	}
	if (j < w - 1) { // right
		if (pixels[i][j + 1] == 'X')
			replace_dots(i, j + 1, h, w, 0, nr_dots, pixels);
		if (pixels[i][j + 1] == '*')
			replace_die(i, j + 1, h, w, nr_dots, pixels);
	}
	if (i < h - 1) { // lower
		if (pixels[i + 1][j] == 'X')
			replace_dots(i + 1, j, h, w, 0, nr_dots, pixels);
		if (pixels[i + 1][j] == '*')
			replace_die(i + 1, j, h, w, nr_dots, pixels);
	}
}

void replace_dots(int i, int j, int h, int w, int in_dots, int& nr_dots, vector< vector<char> >& pixels)
{
	pixels[i][j] = '*';
	if (i && pixels[i - 1][j] == 'X') // upper
		replace_dots(i - 1, j, h, w, in_dots + 1, nr_dots, pixels);
	if (j && pixels[i][j - 1] == 'X') // left
		replace_dots(i, j - 1, h, w, in_dots + 1, nr_dots, pixels);
	if (j < w - 1 && pixels[i][j + 1] == 'X') // right
		replace_dots(i, j + 1, h, w, in_dots + 1, nr_dots, pixels);
	if (i < h - 1 && pixels[i + 1][j] == 'X') // lower
		replace_dots(i + 1, j, h, w, in_dots + 1, nr_dots, pixels);
	if (!in_dots) {
		nr_dots++;
#ifdef DEBUG
		cout << '(' << i << ", " << j << ") " << nr_dots << endl;
#endif
	}
}

int main()
{
	for (int nr = 1; ; nr++) {
		int w, h;
		cin >> w >> h;
		if (!w && !h)
			break;
		vector< vector<char> > pixels(h, vector<char>(w));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				cin >> pixels[i][j];
		vector<int> dots;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				bool die_or_dots = false;
				int nr_dots = 0;
				if (pixels[i][j] == 'X') {
					die_or_dots = true;
					replace_dots(i, j, h, w, 0, nr_dots, pixels);
				}
				if (pixels[i][j] == '*') {
					die_or_dots = true;
					replace_die(i, j, h, w, nr_dots, pixels);
				}
				if (die_or_dots)
					dots.push_back(nr_dots);
			}
		sort(dots.begin(), dots.end());
		cout << "Throw " << nr << endl;
		bool printed = false;
		for (vector<int>::const_iterator i = dots.begin(), e = dots.end(); i != e; ++i) {
			if (printed)
				cout << ' ';
			printed = true;
			cout << *i;
		}
		cout << endl << endl;
	}
	return 0;
}

