
/*
	UVa 10071 - Back to High School Physics

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10071_Back_to_High_School_Physics.cpp
*/

/*
A particle has initial velocity and constant acceleration. 
If its velocity after certain time is v then what will its displacement be in twice of that time?

	For an unitial velocity of u and a constant acceleration of a,
	velocity of v at the time of t is:
		v = u + a * t
	Then,
		a = (v - u) / t
	Displacement of s for the twice of time is:
		s = u * (2 * t) + (1 / 2) * a * (2 * t)^2
		  = 2 * v * t
*/

#include <iostream>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	int v, t;
	while (cin >> v >> t)
		cout << 2 * v * t << endl;
	return 0;
}

