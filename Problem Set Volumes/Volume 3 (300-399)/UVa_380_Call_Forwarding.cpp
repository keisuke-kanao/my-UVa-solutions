
/*
	UVa 380 - Call Forwarding

	To build using Visucal Studio 2012:
		cl -EHsc UVa_380_Call_Forwarding.cpp

	from ACM Mid-Atlantic Regionals - 1996, Problem 4
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidAtl/1996/index.html)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

struct call_forwarding {
	int t_; // target
	int st_, et_; // start time, end time

	call_forwarding(int t, int st, int et) : t_(t), st_(st), et_(et) {}
	bool operator<(const call_forwarding& cf) const {return st_ < cf.st_;}
};

struct request {
	bool f_; // true if forwarded
	vector<call_forwarding> forwardings_;
	request() : f_(false) {}
};

int call_forward(int t, int s, map<int, request>& requests)
{
	for (map<int, request>::iterator i = requests.begin(), e = requests.end(); i != e; ++i)
		i->second.f_ = false;
	while (true) {
		map<int, request>::iterator i = requests.find(s);
		if (i == requests.end()) // forwarding is not registered
			return s;
		else if (i->second.f_) // already has been forwarded
			return 9999;
		else {
			i->second.f_ = true;
			s = -1;
			for (vector<call_forwarding>::const_iterator j = i->second.forwardings_.begin(), e = i->second.forwardings_.end();
				j != e; ++j)
				if (t >= j->st_ && t <= j->et_) {
					s = j->t_; break;
				}
			if (s == -1)
				return i->first;
		}
	}
}

int main()
{
	cout << "CALL FORWARDING OUTPUT\n";
	int nr_systems;
	cin >> nr_systems;
	for (int ns = 1; ns <= nr_systems; ns++) {
		map<int, request> requests;
		while (true) {
			int s, t, st, d;
			cin >> s;
			if (!s)
				break;
			cin >> st >> d >> t;
			pair<map<int, request>::iterator, bool> result = requests.insert(make_pair(s, request()));
			result.first->second.forwardings_.push_back(call_forwarding(t, st, st + d));
		}
		cout << "SYSTEM " << ns << endl;
		while (true) {
			int t, s;
			cin >> t;
			if (t == 9000)
				break;
			cin >> s;
			cout << "AT " << setfill('0') << setw(4) << t << " CALL TO " << setw(4) << s << " RINGS " <<
				setw(4) << call_forward(t, s, requests) << endl;
		}
	}
	cout << "END OF OUTPUT\n";
	return 0;
}

