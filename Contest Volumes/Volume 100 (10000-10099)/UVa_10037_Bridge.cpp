
/*
	4.6.3 Bridge
	PC/UVa IDs: 110403/10037, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10037_Bridge.cpp

	For more informaiton, see "Bridge and torch problem - Wikipedia, the free encyclopedia" 
	(http://en.wikipedia.org/wiki/Bridge_and_torch_problem).
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int schedule_bridge_crossing(vector<int>& people, int n, vector< pair<int, int> >& schedule)
{
	if (n == 1) {
// 		one people cross the bridge forward
		schedule.push_back(pair<int, int>(people[0], -1));
		return people[0];
	}
	else if (n == 2) {
//		two people cross the bridge forward
		schedule.push_back(pair<int, int>(people[0], people[1]));
		return people[1];
	}
	else if (n == 3) {
/*
		the fist and the third people cross the bridge forward, the first person returns, and 
		the fist and the second people cross the bridge forward
*/
		int t = people[2] + people[0] + people[1];
		schedule.push_back(pair<int, int>(people[0], people[2]));
		schedule.push_back(pair<int, int>(people[0], -1));
		schedule.push_back(pair<int, int>(people[0], people[1]));
		return t;
	}
	else {
/*
		The fist and the second people cross the bridge forward, the first people returns,
		the (n - 1)-th and the n-th people cross the bridge forward, and the second people returns
*/
		int t1 = people[0] + 2 * people[1] + people[n - 1];
/*
		The fist and the (n - 1)-th people cross the bridge forward, the first people returns,
		the first and the n-th people cross the bridge forward, and the first people returns
		Note that the order in which (n - 1)-th people and n-th people are crossed can be exchangable.
*/
		int t2 = 2 * people[0] + people[n - 2] + people[n - 1];
		if (t1 < t2) {
			schedule.push_back(pair<int, int>(people[0], people[1]));
			schedule.push_back(pair<int, int>(people[0], -1));
			schedule.push_back(pair<int, int>(people[n - 2], people[n - 1]));
			schedule.push_back(pair<int, int>(people[1], -1));
			return t1 + schedule_bridge_crossing(people, n - 2, schedule);
		}
		else {
			schedule.push_back(pair<int, int>(people[0], people[n - 1]));
			schedule.push_back(pair<int, int>(people[0], -1));
			schedule.push_back(pair<int, int>(people[0], people[n - 2]));
			schedule.push_back(pair<int, int>(people[0], -1));
			return t2 + schedule_bridge_crossing(people, n - 2, schedule);
		}
	}
}

int main(int /* argc */, char** /** argv */)
{
	// read the number of test cases
	int cases;
	cin >> cases;
	while (cases--) {
		// read the number of people
		int n;
		cin >> n;
		// read the crossing time of each peple and append it to the vector
		vector<int> people(n);
		for (int i = 0; i < n; i++)
			cin >> people[i];
		sort(people.begin(), people.end()); // sort the vector in the ascending order of thier crossing times
		vector< pair<int, int> > schedule;
		int t = schedule_bridge_crossing(people, n, schedule);
		cout << t << endl;
		for (vector< pair<int, int> >::const_iterator i = schedule.begin(); i != schedule.end(); i++) {
			cout << i->first;
			if (i->second != -1)
				cout << ' ' << i->second;
			cout << endl;
		}
		if (cases)
			cout << endl;
	}
	return 0;
}

