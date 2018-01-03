
/*
	UVa 1203 - Argus

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1203_Argus.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int nr_instructions_max = 1000;
struct instruction {
	int q_num_;
	int period_;
} instructions[nr_instructions_max];

struct query_comparator {
	bool operator() (const pair<int, int>& i, const pair<int, int>& j) const;
};

bool query_comparator::operator() (const pair<int, int>& i, const pair<int, int>& j) const
{
	if (i.second > j.second)
		return true;
	else if (i.second < j.second)
		return false;
	else
		return instructions[i.first].q_num_ > instructions[j.first].q_num_;
}

int main()
{
	int nr_instructions = 0;
	while (true) {
		string s;
		cin >> s;
		if (s[0] == '#')
			break;
		cin >> instructions[nr_instructions].q_num_ >> instructions[nr_instructions].period_;
		nr_instructions++;
	}
	int k;
	cin >> k;
	priority_queue< pair<int, int>, vector< pair<int, int> >, query_comparator > pq;
	for (int i = 0; i < nr_instructions; i++)
		pq.push(make_pair(i, instructions[i].period_));
	while (k--) {
		pair<int, int> q = pq.top();
		pq.pop();
#ifdef DEBUG
		cout << instructions[q.first].q_num_ << ' ' << q.second << endl;
#else
		cout << instructions[q.first].q_num_ << endl;
#endif
		pq.push(make_pair(q.first, q.second + instructions[q.first].period_));
	}
	return 0;
}

