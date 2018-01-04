
/*
	UVa 11926 - Multitasking

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11926_Multitasking.cpp
*/

#include <cstdio>
#include <cstring>

const int minutes_max = 1000000;

bool minutes[minutes_max + 1];

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		memset(minutes, 0, sizeof(minutes));
		bool conflict = false;
		while (n--) {
			int st, et;
			scanf("%d %d", &st, &et);
			if (conflict)
				continue;
			for (int i = st; i < et; i++) {
				if (minutes[i]) {
					conflict = true; break;
				}
				else
					minutes[i] = true;
			}
		}
		while (m--) {
			int st, et, ri;
			scanf("%d %d %d", &st, &et, &ri);
			if (conflict)
				continue;
			for (int i = 0; i <= minutes_max; i += ri) {
				for (int j = i + st; j <= minutes_max && j < i + et; j++) {
					if (minutes[j]) {
						conflict = true; break;
					}
					else
						minutes[j] = true;
				}
				if (conflict)
					break;
			}
		}
		puts(((conflict) ? "CONFLICT" : "NO CONFLICT"));
	}
	return 0;
}

