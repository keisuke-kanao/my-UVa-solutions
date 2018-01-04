
/*
	UVa 477 - Points in Figures: Rectangles and Circles
	UVa 478 - Points in Figures: Rectangles, Circles, Triangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_477_478_Points_in_Figures_RCT.cpp
*/

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class shape {
public:
	shape() {}
	virtual ~shape() {}
	virtual bool is_inside(double x, double y) const = 0;
};

class rectangle : public shape {
private:
	double left_, top_, right_, bottom_;

public:
	rectangle(double left, double top, double right, double bottom) :
		left_(left), top_(top), right_(right), bottom_(bottom) {}
	virtual bool is_inside(double x, double y) const {return x > left_ && x < right_ && y > bottom_ && y < top_;}
};

class circle : public shape {
private:
	double x_, y_, radius_;

public:
	circle(double x, double y, double radius) :
		x_(x), y_(y), radius_(radius) {}
	virtual bool is_inside(double x, double y) const {return (x - x_) * (x - x_) + (y - y_) * (y - y_) < radius_ * radius_;}
};

class triangle : public shape {
private:
	double x1_, y1_, x2_, y2_, x3_, y3_;

	static double cross_product(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		return x1 * y2 - y1 * x2 + y1 * x3 - x1 * y3 + x2 * y3 - x3 * y2;
	}

public:
	triangle(double x1, double y1, double x2, double y2, double x3, double y3) :
		x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3) {}
	virtual bool is_inside(double x, double y) const;
};

bool triangle::is_inside(double x, double y) const
{
	const double epsilon = numeric_limits<float>::epsilon();
	double cp1 = cross_product(x1_, y1_, x2_, y2_, x, y), cp2 = cross_product(x2_, y2_, x3_, y3_, x, y),
		cp3 = cross_product(x3_, y3_, x1_, y1_, x, y);
	return cp1 > epsilon && cp2 > epsilon && cp3 > epsilon || cp1 < -epsilon && cp2 < -epsilon && cp3 < -epsilon;
}

int main()
{
	char c;
	vector<shape*> shapes;
	while (true) {
		cin >> c;
		if (c == '*')
			break;
		else if (c == 'r') {
			double l, t, r, b;
			cin >> l >> t >> r >> b;
			shapes.push_back(new rectangle(l, t, r, b));
		}
		else if (c == 'c') {
			double x, y, r;
			cin >> x >> y >> r;
			shapes.push_back(new circle(x, y, r));
		}
		else {
			double x1, y1, x2, y2, x3, y3;
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			shapes.push_back(new triangle(x1, y1, x2, y2, x3, y3));
		}
	}
	size_t nr_shapes = shapes.size();
	for (int p = 1; ; p++) {
		double x, y;
		cin >> x >> y;
		if (x == 9999.9 && y == 9999.9)
			break;
		bool contained = false;
		for (size_t i = 0; i < nr_shapes; i++)
			if (shapes[i]->is_inside(x, y)) {
				contained = true;
				cout << "Point " << p << " is contained in figure " << i + 1 << endl;
			}
		if (!contained)
			cout << "Point " << p << " is not contained in any figure\n";
	}
	for (size_t i = 0; i < nr_shapes; i++)
		delete shapes[i];
	return 0;
}

