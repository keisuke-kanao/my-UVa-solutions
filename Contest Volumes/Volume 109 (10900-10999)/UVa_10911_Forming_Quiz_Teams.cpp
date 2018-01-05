/*
	UVa 10911 - Forming Quiz Teams

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10911_Forming_Quiz_Teams.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>

const int n_max = 16, nr_chars_max = 20;
const double max_s = 1000.0 * static_cast<double>(n_max);

struct point {
	int x, y;
} points[n_max];

bool assigned[n_max]; // assigned[i] is true if i-th member has already been assigned to a team
double distances[n_max][n_max]; // distances[i][j] is the distance between i and j

double euclidean_distance(const point& p1, const point& p2)
{
	double dx = static_cast<double>(p1.x - p2.x), dy = static_cast<double>(p1.y - p2.y);
	return sqrt(dx * dx + dy * dy);
}

void form_quiz_teams(int n, int i, double s, double& min_s)
{
	if (i == n) {
		if (s < min_s)
			min_s = s;
	}
	else if (s < min_s) {
		if (assigned[i])
			form_quiz_teams(n, i + 1, s, min_s);
		else {
			assigned[i] = true;
			for (int j = 0; j < n; j++)
				if (j != i && !assigned[j]) {
					assigned[j] = true;
					form_quiz_teams(n, i + 1, s + distances[i][j], min_s);
					assigned[j] = false;
				}
			assigned[i] = false;
		}
	}
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		n <<= 1; // n * 2
		char s[nr_chars_max + 1];
		for (int i = 0; i < n; i++)
			scanf("%s %d %d", s, &points[i].x, &points[i].y);
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				distances[i][j] = distances[j][i] = euclidean_distance(points[i], points[j]);
		memset(assigned, 0, sizeof(assigned));
		double min_s = max_s;
		form_quiz_teams(n, 0, 0.0, min_s);
		printf("Case %d: %.2lf\n", case_nr, min_s);
	}
	return 0;
}

