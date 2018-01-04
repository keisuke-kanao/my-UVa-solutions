
/*
	UVa 184 - Laser Lines

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_184_Laser_Lines.cpp

	from ACM South Pacific Regionals - 1993
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1993/index.html)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct point {
	int x, y;

	bool operator<(const point& p) const;
};

bool point::operator<(const point& p) const
{
	if (x < p.x)
		return true;
	else if (x > p.x)
		return false;
	else
		return y < p.y;
}

bool collinear(const point& p1, const point& p2, const point& p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) == 0;
}

int main()
{
	while (true) {
		point p;
		cin >> p.x >> p.y;
		if (!p.x && !p.y)
			break;
		vector<point> points;
		points.push_back(p);
		while (true) {
			cin >> p.x >> p.y;
			if (!p.x && !p.y)
				break;
			points.push_back(p);
		}
		sort(points.begin(), points.end());
		bool found = false;
		size_t nr_points = points.size();
		vector< pair<size_t, size_t> > lines; // pair of indices that form 'longer' lines
		for (size_t i = 0; i < nr_points - 2; i++)
			for (size_t j = i + 1; j < nr_points - 1; j++) {
				int nr_found = 0;
				for (size_t k = 0; k < lines.size(); k++)
					if (collinear(points[lines[k].first], points[lines[k].second], points[i]) &&
						collinear(points[lines[k].first], points[lines[k].second], points[j])) {
						nr_found = -1; break;
					}
				if (nr_found == -1)
					continue;

				for (size_t k = j + 1; k < nr_points; k++) {
					if (collinear(points[i], points[j], points[k])) {
						if (!found) {
							found = true;
							cout << "The following lines were found:\n";
						}
						if (!nr_found)
							cout << setfill(' ') << '(' << setw(4) << points[i].x << ',' << setw(4) << points[i].y << ')' <<
								'(' << setw(4) << points[j].x << ',' << setw(4) << points[j].y << ')';
						cout << '(' << setw(4) << points[k].x << ',' << setw(4) << points[k].y << ')';
						nr_found++;
					}
				}
				if (nr_found) {
					cout << endl;
					if (nr_found > 1)
						lines.push_back(make_pair(i, j));
				}
			}
		if (!found)
			cout <<"No lines were found\n";
	}
	return 0;
}

