
/*
	UVa 11269 - Setting Problems

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11269_Setting_Problems.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

/*
This is a greedy problem though there is a known algorithm for it called the Johnson's scheduling algorithm. 
Basically partition the tasks into two. Those with s <= g put into list 1 and those with s > g put into list 2. 
Sort list 1 in ascending values of S and sort list 2 in descending values of G. 
Then add up all the S values together to a total. 
For the G values, it is slightly more complicated. 
If a G value is greater than the S value of the task after it, then add the difference to the G of the task that comes after it.
*/

const int nr_problems_max = 100;

struct problem {
	int s_, g_;
} problems[nr_problems_max], slist[nr_problems_max], glist[nr_problems_max];

bool compare_s(const problem& i, const problem& j)
{
	return i.s_ < j.s_;
}

bool compare_g(const problem& i, const problem& j)
{
	return i.g_ > j.g_;
}

int main()
{
	int N;
	while (cin >> N) {
		for (int i = 0; i < N; i++)
			cin >> problems[i].s_;
		for (int i = 0; i < N; i++)
			cin >> problems[i].g_;
		int ns = 0, ng = 0;
		for (int i = 0; i < N; i++)
			if (problems[i].s_ <= problems[i].g_) {
				slist[ns].s_ = problems[i].s_;
				slist[ns].g_ = problems[i].g_;
				ns++;
			}
			else {
				glist[ng].s_ = problems[i].s_;
				glist[ng].g_ = problems[i].g_;
				ng++;
			}
		sort(slist, slist + ns, compare_s);
		sort(glist, glist + ng, compare_g);
		for (int i = 0; i < ng; i++) {
			slist[ns + i].s_ = glist[i].s_;
			slist[ns + i].g_ = glist[i].g_;
		}
		int st = slist[0].s_, gt = st + slist[0].g_;
		for (int i = 1; i < N; i++) {
			st += slist[i].s_;
			if (gt > st)
				gt += slist[i].g_;
			else
				gt = st + slist[i].g_;
		}
		cout << gt << endl;
	}
	return 0;
}

