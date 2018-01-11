
/*
	UVa 10714 - Ants

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10714_Ants.cpp
*/

/*
	from http://www.questtosolve.com/browse.php?vol=107

Keep two variables, min and max, that'll be the eventual output. 
For each ant, find two distances, the distance to the nearer end, and the distance to the farther end. 

min = max(distance to near end, min)
max = max(distance to far end, max)

And what about the business of ants changing direction when they collide? Doesn't matter. 
Consider what it be like if they walked through each other. It would be exactly the same.
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int pole_length, nr_ants;
		cin >> pole_length >> nr_ants;
		int earliest_time = 0, latest_time = 0;
		for (int i = 0; i < nr_ants; i++) {
			int distance_to_near_end;
			cin >> distance_to_near_end;
			int distance_to_farther_end = pole_length - distance_to_near_end;
			if (distance_to_near_end > distance_to_farther_end)
				swap(distance_to_near_end, distance_to_farther_end);
			earliest_time = max(earliest_time, distance_to_near_end);
			latest_time = max(latest_time, distance_to_farther_end);
		}
		cout << earliest_time << ' ' << latest_time << endl;
	}
	return 0;
}

