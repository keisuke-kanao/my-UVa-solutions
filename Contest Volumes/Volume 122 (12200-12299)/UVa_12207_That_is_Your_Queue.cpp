
/*
	UVa 12207 - That is Your Queue

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12207_That_is_Your_Queue.cpp
*/

#include <list>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	const int C_max = 1000;
	for (int case_nr = 1; ; case_nr++) {
		int P, C;
		scanf("%d %d", &P, &C);
		if (!P)
			break;
		printf("Case %d:\n", case_nr);
		list<int> admissions;
		for (int i = 1, e = min(P, C_max); i <= e; i++)
			admissions.push_back(i);
		while (C--) {
			char command[2];
			int x;
			scanf("%s", command);
			if (command[0] == 'N') {
				x = admissions.front(); admissions.pop_front();
				printf("%d\n", x);
				admissions.push_back(x);
			}
			else {
				scanf("%d", &x);
				admissions.remove(x);
				admissions.push_front(x);
			}
		}
	}
	return 0;
}

