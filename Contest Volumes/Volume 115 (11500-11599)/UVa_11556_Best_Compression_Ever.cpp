
/*
	UVa 11556 - Best Compression Ever

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11556_Best_Compression_Ever.cpp
*/

#include <cstdio>

int main()
{
	long long n = 1, N;
	int b;
	while (scanf("%lld %d", &N, &b) != EOF)
		puts((N < n << (b + 1)) ? "yes" : "no");
	return 0;
}

/*
Sample Input

13 3
1 0
31415926535897 40

Sample Output

yes
yes
no

*/

/*
Sample Input

1000000000000000 0
1 50
999999999999999 49
500000 1
160 50
780000000 47
20000 33
4852999999 12
1558888 26
16 14
157 6
160009 38
14700000587 47
13477 18
654 49

Sample Output

no
yes
yes
no
yes
yes
yes
no
yes
yes
no
yes
yes
yes
yes

*/

/*

2 0		no
2 1		yes			2	1

3 0		no
3 1		yes
3 2		yes

4 0		no
4 1		no
4 2		yes			4	2

5 0		no
5 1		no
5 2		yes
5 3		yes

6 0		no
6 1		no
6 2		yes
6 3		yes

7 0		no
7 1		no
7 2		yes
7 3		yes

8 0		no
8 1		no
8 2		no
8 3		yes			8	3

9 0		no
9 1		no
9 2		no
9 3		yes

10 0	no
10 1	no
10 2	no
10 3	yes

11 0	no
11 1	no
11 2	no
11 3	yes

12 0	no
12 1	no
12 2	no
12 3	yes

13 0	no
13 1	no
13 2	no
13 3	yes

14 0	no
14 1	no
14 2	no
14 3	yes

15 0	no
15 1	no
15 2	no
15 3	yes

16 0	no
16 1	no
16 2	no
16 3	no
					16	4
*/

