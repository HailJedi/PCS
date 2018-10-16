#include <bits/stdc++.h>

#define N 2005
#define M 200005
#define mod 1000000007

using namespace std;

int m, n, p, k;
int f[N][N];
int AL[N], AR[N], Max[N];
string L, R;

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
	for (int i = 1; i <= m; i++) {
		for (int j = AL[i]; j <= AR[i]; j++) {
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
	for (int i = 1; i <= m; i++) {
	  for (int j = AL[i]; j <= AR[i]; j++) {
			Max[j] = max(Max[j], AR[i]);
		}
	}
	int f[N] = {0};
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		add(f[i], f[i-1]);
		add(f[max(Max[i], i)], f[i-1]);
	}
	return f[n];
}

int count(int n,vector<int> A,vector<int> B,int k) {
	m = A.size();
  for (int i = 1; i <= m; i++) {
 		AL[i] = A[i-1];
		AR[i] = B[i-1];
	}
 	if (k == 0) return work0();
 	if (k == 1) return work1();
	for (int i = 1; i <= m; i++) {
	  for (int j = AL[i]; j <= AR[i]; j++) {
			Max[j] = max(Max[j], AR[i]);
		}
	}
	f[0][0] = 1;
	for (int i = 0; i < n; i++) {
	  for (int j = 0; j <= n; j++) {
		  if (f[i][j]) {
		   	if (j == i+1) {
					add(f[i+1][0], f[i][j]);
				} else {
					add(f[i+1][j], f[i][j]);
				}
		   	if (j) {
		   	  int Next = max(Max[i+1], j);
		   	  if (Next == j) {
						add(f[j][0], f[i][j]);
					} else {
						add(f[j][Next], f[i][j]);
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
	freopen("read.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	vector<int> L, R;
	while (m--) {
		int x, y;
	  scanf("%d %d", &x, &y);
	  L.push_back(x);
		R.push_back(y);
	}
	printf("%d\n", count(n, L, R, k));
}
