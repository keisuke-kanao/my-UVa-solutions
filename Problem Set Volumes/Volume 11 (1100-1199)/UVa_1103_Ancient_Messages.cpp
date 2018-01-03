
/*
	UVa 1103 - Ancient Messages

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1103_Ancient_Messages.cpp
*/

#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <cstdio>
#include <cctype>
using namespace std;

const int nr_dirs = 4;
const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
const char hieroglyph_characters[] = {0, 'W', 'A', 'K', 'J', 'S', 'D'};

const int H_max = 200, W_max = 50;
int image[H_max + 2][W_max * 4 + 2];

void bfs_black_pixels(int rows, int columns, int sr, int sc, int nr)
{
	image[sr][sc] = nr;
	queue< pair<int, int> > q;
	q.push(make_pair(sr, sc));
	while (!q.empty()) {
		pair<int, int> u = q.front();
		q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = u.first + dirs[i].first, c = u.second + dirs[i].second;
			if (r >= 0 && r < rows && c >= 0 && c < columns && image[r][c] == 1) {
				image[r][c] = nr;
				q.push(make_pair(r, c));
			}
		}
	}
}

void bfs_white_pixels(int rows, int columns, int sr, int sc, int nr, vector< set<int> >& hieroglyphs)
{
	image[sr][sc] = nr;
	queue< pair<int, int> > q;
	q.push(make_pair(sr, sc));
	while (!q.empty()) {
		pair<int, int> u = q.front();
		q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = u.first + dirs[i].first, c = u.second + dirs[i].second;
			if (r >= 0 && r < rows && c >= 0 && c < columns) {
				if (image[r][c] == 0) {
					image[r][c] = nr;
					q.push(make_pair(r, c));
				}
				else if (image[r][c] > 0)
					hieroglyphs[image[r][c] - 2].insert(nr);
			}
		}
	}
}

int main()
{
	const int nr_pixels = 4;
	for (int case_nr = 1; ; case_nr++) {
		int H, W;
		scanf("%d %d", &H, &W);
		if (!H)
			break;
		for (int i = 1; i <= H; i++) {
			char s[W_max + 1];
			scanf("%s", s);
			image[i][0] = 0;
			for (int j = 0, k = 1; j < W; j++, k += nr_pixels) {
				int p = (isdigit(s[j])) ? s[j] - '0' : s[j] - 'a' + 10;
				for (int l = 0, b = 8; l < nr_pixels; l++, b >>= 1)
					image[i][k + l] = (p & b) ? 1 : 0;
			}
			image[i][W * nr_pixels + 1] = 0;
		}
		W = W * nr_pixels + 2;
		for (int j = 0; j < W; j++)
			image[0][j] = image[H + 1][j] = 0;
		H += 2;
#ifdef DEBUG
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
				printf("%d", image[i][j]);
			putchar('\n');
		}
#endif
		int nr_hieroglyphs = 0;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				if (image[i][j] == 1) {
					bfs_black_pixels(H, W, i, j, nr_hieroglyphs + 2);
					nr_hieroglyphs++;
				}
		int nr_white_areas = 0;
		vector< set<int> > hieroglyphs(nr_hieroglyphs);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				if (image[i][j] == 0) {
					bfs_white_pixels(H, W, i, j, -(nr_white_areas + 1), hieroglyphs);
					nr_white_areas++;
				}
#ifdef DEBUG
		printf("hieroglyphs: %d\n", nr_hieroglyphs);
		for (int i = 0; i < nr_hieroglyphs; i++)
			printf("  %d: %u\n", i, hieroglyphs[i].size());
		printf("white areas: %d\n", nr_white_areas);
#endif
		vector<char> codes;
		for (int i = 0; i < nr_hieroglyphs; i++)
			codes.push_back(hieroglyph_characters[hieroglyphs[i].size()]);
		sort(codes.begin(), codes.end());
		printf("Case %d: ", case_nr);
		for (int i = 0; i < codes.size(); i++)
			putchar(codes[i]);
		putchar('\n');
	}
	return 0;
}

