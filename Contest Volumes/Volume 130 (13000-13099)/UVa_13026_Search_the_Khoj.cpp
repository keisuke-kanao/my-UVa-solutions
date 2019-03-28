
/*
    UVa 13026 - Search the Khoj

    To build using Visual Studio 2015:
        cl -EHsc -O2 UVa_13026_Search_the_Khoj.cpp
*/

#include <cstdio>

const int N_max = 1000, nr_chars = 11;
char numbers[N_max][nr_chars + 1];

bool compare_number(const char* m, const char* n)
{
    for (int d = 0; *m; m++, n++)
        if (*m != *n) {
            if (d++)
                return false;
        }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%s", numbers[i]);
        char mnumber[nr_chars + 1];
        scanf("%s", mnumber);
        printf("Case %d:\n", t);
        for (int i = 0; i < N; i++)
            if (compare_number(mnumber, numbers[i]))
                printf("%s\n", numbers[i]);
    }
    return 0;
}

/*
Sample Input

2
3
0123456
0012345
0123457
0123458
2
123
124
123

Sample Output

Case 1:
0123456
0123457
Case 2:
123
124

*/

