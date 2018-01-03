
/*
	UVa 735 - Dart-a-Mania

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_735_Dart-a-Mania.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_throws = 3, nr_points = 43, point_max = 60;
const int points[nr_points] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 26, 27, 28, 30, 32, 33, 34, 36, 38, 39, 40, 42, 45, 48, 50, 51, 54, 57, 60
};
int current_obtained[nr_throws], sorted_current_obtained[nr_throws];
bool obtained[point_max + 1][point_max + 1][point_max + 1]; // obtained[i][j][k] is true if combination of i, j, and k has already been counted

void sort_obtained_points()
{
	memcpy(sorted_current_obtained, current_obtained, sizeof(current_obtained));
	if (sorted_current_obtained[0] > sorted_current_obtained[1])
		swap(sorted_current_obtained[0], sorted_current_obtained[1]);
	if (sorted_current_obtained[1] > sorted_current_obtained[2])
		swap(sorted_current_obtained[1], sorted_current_obtained[2]);
	if (sorted_current_obtained[0] > sorted_current_obtained[1])
		swap(sorted_current_obtained[0], sorted_current_obtained[1]);
/*
if (a > c)
   swap(a, c)

if (a > b)
   swap(a, b)

//Now the smallest element is the first one. Just check the 2-nd and 3-rd

if (b > c)
   swap(b, c);


if (a > b)
   swap(a,b)
if (b > c)
   swap(b,c)
if (a > b)
   swap(a,b)
print a,b,c
*/
}

void throw_darts(int nr, int score, int current, int& nr_combinations, int& nr_permutations)
{
	if (nr < nr_throws) {
		for (int i = 0; i < nr_points && current + points[i] <= score; i++) {
			current_obtained[nr] = points[i];
			throw_darts(nr + 1, score, current + points[i], nr_combinations, nr_permutations);
		}
	}
	else {
		if (current == score) {
			sort_obtained_points();
			if (!obtained[sorted_current_obtained[0]][sorted_current_obtained[1]][sorted_current_obtained[2]]) {
				nr_combinations++;
				obtained[sorted_current_obtained[0]][sorted_current_obtained[1]][sorted_current_obtained[2]] = true;
			}
			nr_permutations++;
		}
	}
}

int main()
{
	while (true) {
		int score;
		cin >> score;
		if (score <= 0)
			break;
		memset(obtained, 0, sizeof(obtained));
		int nr_combinations = 0, nr_permutations = 0;
		throw_darts(0, score, 0, nr_combinations, nr_permutations);
		if (nr_combinations) {
			cout << "NUMBER OF COMBINATIONS THAT SCORES " << score << " IS " << nr_combinations << ".\n";
			cout << "NUMBER OF PERMUTATIONS THAT SCORES " << score << " IS " << nr_permutations << ".\n";
		}
		else
			cout << "THE SCORE OF " << score << " CANNOT BE MADE WITH THREE DARTS.\n";
		cout << "**********************************************************************\n";
	}
	cout << "END OF OUTPUT\n";
	return 0;
}

/*
#include <iostream>
#include <set>
using namespace std;

int main()
{
	set<int> points;
	points.insert(0);
	for (int i = 1; i <= 20; i++) {
		points.insert(i);
		points.insert(i * 2);
		points.insert(i * 3);
	}
	points.insert(50);
	cout << points.size() << endl;
	for (set<int>::const_iterator i = points.begin(); i != points.end(); ++i)
		cout << *i << ", ";
	cout << endl;
	return 0;
}
*/

