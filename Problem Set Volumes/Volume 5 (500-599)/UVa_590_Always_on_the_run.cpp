
/*
	UVa 590 - Always on the run

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_590_Always_on_the_run.cpp

	from Western and Southwestern European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1997/index.html)
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_cities_max = 10, nr_flights_max = 1000, nr_days_max = 30;

struct schedule {
	int nr_days_;
	int prices_[nr_days_max];
};

schedule schedules[nr_cities_max][nr_cities_max];
	// schedules[i][j] is the schedule from i-th city j-th city
int costs[2][nr_cities_max][nr_cities_max];
	// costs[k][i][j] is the ((k - 1) % 2)-th day's cost from from i-th city j-th city

int main()
{
	for (int scenario_nr = 1; ; scenario_nr++) {
		int nr_cities, nr_flights;
		cin >> nr_cities >> nr_flights;
		if (!nr_cities && !nr_flights)
			break;
		for (int i = 0; i < nr_cities; i++)
			for (int j = 0; j < nr_cities; j++)
				if (i != j) {
					schedule& s = schedules[i][j];
					cin >> s.nr_days_;
					for (int d = 0; d < s.nr_days_; d++)
						cin >> s.prices_[d];
				}

		for (int i = 0; i < nr_cities; i++)
			for (int j = 0; j < nr_cities; j++)
				costs[0][i][j] = (i != j) ? schedules[i][j].prices_[0] : 0;
		for (int k = 1; k < nr_flights; k++)
			for (int i = 0; i < nr_cities; i++)
				for (int j = 0; j < nr_cities; j++) {
					int c = 0;
					for (int l = 0; l < nr_cities; l++)
						if (l != j) {
							int cil = costs[(k - 1) % 2][i][l],
								clj = schedules[l][j].prices_[k % schedules[l][j].nr_days_];
							if (cil && clj) {
								int cilj = cil + clj;
								c = (c) ? min(c, cilj) : cilj;
							}
						}
					costs[k % 2][i][j] = c;
				}

		cout << "Scenario #" << scenario_nr << endl;
		int c = costs[(nr_flights - 1) % 2][0][nr_cities - 1];
		if (c)
			cout << "The best flight costs " << c << ".\n\n";
		else
			cout << "No flight possible.\n\n";
	}
	return 0;
}

