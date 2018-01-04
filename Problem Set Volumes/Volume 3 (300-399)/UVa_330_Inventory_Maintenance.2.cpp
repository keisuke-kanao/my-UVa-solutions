
/*
	UVa 330 - Inventory Maintenance

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_330_Inventory_Maintenance.cpp

	Another accepted solution.
*/

#include <string>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 15, nr_items_max = 200;

struct item {
	bool deleted_;
	double cost_, price_;
	int in_stock_;
};

int main()
{
	map<string, item> items;
	char activity[nr_chars_max + 1], name[nr_chars_max + 1];
	int quantity;
	double profit = 0.0;
	while (scanf("%s", activity) != EOF && activity[0] != '*') {
		switch (activity[0]) {
		case 'n':
		{
			item it;
			scanf("%s %lf %lf", name, &it.cost_, &it.price_);
			it.deleted_ = false, it.in_stock_ = 0;
			items[name] = it;
		}
			break;
		case 'b':
			scanf("%s %d", name, &quantity);
			items[name].in_stock_ += quantity;
			break;
		case 's':
		{
			scanf("%s %d", name, &quantity);
			item& it = items[name];
			it.in_stock_ -= quantity;
			profit += (it.price_ - it.cost_) * quantity;
		}
			break;
		case 'd':
		{
			scanf("%s", name);
			item& it = items[name];
			it.deleted_ = true;
            profit -= it.cost_ * it.in_stock_;
            it.in_stock_ = 0;
		}
			break;
		default: // report
			double total = 0.0;
			puts("                  INVENTORY REPORT");
			puts("Item Name     Buy At      Sell At      On Hand        Value");
			puts("---------     ------      -------      -------        -----");
			for (map<string, item>::const_iterator ii = items.begin(), ie = items.end(); ii != ie; ++ii) {
				const item& it = ii->second;
				if (!it.deleted_) {
					double value = it.cost_ * it.in_stock_;
					printf("%-10s %9.2lf %12.2lf %12d %12.2lf\n", ii->first.c_str(), it.cost_, it.price_, it.in_stock_, value);
					total += value;
				}
			}
            puts("------------------------");
            printf("Total value of inventory                       %12.2lf\n", total);
            printf("Profit since last report                       %12.2lf\n\n", profit);
            profit = 0.0;
			break;
		}
	}
	return 0;
}

