// std

#include <bits/stdc++.h>

#define N 2005
#define M 200005
#define mod 1000000007

using namespace std;

int m, n, p, k;
int f[N][N];
int Max[N];
vector<int> A, B;

int power(int x, int y) {
	int sum = 1;
	for (; y; y >>= 1) {
		if (y & 1) {
			sum = 1ll * sum * x % mod;
		}
		x = 1ll * x * x % mod;
	}
	return sum;
}

int work0() {
	int h[N] = {0}, s = 0;
	for (int i = 0; i < m; i++) {
		for (int j = A[i]; j <= B[i]; j++) {
			h[j] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!h[i]) {
			++s;
		}
	}
	return power(2, s);
}

void add(int &x, int y) {
	x += y;
	if (x >= mod) {
		x-=mod;
	}
}

int work1() {
	static int f[N] = {0};
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		add(f[i], f[i-1]);
		add(f[max(Max[i], i)], f[i-1]);
	}
	return f[n];
}

int count() {
	m = A.size();
 	if (k == 0) return work0();
	for (int i = 0; i < m; i++) {
	  for (int j = A[i]; j <= B[i]; j++) {
			Max[j] = max(Max[j], B[i]);
		}
	}
	if (k == 1) return work1();
	f[0][0] = 1;
	for (int i = 0; i < n; i++) {
	  for (int j = 0; j <= n; j++) {
		  if (f[i][j]) {
		   	if (i+1 == j) {
					add(f[i+1][0], f[i][j]);
				} else {
					add(f[i+1][j], f[i][j]);
				}
		   	if (j != 0) {
		   	  if (Max[i+1] <= j) {
						add(f[j][0], f[i][j]);
					} else {
						add(f[j][Max[i+1]], f[i][j]);
					}
				} else {
				 	if (Max[i+1] <= i+1) {
						add(f[i+1][0], f[i][j]);
					} else {
						add(f[i+1][Max[i+1]], f[i][j]);
					}
				}
	    }
		}
	}
	return f[n][0];
}

int main() {
	// freopen("read.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	while (m--) {
		int x, y;
	  scanf("%d %d", &x, &y);
	  A.push_back(x);
		B.push_back(y);
	}
	printf("%d\n", count());
}
