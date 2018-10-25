/*
Created 2018-10-25
"USACO 2011 November Contest, Gold Division
Problem 2. Binary Sudoku"
😠
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int f[10][1<<9][1<<3];
int row[10];
char sudo[9];

void update(int &x, int y) {
	if (x > y) {
 		x = y;
	}
}

int main() {
	freopen("bsudoku.in", "r", stdin);
	freopen("bsudoku.out", "w", stdout);
	for (int i = 1; i <= 9; i++) {
		scanf("%s", sudo);
		for (int j = 0; j < 9; j++) {
			row[i] |= ((sudo[j] == '1') << j);
		}
	}
	memset(f, 0x3f, sizeof f);
	f[0][0][0] = 0;
	for (int r = 0; r < 9; r++) {
		for (int cs = 0; cs < (1 << 9); cs++) {
			for (int sd = 0; sd < (1 << 3); sd++) {
				if (f[r][cs][sd] != INF && (r % 3 || sd == 0)) {
					for (int tog = 0; tog < (1 << 9); tog++) {
						int nrs = tog ^ row[r+1];
						int ncs = nrs ^ cs;
						int sd0 = ((sd >> 0) & 1) ^ __builtin_parity(nrs & (7 << 0));
						int sd1 = ((sd >> 1) & 1) ^ __builtin_parity(nrs & (7 << 3));
						int sd2 = ((sd >> 2) & 1) ^ __builtin_parity(nrs & (7 << 6));
						int nsd = (sd0 << 0) | (sd1 << 1) | (sd2 << 2);
						if (__builtin_parity(nrs) == 0) {
							update(f[r+1][ncs][nsd], f[r][cs][sd] + __builtin_popcount(tog));
						}
					}
				}
			}
		}
	}
	printf("%d\n", f[9][0][0]);
	return 0;
}
