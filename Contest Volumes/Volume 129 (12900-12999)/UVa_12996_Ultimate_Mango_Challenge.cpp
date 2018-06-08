
/*
    UVa 12996 - Ultimate Mango Challenge

    To build using Visual Studio 2015:
        cl -EHsc -O2 UVa_12996_Ultimate_Mango_Challenge.cpp
*/

#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        const int N_max = 10;
        int nr_mangos[N_max];
        int N, L;
        scanf("%d %d", &N, &L);
        bool yes = true;
        int s = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", &nr_mangos[i]);
            s += nr_mangos[i];
        }
        if (s > L)
            yes = false;
        for (int i = 0; i < N; i++) {
            int l;
            scanf("%d", &l);
            if (l < nr_mangos[i])
                yes = false;
        }
        printf("Case %d: %s\n", t, ((yes) ? "Yes" : "No"));
    }
    return 0;
}

