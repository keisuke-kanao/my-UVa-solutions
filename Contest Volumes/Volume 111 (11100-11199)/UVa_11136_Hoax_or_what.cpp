
/*
	UVa 11136 - Hoax or what

	To build using Visual Studio 2012:
 		cl -EHsc -O2 UVa_11136_Hoax_or_what.cpp
*/

#include <set>
#include <cstdio>
using namespace std;

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		long long paid = 0;
		multiset<int> bills;
		while (n--) {
			int k;
			scanf("%d", &k);
			while (k--) {
				int b;
				scanf("%d", &b);
				bills.insert(b);
			}
			paid += *bills.rbegin() - *bills.begin();
			bills.erase(bills.begin());
			bills.erase(--bills.rbegin().base());
		}
		printf("%lld\n", paid);
	}
	return 0;
}

