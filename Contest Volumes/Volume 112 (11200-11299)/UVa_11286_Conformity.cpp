
/*
	UVa 11286 - Conformity

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11286_Conformity.cpp
*/

#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	const int nr_courses = 5;

	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		map<long long, int> combinations;
		for (int i = 0; i < n; i++) {
			int courses[nr_courses];
			for (int j = 0; j < nr_courses; j++)
				cin >> courses[j];
			sort(courses, courses + nr_courses);
			long long combination = 0;
			for (int j = 0; j < nr_courses; j++) {
				if (j)
					combination <<= 9;
				combination |= courses[j];
			}
			pair<map<long long, int>::iterator, bool> result = combinations.insert(make_pair(combination, 1));
			if (!result.second)
				result.first->second++;
		}
		int max_popularity = 0, nr_frosh;
		for (map<long long, int>::const_iterator ci = combinations.begin(), ce = combinations.end(); ci != ce; ++ci) {
			if (ci->second > max_popularity)
				max_popularity = nr_frosh = ci->second;
			else if (ci->second == max_popularity)
				nr_frosh += ci->second;
		}
		cout << nr_frosh << endl;
	}
	return 0;
}

