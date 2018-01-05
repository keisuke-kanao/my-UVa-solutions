
/*
	UVa 10898 - Combo Deal

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10898_Combo_Deal.cpp

	This is the first submitted solution, rank = 64.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_items_max = 6, nr_combos_max = 8;
int nr_items, nr_combos, prices[nr_items_max], quantities[nr_items_max];
struct combo {
	int quantities_[nr_items_max];
	int price_;
} combos[nr_combos_max];

const int quantity_min = 0, quantity_max = 9;
int min_payments[1000000 /* (quantity_max - quantity_min + 1)^nr_items_max */ ];
	// min_payments[i] is the min. payment for quantities where 
	// i = quantities[0] * 10^0 + quantities[1] * 10^1 + quantities[2] * 10^2 + ... + quantities[nr_items] * 10^(nr_items - 1)]

const int pow10s[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

int get_index(int quantities[])
{
	int index = 0;
	for (int i = 0; i < nr_items; i++)
		index += quantities[i] * pow10s[i];
	return index;
}

int combo_deal(int quantities[])
{
	int pi = get_index(quantities);
	if (min_payments[pi] != -1)
		return min_payments[pi];
	int payment = 0;
	for (int i = 0; i < nr_items; i++)
		payment += prices[i] * quantities[i];
	for (int i = 0; i < nr_combos; i++) {
		combo& c = combos[i];
		int j;
		for (j = 0; j < nr_items; j++)
			if (c.quantities_[j] > quantities[j])
				break;
		if (j == nr_items) { // the combo can be applied
			for (j = 0; j < nr_items; j++)
				quantities[j] -= c.quantities_[j];
			payment = min(payment, combo_deal(quantities) + c.price_);
			for (j = 0; j < nr_items; j++)
				quantities[j] += c.quantities_[j];
		}
	}
	return min_payments[pi] = payment;
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
			for (int i = 0; i < nr_items; i++)
				scanf("%d", &quantities[i]);
			memset(min_payments, -1, sizeof(int) * pow10s[nr_items]);
			printf("%d\n", combo_deal(quantities));
		}
	}
	return 0;
}

