
/*
	UVa 10112 - Myacm Triangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10112_Myacm_Triangles.cpp

	from ACM Mid Central Regionals 1999
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1999/index.html)
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct monument {
	char label_;
	int x_, y_;

	bool operator<(const monument& m) const {return label_ < m.label_;}
};

const int nr_monuments_max = 15;
monument monuments[nr_monuments_max];
int areas[nr_monuments_max][nr_monuments_max][nr_monuments_max];
	// areas[i][j][k] is the area of triangle that is made up of monuments[i], monuments[j], and monuments[k]

int triangle_area(const monument& m1, const monument& m2, const monument& m3)
{
	return labs((m3.y_ - m1.y_) * (m2.x_ - m1.x_) - (m2.y_ - m1.y_) * (m3.x_ - m1.x_)); // twice of a triangle area
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> monuments[i].label_ >> monuments[i].x_ >> monuments[i].y_;
		sort(monuments, monuments + n);
		for (int i = 0; i < n - 2; i++)
			for (int j = i + 1; j < n - 1; j++)
				for (int k = j + 1; k < n; k++) {
					int area = triangle_area(monuments[i], monuments[j], monuments[k]);
					areas[i][j][k] = areas[i][k][j] = areas[j][i][k] = areas[j][k][i] = areas[k][i][j] = areas[k][j][i] = area;
#ifdef DEBUG
					cout << monuments[i].label_ << monuments[j].label_ << monuments[k].label_ << ' ' << area << endl;
#endif
				}
		int ti, tj, tk, max_area = 0;
		for (int i = 0; i < n - 2; i++)
			for (int j = i + 1; j < n - 1; j++)
				for (int k = j + 1; k < n; k++) {
					int area = areas[i][j][k];
					bool monument_in_triangle = false;
					for (int l = 0; l < n; l++) {
						if (l == i || l == j || l == k)
							continue;
						if (areas[i][j][l] + areas[i][l][k] + areas[l][j][k] == area) {
							// monuments[l] is in the triangle of monuments[i], monuments[j], and monuments[k]
							monument_in_triangle = true; break;
						}
					}
					if (!monument_in_triangle && area > max_area) {
						ti = i; tj = j; tk = k;
						max_area = area;
					}
				}
		cout << monuments[ti].label_ << monuments[tj].label_ << monuments[tk].label_ << endl;
	}
	return 0;
}

