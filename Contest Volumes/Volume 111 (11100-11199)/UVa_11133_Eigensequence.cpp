
/*
	UVa 11133 - Eigensequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11133_Eigensequence.cpp
*/

/*
This is a math and DP problem.
If an array is eigensequence, then a[n]%(a[n]-a[n-1])==0,
so a[n]=k*(a[n]-a[n-1]) for some integer k.
so a[n]-(a[n]-a[n-1])=a[n-1]=(k-1)*(a[n]-a[n-1])
so a[n-1]%(a[n]-a[n-1])==0.
In fact, for any integer b, if a[n-1]%b == 0, a[n-1]+b is a valid choice for a[n].(because a[n]%b==0).
For any interval [x,y], use f[x][y] to denote the number of eigensequence start with x and end with y.
f[x][y]=sum(f[x+i][y]) for all i which a%i==0 and a+i<b.
boundery cases: if x == y, f[x][y]=1;
if x > y, f[x][y]=0;
*/

#include <cstdio>

const int an_max = 44;
int nr_ess[an_max + 1][an_max + 1];
	// nr_ess[i][j] is the number of eigensequences start with i and end with j

int eigensequence(int a1, int an)
{
	int& nr = nr_ess[a1][an];
	if (nr == -1) {
		nr = 0;
		for (int i = 1; i <= an - a1; i++)
			if (!(a1 % i))
				nr += eigensequence(a1 + i, an);
	}
	return nr;
}

int main()
{
	while (true) {
		int a1, an;
		scanf("%d %d", &a1, &an);
		if (a1 >= an)
			break;
		for (int i = a1; i <= an; i++)
			for (int j = a1; j <= an; j++)
				nr_ess[i][j] = (i == j) ? 1 : ((i > j) ? 0 : -1);
		printf("%d %d %d\n", a1, an, eigensequence(a1, an));
	}
	return 0;
}

