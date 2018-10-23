/*
Created 2018-10-23
"Minimum path"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int N = 2000 + 5;
const int B = 998244353;

int n, k;
char mat[N][N];
ull hsh[N][N];
int pre[N][N];
int f[N][N];

void print(int i, int j) {
	if (pre[i][j] != 0) {
		if (pre[i][j] == 1) {
			print(i-1, j);
		} else {
			print(i, j-1);
		}
	}
	printf("%c", mat[i][j]);
}

bool update(ull &x, ull y, char c) {
	if (x == -1 || x > y * B + c - 'a') {
		x = y * B + c - 'a';
		return true;
	}
	return false;
}

void update(int &x, int y) {
	if (x == -1 || x > y) {
		x = y;
	}
}

int main() {
	freopen("read.in", "r", stdin);	
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%s", mat[i]+1);
	}
	memset(f, -1, sizeof f);
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
				mat[i][j] = 'a';
			}
			hsh[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i-1 >= 1 && update(hsh[i][j], hsh[i-1][j], mat[i][j])) {
				pre[i][j] = 1;
			}
			if (j-1 >= 1 && update(hsh[i][j], hsh[i][j-1], mat[i][j])) {
				pre[i][j] = -1;
			}
		}
	}
	print(n, n);
	printf("\n");
	return 0;
}	

/*
aaad
aade
acad
bcde
*/
