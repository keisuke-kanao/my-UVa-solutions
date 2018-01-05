
/*
	UVa 10898 - Combo Deal

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10898_Combo_Deal.cpp

	This is the second submitted solution, rank = 24.
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_items_max = 6, nr_combos_max = 8;

int nr_items, nr_combos, prices[nr_items_max], quantities[nr_items_max], min_payment;
struct combo {
	int quantities_[nr_items_max];
	int price_;
} combos[nr_combos_max];

void combo_deal(int ci, int payment)
{
	if (ci == nr_combos) {
		for (int i = 0; i < nr_items; i++)
			if (quantities[i])
				payment += prices[i] * quantities[i];
			min_payment = min(min_payment, payment);
	}
	else {
		combo& c = combos[ci];
		for (int i = 1; ; i++) {
			int j;
			for (j = 0; j < nr_items; j++)
			if (c.quantities_[j] * i > quantities[j])
				break;
			if (j < nr_items || payment + c.price_ * i >= min_payment)
				break;
			for (j = 0; j < nr_items; j++)
				quantities[j] -= c.quantities_[j] * i;
			combo_deal(ci + 1, payment + c.price_ * i);
			for (j = 0; j < nr_items; j++)
				quantities[j] += c.quantities_[j] * i;
		}
		if (payment < min_payment)
			combo_deal(ci + 1, payment);
	}
}

int main()
{
	while (scanf("%d", &nr_items) != EOF) {
		for (int i = 0; i < nr_items; i++)
			scanf("%d", &prices[i]);
		scanf("%d", &nr_combos);
		for (int i = 0; i < nr_combos; i++) {
			combo& c = combos[i];
			for (int j = 0; j < nr_items; j++)
				scanf("%d", &c.quantities_[j]);
			scanf("%d", &c.price_);
		}
		int nr_orders;
		scanf("%d", &nr_orders);
		while (nr_orders--) {
			min_payment = 0;
			for (int i = 0; i < nr_items; i++) {
				scanf("%d", &quantities[i]);
				min_payment += prices[i] * quantities[i];
			}
			int payment = 0;
			combo_deal(0, payment);
			printf("%d\n", min_payment);
		}
	}
	return 0;
}

