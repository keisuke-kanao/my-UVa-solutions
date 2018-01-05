
/*
	UVa 11239 - Open Source

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11239_Open_Source.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

struct project {
	string name_;
	int nr_students_;

	project() : nr_students_(0) {}
	project(const string& name) : name_(name), nr_students_(0) {}

	bool operator<(const project& p) const {
		if (nr_students_ > p.nr_students_)
			return true;
		else if (nr_students_ < p.nr_students_)
			return false;
		else
			return name_ < p.name_;
	}
};

int main()
{
	bool continued = false;
	string s;
	while (true) {
		vector<project> projects;
		map<string, int> students;
		int pi;
		while (true) {
			if (!continued)
				getline(cin, s);
			else
				continued = false;
			if (s[0] == '1')
				break;
			if (isupper(s[0])) {
				pi = static_cast<int>(projects.size());
				projects.push_back(project(s));
			}
			else {
				pair< map<string, int>::iterator, bool > result = students.insert(make_pair(s, pi));
				if (result.second)
					projects[pi].nr_students_++;
				else if (result.first->second != pi) {
					if (result.first->second != -1) {
						projects[result.first->second].nr_students_--;
						result.first->second = -1;
					}
				}
			}
		}
		sort(projects.begin(), projects.end());
		for (vector<project>::const_iterator i = projects.begin(), e = projects.end(); i != e; ++i)
			cout << i->name_ << ' ' << i->nr_students_ << endl;
		getline(cin, s);
		if (s[0] == '0')
			break;
		continued = true;
	}
	return 0;
}

