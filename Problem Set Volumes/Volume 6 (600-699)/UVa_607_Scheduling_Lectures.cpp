
/*
	UVa 607 - Scheduling Lectures

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_607_Scheduling_Lectures.cpp

	An accepted solution.
*/

#include <iostream>
#include <limits>
using namespace std;

const int n_max = 1000, L_max = 500;
int topics[n_max + 1];
int lectures[n_max + 1], DIs[n_max + 1];
	// lectures[i] is the lecture # for topic i, DIs[i] is the dissatisfaction index for topic i

int dissatisfaction_index(int t, int C)
{
    if (!t)
		return 0;
    else if (t <= 10)
		return -C;
    else
		return (t - 10) * (t - 10);
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (case_nr > 1)
			cout << endl;
		int L, C;
		cin >> L >> C;
		for (int i = 1; i <= n; i++)
			cin >> topics[i];
        for (int i = 1; i <= n; i++)
			lectures[i] = numeric_limits<int>::max();
        lectures[1] = 1;
		DIs[1] = dissatisfaction_index(L - topics[1], C);
		for (int i = 2; i <= n; i++) {
			int sum = 0;
			for (int j = i; j >= 1; j--) {
                sum += topics[j];
				if (sum > L)
					break;
				if (lectures[j - 1] + 1 < lectures[i]) {
					lectures[i] = lectures[j - 1] + 1;
					DIs[i] = DIs[j - 1] + dissatisfaction_index(L - sum, C);
				}
				else if (lectures[j - 1] + 1 == lectures[i]) {
					if (DIs[j - 1] + dissatisfaction_index(L - sum, C) < DIs[i])
						DIs[i] = DIs[j - 1] + dissatisfaction_index(L - sum, C);
				}
			}
			cout << i << ' ' << lectures[i] << ' ' << DIs[i] << endl;
		}
		cout << "Case " << case_nr << ":\n";
		cout << "Minimum number of lectures: " << lectures[n] << endl;
		cout << "Total dissatisfaction index: " << DIs[n] << endl;
	}
	return 0;
}

