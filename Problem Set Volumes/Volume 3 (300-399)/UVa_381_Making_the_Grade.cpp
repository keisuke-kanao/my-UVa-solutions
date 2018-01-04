
/*
	UVa 381 - Making the Grade

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_381_Making_the_Grade.cpp
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int S_max = 30, T_max = 10;

struct student {
	int scores_[T_max];
	int bonus_points_, absences_;
	double average_;
	int grade_;
} students[S_max];

int main()
{
	int N;
	scanf("%d", &N);
	puts("MAKING THE GRADE OUTPUT");
	while (N--) {
		int S, T;
		scanf("%d %d", &S, &T);
		for (int i = 0; i < S; i++) {
			student& st = students[i];
			for (int j = 0; j < T; j++)
				scanf("%d", &st.scores_[j]);
			if (T > 2)
				sort(st.scores_, st.scores_ + T);
			scanf("%d %d", &st.bonus_points_, &st.absences_);
		}
		double ss = 0.0;
		for (int i = 0; i < S; i++) { // calculate each student's average score
			student& st = students[i];
			if (T > 2) {
				int s = 0;
				for (int j = 1; j < T; j++)
					s += st.scores_[j];
				st.average_ = s / static_cast<double>(T - 1);
			}
			else
				st.average_ = static_cast<double>(st.scores_[0] + st.scores_[1]) / 2.0;
#ifdef DEBUG
				printf("%0.1lf%c", st.average_, ((i < S - 1) ? ' ' : '\n'));
#endif
			ss += st.average_;
		}
		// calculate the mean and sd
		double mean = ss / S;
		ss = 0;
		for (int i = 0; i < S; i++)
			ss += (students[i].average_ - mean) * (students[i].average_ - mean);
		double sd = sqrt(ss / static_cast<double>(S));
		if (sd < 1.0)
			sd = 1.0;
#ifdef DEBUG
		printf("mean: %0.1lf: sd: %0.1lf\n", mean, sd);
#endif
		double gp = 0.0;
		for (int i = 0; i < S; i++) {
			student& st = students[i];
			st.average_ += (st.bonus_points_ / 2) * 3;
			if (st.average_ >= mean + sd)
				st.grade_ = 0;
			else if (st.average_ >= mean)
				st.grade_ = 1;
			else if (st.average_ >= mean - sd)
				st.grade_ = 2;
			else
				st.grade_ = 3;
			if (st.absences_)
				st.grade_ = min(st.grade_ + st.absences_ / 4, 4);
			else
				st.grade_ = max(st.grade_ - 1, 0);
#ifdef DEBUG
			printf("%c%c", ((st.grade_ < 4) ? 'A' + st.grade_ : 'F'), ((i < S - 1) ? ' ' : '\n'));
#endif
			switch (st.grade_) {
			case 0: // A
				gp += 4.0; break;
			case 1: // B
				gp += 3.0; break;
			case 2: // C
				gp += 2.0; break;
			case 3: // D
				gp += 1.0; break;
			default: // F
				break;
			}
		}
		printf("%0.1lf\n", gp / S);
	}
	puts("END OF OUTPUT");
	return 0;
}

