/*
Created 2018-10-23
"Minimum path"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;

int n, k;
char mat[N][N];
int f[N][N];
bool tag[N][N];

void update(int &x, int y) {
	if (x == -1 || x > y) {
		x = y;
	}
}

int main() {
	// freopen("read.in", "r", stdin);	
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%s", mat[i]+1);
	}
	memset(f, -1, sizeof f);
	int p = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int buf = mat[i][j] != 'a';
			if (i == 1 && j == 1) {
				f[i][j] = buf;
			}
			if (i-1 >= 1) {
				update(f[i][j], f[i-1][j] + buf);
			}
			if (j-1 >= 1) {
				update(f[i][j], f[i][j-1] + buf);
			}
			if (f[i][j] <= k) {
				p = max(p, i+j);
			}
		}
	}
	for (int i = 2; i <= p; i++) {
		printf("a");
	}
	for (int i = p; i >= 1; i--) {
		if (i <= n && p - i >= 1) {
			int j = p - i;
			if (f[i][j] <= k) {
				tag[i][j] = true;
			}
		}
	}
	tag[0][1] = tag[1][0] = true;
	for (p++; p <= 2*n; p++) {
		char mn = 'z';
		for (int i = p; i >= 1; i--) {
			if (i <= n && p - i >= 1 && p - i <= n) {
				int j = p - i;
				if (tag[i-1][j] || tag[i][j-1]) {
					mn = min(mn, mat[i][j]);
				}
			}
		}
		printf("%c", mn);
		for (int i = p; i >= 1; i--) {
			if (i <= n && p - i >= 1) {
				int j = p - i;
				if ((tag[i-1][j] || tag[i][j-1]) && mn == mat[i][j]) {
					tag[i][j] = true;
				}
			}
		}
	}
	printf("\n");
	return 0;
}	

/*
aaad
aade
acad
bcde
*/
