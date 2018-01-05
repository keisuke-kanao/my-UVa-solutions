
/*
	UVa 10114 - Loansome Car Buyer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10114_Loansome_Car_Buyer.cpp
*/

#include <cstdio>

const int nr_months_max = 100;

struct depreciation {
	int month_;
	double percentage_;
} depreciations[nr_months_max + 1];

int main()
{
	while (true) {
		int m, d, nr_months, nr_depreciations;
		double payment, loan, car;
		scanf("%d %lf %lf %d", &nr_months, &payment, &loan, &nr_depreciations);
		if (nr_months < 0)
			break;
		for (d = 0; d < nr_depreciations; d++)
			scanf("%d %lf", &depreciations[d].month_, &depreciations[d].percentage_);
		car = loan + payment; // initial payment
		payment = loan / nr_months; // payment per month
		for (m = 0, d = 0; m <= nr_months; m++) {
			if (m)
				loan -= payment;
			if (d < nr_depreciations - 1 && depreciations[d + 1].month_ == m)
				d++;
			car -= car * depreciations[d].percentage_;
#ifdef DEBUG
			printf("%d %lf %lf %lf\n", m, depreciations[d].percentage_, loan, car);
#endif
			if (car > loan)
				break;
		}
		printf("%d %s\n", m, ((m == 1) ? "month" : "months"));
	}
	return 0;
}

