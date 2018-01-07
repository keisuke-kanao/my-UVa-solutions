
/*
	UVa 10499 - The Land of Justice

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10499_The_Land_of_Justice.cpp
*/

#include <iostream>
using namespace std;

/*
	from Our Quest to Solve the UVa ICPC Online Problem Set :: UVa Solutions
		(http://www.questtosolve.com/browse.php?pid=10499)
	Solution Description:
		The sphere starts with 4*pi*r^2 surface area. We can ignore r (assume it's 1), so we have 4*pi SA. 
		When you cut a wedge out of a sphere, that wedge has two new faces, each one of which is a semicircle. 
		Therefore, the wedge has a whole circle of new SA, or another pi of SA.

		So, if we cut the sphere into N wedges, we have 4*pi + N*pi as the total SA. 
		N*pi / 4*pi is then the profit. This reduces to N/4 as the profit. 
		But we want a percentage, so multiply by 100 and get (25*N)% as the final answer.

		Don't forget the special case where N = 1, and make sure you use longs. 
		N might be in the int range, but 25*N is not.
*/

int main()
{
	while (true) {
		long long n;
		cin >> n;
		if (n < 0)
			break;
		cout << ((n == 1) ? 0 : 25 * n) << "%\n";
	}
	return 0;
}


