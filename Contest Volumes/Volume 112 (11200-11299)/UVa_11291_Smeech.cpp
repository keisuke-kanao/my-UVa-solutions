
/*
	UVa 11291 - Smeech

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11291_Smeech.cpp
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

double smeech(char* ss, char** se)
{
	while (isspace(*ss))
		ss++;
	if (*ss == '(') {
		ss++;
		double p = strtod(ss, se);
		ss = *se;
		double e1 = smeech(ss, se);
		ss = *se;
		double e2 = smeech(ss, se);
		ss = *se;
		while (*ss != ')')
			ss++;
		*se = ss + 1;
		return p * (e1 + e2) + (1.0 - p) * (e1 - e2);
	}
	else
		return strtod(ss, se);
}

int main()
{
	while (true) {
		string s;
		getline(cin, s);
		if (s == "()")
			break;
		char* ss = new char[s.length() + 1];
		strcpy(ss, s.c_str());
		char* se;
		printf("%.2lf\n", smeech(ss, &se));
		delete[] ss;
	}
	return 0;
}

