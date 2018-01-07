
/*
	UVa 107 - The Cat in the Hat

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_107_The_Cat_in_the_Hat.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	Given the height of the initial cat and the number of worker cats (of height one),
	consider a N-ary tree with its height h, then:
		N^h = number of worker cats
		(N + 1)^h = height of the intial cat
	Or,
		N = pow(number_of_worker_cats, 1 / h)
		N + 1 = pow(height_of_the_intial_cat, 1 / h)
	Once N and h are known, then:
		number of cats that are not working = 1 + N + N^2 + ... + N^(h - 1)
		height of the stack of cats = N^h * 1 + N^(h - 1) * (N + 1) + N^(h - 2) * (N + 1)^2 + ... + 1 * (N + 1)^h
*/

int power_root(int base, int exponent)
{
	int pr = static_cast<int>(ceil(pow(static_cast<double>(base), 1.0 / static_cast<double>(exponent))));
	if (pow(static_cast<double>(pr), static_cast<double>(exponent)) == base)
		return pr;
	else {
		pr--;
		return (pow(static_cast<double>(pr), static_cast<double>(exponent)) == base) ? pr : -1;
	}
}

void get_tree_N_and_height(int nr_worker_cats, int initial_cat_height, int& tree_N, int& tree_height)
{
	if (nr_worker_cats == 1) {
		tree_N = 1;
		int p = 1;
		for (tree_height = 0; ; tree_height++, p *= 2)
			if (p == initial_cat_height)
				break;
	}
	else {
		for (tree_height = 1; ; tree_height++) {
			if ((tree_N = power_root(nr_worker_cats, tree_height)) == -1)
				continue;
			if (pow(static_cast<double>(tree_N + 1), static_cast<double>(tree_height)) == initial_cat_height)
				break;
		}
	}
}

int main()
{
	while (true) {
		int initial_cat_height, nr_worker_cats;
		cin >> initial_cat_height >> nr_worker_cats;
		if (!initial_cat_height && !nr_worker_cats)
			break;
		int tree_N, tree_height;
		get_tree_N_and_height(nr_worker_cats, initial_cat_height, tree_N, tree_height);
		long long nr_cats_not_working = 0;
		for (int i = 0; i < tree_height; i++) {
			nr_cats_not_working *= tree_N;
			nr_cats_not_working++;
		}
		long long cat_stack_height = initial_cat_height;
		for (int i = 0, n = 1; i < tree_height; i++) {
			initial_cat_height /= tree_N + 1;
			n *= tree_N;
			cat_stack_height += initial_cat_height * n;
		}
		cout << nr_cats_not_working << ' ' << cat_stack_height << endl; 
	}
	return 0;
}

