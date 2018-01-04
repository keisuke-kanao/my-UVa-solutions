
/*
	UVa 349 - Transferable Voting (II)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_349_Transferable_Voting_II.cpp

	from 1996 ACM North Central Programming Contest November 9, 1996, Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1996/prob_e.html)
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_votes_max = 100, nr_candidates_max = 5;

struct ballot {
	int ci_; // index to the next choices_[], or -1, if no more choices_[] will be examined
	bool votes_[nr_candidates_max + 1];
	int choices_[nr_candidates_max];
} ballots[nr_votes_max];

int votes[nr_candidates_max + 1];
	// votes[i] is the number of votes for the candidate of i, or -1 for eliminated candidates

int main()
{
	for (int e = 1; ; e++) {
		int c, n;
		scanf("%d %d", &c, &n);
		if (!c && !n)
			break;
		int nr_ballots = 0, nr_bad_ballots = 0;
		memset(votes, 0, sizeof(votes));
		for (int i = 0; i < n; i++) {
			ballot& b = ballots[nr_ballots];
			memset(b.votes_, 0, sizeof(b.votes_));
			bool bad = false;
			for (int j = 0; j < c; j++) {
				scanf("%d", &b.choices_[j]);
				if (b.choices_[j] < 1 || b.choices_[j] > c || b.votes_[b.choices_[j]])
					bad = true;
				else
					b.votes_[b.choices_[j]] = true;
			}
			if (bad)
				nr_bad_ballots++;
			else {
				b.ci_ = 0;
				nr_ballots++;
			}
		}
		int nr_majority = nr_ballots / 2 + 1;
		int max_votes, min_votes, max_c, min_c;
		for (int cc = c; cc > 1; cc--) {
			for (int i = 0; i < nr_ballots; i++) {
				ballot& b = ballots[i];
				if (b.ci_ != -1)
					votes[b.choices_[b.ci_]]++;
			}
			max_votes = 0, min_votes = nr_ballots + 1;
			for (int i = 1; i <= c; i++)
				if (votes[i] != -1) {
					max_votes = max(max_votes, votes[i]);
					min_votes = min(min_votes, votes[i]);
				}
			max_c = -1, min_c = -1;
			for (int i = 1; i <= c; i++) {
				if (votes[i] == max_votes) {
					if (max_c == -1)
						max_c = i;
					else
						max_c = -1;
				}
				if (votes[i] == min_votes) {
					if (min_c == -1)
						min_c = i;
				}
			}
			if (max_votes >= nr_majority && max_c != -1)
				break; // one candidate is elected
			else {
				for (int i = 0; i < n; i++) {
					ballot& b = ballots[i];
					if (b.choices_[b.ci_] == min_c)
						b.ci_++;
					else
						b.ci_ = -1;
				}
			}
		}
		printf("Election #%d\n", e);
		if (nr_bad_ballots)
			printf("   %d bad ballot(s)\n", nr_bad_ballots);
		if (max_c != -1)
			printf("   Candidate %d is elected.\n", max_c);
		else {
			printf("   The following candidates are tied:");
			for (int i = 1; i <= c; i++)
				if (votes[i] == max_votes)
					printf(" %d", i);
			putchar('\n');
		}
	}
	return 0;
}

