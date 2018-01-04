
/*
	UVa 12096 - The SetStack Computer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12096_The_SetStack_Computer.cpp

	This is an accepted solution.
*/

#include <stack>
#include <set>
#include <map>
#include <cstdio>
using namespace std;

int main()
{
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		stack< set<size_t> > st;
		map<set<size_t>, size_t> sets;
		set<size_t> empty_set;
		sets.insert(make_pair(empty_set, sets.size()));
		while (N--) {
			const int nr_chars_max = 9;
			char s[nr_chars_max + 1];
			scanf("%s", s);
			switch (s[0]) {
			case 'P':
				st.push(empty_set);
				break;
			case 'D':
				st.push(st.top());
				break;
			case 'U':
			{
				set<size_t> first = st.top();
				st.pop();
				set<size_t>& second = st.top();
				for (set<size_t>::const_iterator i = first.begin(), e = first.end(); i != e; ++i)
					second.insert(*i);
				sets.insert(make_pair(second, sets.size()));
			}
				break;
			case 'I':
			{
				set<size_t> first = st.top();
				st.pop();
				set<size_t>& second = st.top();
				set<size_t>::const_iterator fi = first.begin(), fe = first.end();
				set<size_t>::iterator si = second.begin(), se = second.end();
				while (fi != fe && si != se) {
					if (*fi < *si)
						++fi;
					else if (*fi > *si)
						second.erase(si++);
					else
						++fi, ++si;
				}
				while (si != se)
					second.erase(si++);
				sets.insert(make_pair(second, sets.size()));
			}
				break;
			case 'A':
			{
				set<size_t> first = st.top();
				st.pop();
				set<size_t>& second = st.top();
				second.insert(sets[first]);
				sets.insert(make_pair(second, sets.size()));
			}
				break;
			}
			printf("%u\n", st.top().size());
		}
		puts("***");
	}
  return 0;
}

