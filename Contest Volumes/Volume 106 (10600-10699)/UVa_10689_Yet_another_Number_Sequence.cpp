
/*
	UVa 10689 - Yet another Number Sequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10689_Yet_another_Number_Sequence.cpp

	This problem is similar to 10229 - Modular Fibonacci.
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

long long Fibonacci(int n, int m)
{
	long long i = 1, h = 1, j = 0, k = 0, t;
	for ( ; n > 0; n /= 2) { // calculate Fn mod m in O(log2(n))
		if (n & 1) {
			t = j * h % m;
			j = i * h % m + j * k % m + t;
			i = i * k % m + t;
		}
		t = h * h % m;
		h = 2 * k * h % m + t;
		k = k * k % m + t;
	}
	return j /* % m */;
}

int main()
{
	const int last_m[] = {1, 10, 100, 1000, 10000};
	int t;
	cin >> t;
	while (t--) {
		int a, b, n, m;
		cin >> a >> b >> n >> m;
		m = last_m[m];
		int last_m_fn;
		if (!n)
			last_m_fn = a % m;
		else if (n == 1)
			last_m_fn = b % m;
		else
			last_m_fn = (Fibonacci(n - 1, m) * a % m + Fibonacci(n, m) * b % m) % m;
		cout << last_m_fn << endl;
	}
	return 0;
}

