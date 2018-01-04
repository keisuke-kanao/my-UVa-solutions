
/*
	UVa 12470 - Tribonacci

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12470_Tribonacci.cpp
*/

#include <cstdio>

/*
t(k + 3)	1 1 1	t(k + 2)
t(k + 2) = 	1 0 0	t(k + 1)
t(k + 1)	0 1 0	t(k)
*/

long long tribonacci(long long n)
{
	const long long modulo = 1000000009;
	long long trib[3][3] = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}}, result[3][3]= {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	while (n) {
		if(n & 1) {
			long long r[3][3] = {};
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						r[i][j] = (r[i][j] + result[i][k] * trib[k][j] % modulo) % modulo;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					result[i][j] = r[i][j];
        }
		long long r[3][3]= {};
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					r[i][j] = (r[i][j] + trib[i][k] * trib[k][j] % modulo) % modulo;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				trib[i][j] = r[i][j];
		n /= 2;
	}
	return result[0][1];
}

int main()
{
	while (true) {
		long long n;
		scanf("%lld", &n);
		if (!n)
			break;
		printf("%lld\n", tribonacci(n - 1));
	}
	return 0;
}

