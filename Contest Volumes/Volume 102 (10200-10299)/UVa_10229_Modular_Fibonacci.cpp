
/*
	UVa 10229 - Modular Fibonacci

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10229_Modular_Fibonacci.cpp
*/

#include <iostream>
using namespace std;

/*
long long conquer_fibonacci(long n){
long long i,h,j,k,t;
i=h=1;
j=k=0;
while(n>0){
if(n%2==1){
t=j*h;
j=i*h + j*k +t;
i=i*k + t;
}
t=h*h;
h=2*k*h + t;
k=k*k + t;
n=(long) n/2;}
return j;}
*/

int main()
{
	int n, m;
	while (cin >> n >> m) {
		m = 1 << m; // 2^m
		long long i = 1, h = 1, j = 0, k = 0, t;
		for ( ; n > 0; n /= 2) { // calculate Fn mod 2^m in O(log2(n))
			if (n & 1) {
				t = j * h % m;
				j = i * h % m + j * k % m + t;
				i = i * k % m + t;
			}
			t = h * h % m;
			h = 2 * k * h % m + t;
			k = k * k % m + t;
		}
		cout << j % m << endl;
	}
	return 0;
}

