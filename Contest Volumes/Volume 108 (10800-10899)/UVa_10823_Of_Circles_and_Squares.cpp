
/*
	UVa 10823 - Of Circles and Squares

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10823_Of_Circles_and_Squares.cpp
*/

/*
In object oriented programming, the vector of object instances would be created and 
the in method of each object instance would be called with the query point in question.
The below round function is from the UVa OJ Board (https://uva.onlinejudge.org/board/viewtopic.php?f=30&t=7724).
*/

#include <cstdio>

const int R_max = 100;

struct object {
	int x_, y_; // center or lower left corner
	int length_; // radius or side length
	int r_, g_, b_;
	virtual int in(int px, int py) const = 0;
		// return porasitive value if (px, py) is inside the object, 0 if (px, py) is on the boundary of the object
		// negative value if (px, py) is outside of the object
};

struct circle : public object {
	virtual int in(int px, int py) const;
} circles[R_max];

struct square : public object {
	virtual int in(int px, int py) const;
} squares[R_max];

int circle::in(int px, int py) const
{
	return length_ * length_ - (px - x_) * (px - x_) - (py - y_) * (py - y_);
}

int square::in(int px, int py) const
{
	if (px == x_ || px == x_ + length_)
		return (py >= y_ && py <= y_ + length_) ? 0 : -1;
	else if (py == y_ || py == y_ + length_)
		return (px >= x_ && px <= x_ + length_) ? 0 : -1;
	else
		return (px > x_ && px < x_ + length_ && py > y_ && py < y_ + length_) ? 1 : -1;
}

int round(int p, int q)   /* Rounds fraction p/q */
{
	return (p / q) + (((2 * (p % q)) >= q) ? 1 : 0);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int R, P;
		scanf("%d %d", &R, &P);
		int nr_circles = 0, nr_squares = 0;
		while (R--) {
			char type[8];
			scanf("%s", type);
			if (type[0] == 'C') { // "CIRCLE"
				circle& c = circles[nr_circles++];
				scanf("%d %d %d %d %d %d", &c.x_, &c.y_, &c.length_, &c.r_, &c.g_, &c.b_);
			}
			else { // "SQUARE"
				square& s = squares[nr_squares++];
				scanf("%d %d %d %d %d %d", &s.x_, &s.y_, &s.length_, &s.r_, &s.g_, &s.b_);
			}
		}
		printf("Case %d:\n", t);
		while (P--) {
			int px, py;
			scanf("%d %d", &px, &py);
			int nr_objects = 0, r = 0, g = 0, b = 0;
			for (int i = 0; i < nr_circles; i++) {
				const circle& c = circles[i];
				int result = c.in(px, py);
				if (!result) {
					nr_objects = 1;
					r = g = b = 0;
#ifdef DEBUG
					printf("on the boundary of circle: %d %d %d\n", c.x_, c.y_, c.length_);
#endif
					break;
				}
				else if (result > 0) {
					nr_objects++;
					r += c.r_, g += c.g_, b += c.b_;
#ifdef DEBUG
					printf("in the circle: %d %d %d\n", c.x_, c.y_, c.length_);
#endif
				}
			}
			if (nr_objects == 1 && !r && !g && !b) // point is on the boundary of an object
				;
			else {
				for (int i = 0; i < nr_squares; i++) {
					const square& s = squares[i];
					int result = s.in(px, py);
					if (!result) {
						nr_objects = 1;
						r = g = b = 0;
#ifdef DEBUG
					printf("on the boundary of square: %d %d %d\n", s.x_, s.y_, s.length_);
#endif
						break;
					}
					else if (result > 0) {
						nr_objects++;
						r += s.r_, g += s.g_, b += s.b_;
#ifdef DEBUG
					printf("in the square: %d %d %d\n", s.x_, s.y_, s.length_);
#endif
					}
				}
			}
			if (nr_objects)
				printf("(%d, %d, %d)\n",
					round(r, nr_objects), round(g, nr_objects), round(b, nr_objects));
/*
				printf("(%.0lf, %.0lf, %.0lf)\n", static_cast<double>(r) / nr_objects,
					static_cast<double>(g) / nr_objects, static_cast<double>(b) / nr_objects);
*/
			else
				puts("(255, 255, 255)");
		}
		if (t < T)
			putchar('\n');
	}
	return 0;
}

