
/*
	UVa 790 - Head Judge Headache

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_790_Head_Judge_Headache.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

const int nr_teams_max = 25, nr_problems = 'G' - 'A' + 1;

struct submission {
	int time_;
	char status_; // 'Y' or 'N'

	submission() {}
	submission(int time, char status) : time_(time), status_(status) {}

	bool operator<(const submission& s) const
	{
		if (time_ != s.time_)
			return time_ < s.time_;
		else
			return status_ < s.status_;
	}
};

struct team {
	int nr_;
	int nr_solved_;
	int time_consumed_;
	vector< vector<submission> > submissions_;

	team() : nr_(nr_teams_max + 1), nr_solved_(0), time_consumed_(0), submissions_(nr_problems, vector<submission>()) {}

	bool operator<(const team& t) const
	{
		if (nr_solved_ != t.nr_solved_)
			return nr_solved_ > t.nr_solved_;
		else if (time_consumed_ != t.time_consumed_)
			return time_consumed_ < t.time_consumed_;
		else
			return nr_ < t.nr_;
	}
};

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	int nr_cases;
	iss.str(line);
	iss >> nr_cases;
	iss.clear();
	getline(cin, line);
	while (nr_cases--) {
		vector<team> teams(nr_teams_max);
		int nr_max = 0;
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			int nr, h, m;
			char pl, sr, c;
			iss >> nr >> pl >> h >> c >> m >> sr;
			iss.clear();
			if (nr > nr_max)
				nr_max = nr;
			teams[nr - 1].submissions_[pl - 'A'].push_back(submission(h * 60 + m, sr));
		}
		for (int i = 0; i < nr_teams_max; i++)
			if (i < nr_max) {
				team& t = teams[i];
				t.nr_ = i + 1;
				for (int j = 0; j < nr_problems; j++) {
					vector<submission>& submissions = t.submissions_[j];
					sort(submissions.begin(), submissions.end());
					for (int k = 0; k < submissions.size(); k++)
						if (submissions[k].status_ == 'Y') {
							t.nr_solved_++;
							t.time_consumed_ += submissions[k].time_ + k * 20;
							break;
						}
				}
			}
		sort(teams.begin(), teams.begin() + nr_teams_max);
		cout << "RANK TEAM PRO/SOLVED TIME\n";
		for (int i = 0, rank = 0; i < nr_teams_max && teams[i].nr_ <= nr_teams_max; i++) {
			if (!i || teams[i].nr_solved_ != teams[i - 1].nr_solved_ ||
				teams[i].time_consumed_ != teams[i - 1].time_consumed_)
				rank = i + 1;
			if (teams[i].nr_solved_)
				cout << setw(4) << rank << setw(5) << teams[i].nr_ << setw(5) << teams[i].nr_solved_ << setw(11) << teams[i].time_consumed_ << endl;
			else
				cout << setw(4) << rank << setw(5) << teams[i].nr_ << endl;
		}
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

