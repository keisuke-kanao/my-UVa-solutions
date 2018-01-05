
/*
	UVa 10655 - Contemplation! Algebra

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10655_Contemplation_Algebra.cpp
*/

#include <cstdio>

/*
	f(n) = a^n + b^n, then:
	f(0) = 1
	f(1) = a + b
	f(n) = (a + b) * f(n - 1) - a * b * f(n - 2) (n >= 2)

	This is a problem for Matrix multiplication and the typical solution is below.
*/

long long power(long long b, int e)
{
	if (e == 0)
		return 1;
	long long p = power(b, e / 2);
	p *= p;
	if (e % 2)
		p *= b;
	return p;
}

int main()
{
	while (true) {
		int p, q, n;
		if (scanf("%d %d %d", &p, &q, &n) == 2)
			break;
		long long v0 = 2, v1 = p, v;
		if (n == 0)
			v = v0;
		else if (n == 1)
			v = v1;
		else {
			if (p == 0 && q == 0)
				v = 0;
			else if (p == 0) { // f(n) = - a * b * f(n - 2)
				if (n % 2)
					v = v1 * power(-q, n / 2);
				else
					v = v0 * power(-q, n / 2);
			}
			else if (q == 0) // f(n) = (a + b) * f(n - 1)
				v = v1 * power(p, n - 1);
			else if (p == 2 && q == 1) // f(n) = f(0)
				v = v0;
			else {
				for (int i = 2; i <= n; i++) {
					v = p * v1 - q * v0;
#ifdef DEBUG
					printf("%lld %lld %lld\n", v, v1, v0);
#endif
/*
					if (v == v1 && v == v0)
						break;
*/
					v0 = v1, v1 = v;
				}
			}
		}
		printf("%lld\n", v);
	}
	return 0;
}

/*
# include<iostream>
# include<cstdio>
# include<cmath>
# include<cstring>
# include<algorithm>
using namespace std;
# define LL long long
struct matrix
{
    int r,c;
    LL m[3][3];
    matrix(int _r,int _c):r(_r),c(_c){}
};
void init(matrix &m,int a,int b)
{
    m.m[1][1]=a,m.m[1][2]=-b;
    m.m[2][1]=1,m.m[2][2]=0;
}
matrix multiply(matrix a,matrix b)
{
    matrix m(a.r,b.c);
    for(int i=1;i<=m.r;++i){
        for(int j=1;j<=m.c;++j){
            m.m[i][j]=0;
            for(int k=1;k<=a.c;++k)
                m.m[i][j]+=a.m[i][k]*b.m[k][j];
        }
    }
    return m;
}
matrix matrix_pow(matrix m,int n)
{
    if(n==0){
        m.m[1][1]=m.m[2][2]=1;
        m.m[1][2]=m.m[2][1]=0;
        return m;
    }
    if(n==1)
        return m;
    matrix res=matrix_pow(m,n/2);
    res=multiply(res,res);
    if(n&1)
        res=multiply(res,m);
    return res;
}
int main()
{
    LL a,b,n;
    while(scanf("%lld%lld%lld",&a,&b,&n)==3)
    {
        if(n==0){
            printf("2\n");
            continue;
        }
        if(n==1){
            printf("%d\n",a);
            continue;
        }
        matrix mat(2,2);
        init(mat,a,b);
        mat=matrix_pow(mat,n-2);
        matrix ans(2,1);
        ans.m[1][1]=a*a-2*b;
        ans.m[2][1]=a;
        ans=multiply(mat,ans);
        printf("%lld\n",ans.m[1][1]);
    }
    return 0;
}
*/

