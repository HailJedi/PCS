#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int c[N];
int n, m, p, k, x, h, d;
vector<int> pth[2][N], lis[2][N];
int bit[N], lf[N], rf[N];

int lowbit(int x) {
	return x & -x;
}

int ask(int p) {
	int ret = 0;
	for (; p > 0; p -= lowbit(p)) {
		ret = max(ret, bit[p]);
	}
	return ret;
}

void change(int p, int v) {
	for (; p <= m; p += lowbit(p)) {
		bit[p] = max(bit[p], v);
	}
}

void run(int s, int d, int t, int *f) {
	int ls = 0;
	memset(bit, 0, sizeof(int)*(m+1));
	for (int i = s, j = 2; j <= n; j++, i += d) {
		for (int k = 0; k < pth[t][i].size(); k++) {
			int ak = ask(pth[t][i][k])+1;
			ls = max(ls, ak);
			lis[t][i].push_back(ak);
		}
		for (int k = 0; k < lis[t][i].size(); k++) {
			change(pth[t][i][k], lis[t][i][k]);
		}
		f[i] = !t ? i - 1 - ls : n - i - ls;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> p >> k;
	m++;
	for (int i = 1; i <= p; i++) {
		cin >> x >> h >> d;
		pth[d^1][x+d].push_back(m-h);
	}
	run(2, 1, 0, lf);
	run(n-1, -1, 1, rf);
	int ans = 0, buf = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		while (j <= n && lf[j] + rf[i] <= k) {
			j++;
		}
		ans = max(ans, j - i);
		if (!lf[i] && !rf[i]) {
			buf++;
		}
	}
	cout << ans - buf << endl;
	return 0;
}