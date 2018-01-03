
/*
	UVa 939 - Genes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_939_Genes.cpp
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

const int N_max = 3100;

map<string, int> names;

enum {non_existent, recessive, dominant};

const int nr_status = dominant - non_existent + 1;

const string status_strings[nr_status] = {
	"non-existent", "recessive", "dominant"
};

const int hypothesis[nr_status][nr_status] = {
	{non_existent, non_existent, recessive},
	{non_existent, recessive, dominant},
	{recessive, dominant, dominant}
};

struct person {
	int parent_, other_parent_;
	int status_;
} persons[N_max];

int get_status(int pi)
{
	if (persons[pi].status_ != -1)
		return persons[pi].status_;
	int parent_status = get_status(persons[pi].parent_),
		other_parent_status = get_status(persons[pi].other_parent_);
	return persons[pi].status_ = hypothesis[parent_status][other_parent_status];
}

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		persons[i].parent_ = persons[i].other_parent_ = persons[i].status_ = -1;
	int nr_persons = 0;
	while (N--) {
		string s, t;
		cin >> s >> t;
		pair<map<string, int>::iterator, bool> result = names.insert(make_pair(s, nr_persons));
		int pi = result.first->second;
		if (result.second)
			nr_persons++;
		int i;
		for (i = 0; i < nr_status; i++)
			if (t == status_strings[i]) {
				persons[pi].status_ = i;
				break;
			}
		if (i == nr_status) {
			result = names.insert(make_pair(t, nr_persons));
			person& c = persons[result.first->second];
			if (c.parent_ == -1)
				c.parent_ = pi;
			else
				c.other_parent_ = pi;
			if (result.second)
				nr_persons++;
		}
	}
	for (map<string, int>::const_iterator ni = names.begin(), ne = names.end(); ni != ne; ++ni)
		cout << ni->first << ' ' << status_strings[get_status(ni->second)] << endl;
	return 0;
}

