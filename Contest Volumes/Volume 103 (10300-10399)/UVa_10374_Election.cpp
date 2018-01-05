
/*
	UVa 10374 - Election

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10374_Election.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	while (nr_cases--) {
		getline(cin, line); // skip a blank line
		map<string, size_t> candidates;
			// key is a candidate name and value is the number that identifies the candidate
		map<size_t, string> parties;
			// key is a candidate number and value is the party that the candidate belongs to
		map<size_t, int> ballots;
		// key is a candidate number and value is the ballot that the candiate got.
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		while (n--) {
			getline(cin, line);
			size_t id = candidates.size();
			candidates.insert(make_pair(line, id));
			getline(cin, line);
			parties.insert(make_pair(id, line));
		}
		getline(cin, line);
		iss.str(line);
		int m;
		iss >> m;
		iss.clear();
		while (m--) {
			getline(cin, line);
			map<string, size_t>::iterator i = candidates.find(line);
			if (i != candidates.end()) {
				pair<map<size_t, int>::iterator, bool> result = ballots.insert(make_pair(i->second, 1));
				if (!result.second)
					result.first->second++;
			}
		}
		int max_ballots = -1;
		for (map<size_t, int>::const_iterator i = ballots.begin(), e = ballots.end(); i != e; ++i)
			if (i->second > max_ballots)
				max_ballots = i->second;
		size_t id = candidates.size();
		for (map<size_t, int>::const_iterator i = ballots.begin(), e = ballots.end(); i != e; ++i)
			if (i->second == max_ballots) {
				if (id == candidates.size())
					id = i->first;
				else {
					id = candidates.size();
					break;
				}
			}
		if (id == candidates.size())
			cout << "tie\n";
		else
			cout << parties[id] << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

