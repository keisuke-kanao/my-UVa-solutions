
/*
	UVa 12541 - Birthdates

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12541_Birthdates.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_persons_max = 100, nr_name_chars_max = 15;

struct person {
	char name_[nr_name_chars_max + 1];
	int date_, month_, year_;

	bool operator<(const person& p) const
	{
		if (year_ < p.year_)
			return true;
		else if (year_ > p.year_)
			return false;
		else {
			if (month_ < p.month_)
				return true;
			else if (month_ > p.month_)
				return false;
			else
				return date_ < p.date_;
		}
	}
} persons[nr_persons_max];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s %d %d %d", persons[i].name_, &persons[i].date_, &persons[i].month_, &persons[i].year_);
	sort(persons, persons + n);
	printf("%s\n%s\n", persons[n - 1].name_, persons[0].name_);
}

