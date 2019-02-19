
/*
    UVa 13275 - Leap Birthdays

    To build using Visual Studio 2015:
        cl -EHsc -O2 UVa_13275_Leap_Birthdays.cpp2267
*/

#include <cstdio>

bool is_leap_year(int year)
{
    if (year % 400 == 0) return true;
    else if(year % 100 == 0) return false;
    else if(year % 4 == 0) return true;
    else return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int D, M, Y, QY;
        scanf("%d %d %d %d", &D, &M, &Y, &QY);
        if (D != 29 || M != 2)
            printf("Case %d: %d\n", t, QY - Y);
        else {
            int n = 0;
            for (int y = Y + 4; y <= QY; y += 4)
                if (is_leap_year(y))
                    n++;
            printf("Case %d: %d\n", t, n);
        }
    }
    return 0;
}

