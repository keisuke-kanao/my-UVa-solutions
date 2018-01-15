
/*
	UVa 10375 - Choose and divide

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10375_Choose_and_divide.cpp
*/

#include <iostream>
#include <utility>
#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

/*
	C(p, q) / C(r, s) = (p! * s! * (r - s)!) / (q! * r! * (p - q)!)
*/

const int nr_facts = 3; // number of factorials

bool multiply_by_partial_factorial(pair<int, int>& pfact, double result_max, double& result)
{
	int i;
	for (i = pfact.first; i <= pfact.second; ) {
		result *= static_cast<double>(i++);
		if (result > result_max)
			break;
	}
	pfact.first = i;
	return pfact.first > pfact.second;
}

bool divide_by_partial_factorial(pair<int, int>& pfact, double result_min, double& result)
{
	int i;
	for (i = pfact.first; i <= pfact.second; ) {
		result /= static_cast<double>(i++);
		if (result < result_min)
			break;
	}
	pfact.first = i;
	return pfact.first > pfact.second;
}

int main()
{
	int p, q, r, s;
	while (cin >> p >> q >> r >> s) {
		int dvd_facts[nr_facts] = {p, s, r - s}, // dividend factorials
			dvs_facts[nr_facts] = {q, r, p - q}; // divisor factorials
		sort(dvd_facts, dvd_facts + nr_facts);
		sort(dvs_facts, dvs_facts + nr_facts);
		int i, j, nr_dvd_pfacts = 0, nr_dvs_pfacts = 0;
		pair<int, int> dvd_pfacts[nr_facts], dvs_pfacts[nr_facts]; // dividend/divisor partial factorials
		for (i = 0; i < nr_facts; i++) {
			if (dvd_facts[i] > dvs_facts[i])
				dvd_pfacts[nr_dvd_pfacts++] = make_pair(dvs_facts[i] + 1, dvd_facts[i]);
			else if (dvd_facts[i] < dvs_facts[i])
				dvs_pfacts[nr_dvs_pfacts++] = make_pair(dvd_facts[i] + 1, dvs_facts[i]);
		}
		i = j = 0;
		double result = 1.0;
		const double result_min = numeric_limits<float>::min(), result_max = numeric_limits<float>::max();
		do {
			if (i < nr_dvd_pfacts && multiply_by_partial_factorial(dvd_pfacts[i], result_max, result))
				i++;
			if (j < nr_dvs_pfacts && divide_by_partial_factorial(dvs_pfacts[j], result_min, result))
				j++;
		} while (i < nr_dvd_pfacts || j < nr_dvs_pfacts);
		printf("%.5lf\n", result);
	}
	return 0;
}

