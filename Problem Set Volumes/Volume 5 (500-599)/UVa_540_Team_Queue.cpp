
/*
	UVa 540 - Team Queue

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_540_Team_Queue.cpp

	from University of Ulm Local Contest 1998 Problem D
		(http://www.informatik.uni-ulm.de/acm/Locals/1998/)

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int main()
{
	for (int s = 1; ; s++) {
		int nr_teams;
		cin >> nr_teams;
		if (!nr_teams)
			break;
		map<int, int> teams; // key is an element, value is the team that the element belongs to 
		for (int i = 0; i < nr_teams; i++) {
			int nr_elements;
			cin >> nr_elements;
			for (int j = 0; j < nr_elements; j++) {
				int element;
				cin >> element;
				teams.insert(make_pair(element, i));
			}
		}
		vector< queue<int> > tqs(nr_teams);
			// tqs[i] is the queue for i-th team
		queue<int> q;
			// items of q is the team indices
		cout << "Scenario #" << s << endl;
		while (true) {
			string command;
			cin >> command;
			if (command == "STOP")
				break;
			else if (command == "ENQUEUE") {
				int element;
				cin >> element;
				int team = teams[element];
				if (tqs[team].empty())
					q.push(team);
				tqs[team].push(element);
			}
			else { // DEQUEUE
				if (!q.empty()) {
					int team = q.front();
					cout << tqs[team].front() << endl;
					tqs[team].pop();
					if (tqs[team].empty())
						q.pop();
				}
			}
		}
		cout << endl;
	}
	return 0;
}

