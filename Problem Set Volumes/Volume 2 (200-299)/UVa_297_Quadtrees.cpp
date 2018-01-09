
/*
	UVa 297 - Quadtrees

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_297_Quadtrees.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int nr_quadrants = 4;
const int nr_pixels = 1024;

struct Quadtree
{
	char type_; // 'p' for parent node, 'f' or black quadrant, 'e' for white quadrant
	Quadtree* quadrants_[nr_quadrants];

	Quadtree(char type);
	~Quadtree();
};

Quadtree::Quadtree(char type) : type_(type)
{
	for (int i = 0; i < nr_quadrants; i++)
		quadrants_[i] = NULL;
}

Quadtree::~Quadtree()
{
	for (int i = 0; i < nr_quadrants; i++)
		delete quadrants_[i];
}

Quadtree* build_quadtree(const char*& representation)
{
	Quadtree* qt = new Quadtree(*representation++);
	if (qt->type_ == 'p') {
		for (int i = 0; i < nr_quadrants; i++)
			qt->quadrants_[i] = build_quadtree(representation);
	}
	return qt;
}

int get_image(Quadtree* qt, int pixels_per_quadrant, int result)
{
	if (qt->type_ == 'p') {
		for (int i = 0; i < nr_quadrants; i++)
			result += get_image(qt->quadrants_[i], pixels_per_quadrant / nr_quadrants, 0);
	}
	else if (qt->type_ == 'f')
		result += pixels_per_quadrant;
	return result;
}

int add_image(Quadtree* one, Quadtree* other, int pixels_per_quadrant, int result)
{
	char one_type = one->type_, other_type = other->type_;
	if (one_type == 'f' || other_type == 'f')
		result += pixels_per_quadrant;
	else if (one_type == 'e' && other_type == 'e')
		;
	else if (one_type == 'p' && other_type == 'p') {
		for (int i = 0; i < nr_quadrants; i++)
			result += add_image(one->quadrants_[i], other->quadrants_[i], pixels_per_quadrant / nr_quadrants, 0);
	}
	else if (one_type == 'p') {
		for (int i = 0; i < nr_quadrants; i++)
			result += get_image(one->quadrants_[i], pixels_per_quadrant / nr_quadrants, 0);
	}
	else {
		for (int i = 0; i < nr_quadrants; i++)
			result += get_image(other->quadrants_[i], pixels_per_quadrant / nr_quadrants, 0);
	}
	return result;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		string one_representation, other_representation;
		cin >> one_representation >> other_representation;
		const char *p = one_representation.c_str(), *q = other_representation.c_str();
		Quadtree *one_tree = build_quadtree(p), *other_tree = build_quadtree(q);
		int result = add_image(one_tree, other_tree, nr_pixels, 0);
		cout << "There are " << result << " black pixels.\n";
		delete one_tree;
		delete other_tree;
	}
	return 0;
}

