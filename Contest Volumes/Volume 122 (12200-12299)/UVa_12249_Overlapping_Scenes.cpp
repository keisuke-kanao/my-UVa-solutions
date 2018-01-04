
/*
	UVa 12249 - Overlapping Scenes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12249_Overlapping_Scenes.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	const int n_max = 6, nr_chars_max = 10;
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		int scenes[n_max], scene_string_lengths[n_max], min_length = 0;
		char scene_strings[n_max][nr_chars_max + 1], merged_string[n_max * nr_chars_max + 1];
		for (int i = 0; i < n; i++) {
			scenes[i] = i;
			scanf("%s", scene_strings[i]);
			scene_string_lengths[i] = strlen(scene_strings[i]);
			min_length += scene_string_lengths[i];
		}
		do {
			strcpy(merged_string, scene_strings[scenes[0]]);
			for (int i = 1; i < n; i++) {
				int j, k = strlen(merged_string);
				for (j = 0; j < k; j++)
					if (!memcmp(&merged_string[j], &scene_strings[scenes[i]][0], k - j))
						break;
				strcat(merged_string, &scene_strings[scenes[i]][k - j]);
			}
#ifdef DEBUG
			printf("%s\n", merged_string);
#endif
			min_length = min(min_length, static_cast<int>(strlen(merged_string)));
		} while (next_permutation(scenes, scenes + n));
		printf("Case %d: %d\n", t, min_length);
	}
	return 0;
}

