
/*
	UVa 11507 - Bender B. Rodriguez Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11507_Bender_B_Rodriguez_Problem.cpp
*/

#include <cstdio>

struct point {
	int x_, y_, z_;
	point() {}
	point(int x, int y, int z) : x_(x), y_(y), z_(z) {}
	point(const point& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}
};

struct rotation {
	const char* s_;
	int matrix_[3][3];
} rotations[] = {
	{"+y", {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}}}, // Rz(90 degree)
	{"-y", {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}}}, // Rz(-90 degree)
	{"+z", {{0, 0, -1}, {0, 1, 0}, {1, 0, 0}}}, // Ry(-90 degree)
	{"-z", {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}}}  // Ry(90 degree)
};

point rotate_point(const point& o, const point& p, const char* s)
{
	int ri = (s[1] - 'y') * 2;
	if (s[0] == '-')
		ri++;
	const rotation& r = rotations[ri];
	point q(p.x_ - o.x_, p.y_ - o.y_, p.z_ - o.z_);
	point result;
	result.x_ = o.x_ + r.matrix_[0][0] * q.x_ + r.matrix_[0][1] * q.y_ + r.matrix_[0][2] * q.z_;
	result.y_ = o.y_ + r.matrix_[1][0] * q.x_ + r.matrix_[1][1] * q.y_ + r.matrix_[1][2] * q.z_;
	result.z_ = o.z_ + r.matrix_[2][0] * q.x_ + r.matrix_[2][1] * q.y_ + r.matrix_[2][2] * q.z_;
	return result;
}

int main()
{
	while (true) {
		int L;
		scanf("%d", &L);
		if (!L)
			break;
		// remember the last (left-most) point and the next to last point
		// rotate both points around j-th point
		char s[2];
		point p(L - 1, 0, 0), q(L, 0, 0);
		L--;
		while (true) {
			scanf("%s", s);
			if (s[0] != 'N') { // "No"
				q = rotate_point(p, q, s);
				break;
			}
			if (L == 1)
				break;
			L--; p.x_--;
		}
#ifdef DEBUG
		printf("(%d, %d, %d) (%d, %d, %d)\n", p.x_, p.y_, p.z_, q.x_, q.y_, q.z_);
#endif
		while (L-- > 1) {
			point o(L, 0, 0);
			scanf("%s", s);
			if (s[0] != 'N') {
				p = rotate_point(o, p, s);
				q = rotate_point(o, q, s);
#ifdef DEBUG
				printf("(%d, %d, %d) (%d, %d, %d)\n", p.x_, p.y_, p.z_, q.x_, q.y_, q.z_);
#endif
			}
		}
		if (p.x_ != q.x_)
			printf((p.x_ < q.x_) ? "+x\n": "-x\n");
		else if (p.y_ != q.y_)
			printf((p.y_ < q.y_) ? "+y\n": "-y\n");
		else
			printf((p.z_ < q.z_) ? "+z\n": "-z\n");
	}
	return 0;
}

