
/*
	UVa 882 - The Mailbox Manufacturers Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_882_The_Mailbox_Manufacturers_Problem.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
https://apps.topcoder.com/forums/?module=Thread&threadID=667388&start=0&mc=5

I don't know if this approach is fast enough, but consider the DP state

f(min crackers, max crackers, mailboxes left)

Which is the smallest number of crackers required, 
when min crackers is the largest number of crackers for which a mailbox is known to have survived and 
     max crackers is the smallest number of crackers for which a mailbox is known to have failed. 
For the next test, choose some number of crackers X between min crackers and max crackers. 
Since we don't know what the outcome will be, we have to take the maximum of the resulting states 
where the mailbox fails and the mailbox survives. I.e.,

f(min, max, boxes) = X + max(f(X, max, boxes), f(min, X, boxes-1))

The answer is the minimum over X of this value.
*/

const int k_max = 10, m_max = 100;
const int infinite = m_max * (m_max + 1) / 2 + 1;

int nr_crackers[k_max + 1][m_max + 1][m_max + 1];

int fire_crackers(int k, int low, int high)
{
	int& nr = nr_crackers[k][low][high];
	if (nr != -1)
		return nr;
	if (low == high)
		return nr = 0;
	nr = infinite;
	if (!k)
		return nr;
	for (int i = low + 1; i <= high; i++)
		nr = min(nr, i + max(fire_crackers(k - 1, low, i - 1), fire_crackers(k, i, high)));
	return nr;
}

int main()
{
	memset(nr_crackers, -1, sizeof(nr_crackers));
	int N;
	scanf("%d", &N);
	while (N--) {
		int k, m;
		scanf("%d%d", &k, &m);
		printf("%d\n", fire_crackers(k, 0, m));
	}
	return 0;
}

