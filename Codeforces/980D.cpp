#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 5010;
int n;
int e[N], f[N], ans[N], cnt[N];
map<int, int> mp;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &e[i]);
		int s = e[i] > 0 ? 1 : -1;
		e[i] *= s;
		for (int j = 2; j * j <= e[i]; j++) if (e[i] % (j*j) == 0) {
			int c = 0;
			while (e[i] % (j*j) == 0) e[i] /= (j*j);
		}
		e[i] *= s;
		f[i] = e[i];
	}
	puts("");
	sort(f+1, f+1+n);
	int p = 0;
	f[0] = INF;
	for (int i = 1; i <= n; i++) {
        if (f[i] != f[i-1]) mp[f[i]] = ++p;
	}
	int zero = INF;
	for (int i = 1; i <= n; i++) {
        if (e[i] == 0) zero = mp[e[i]];
        e[i] = mp[e[i]];
	}
	for (int l = 1; l <= n; l++) {
		int ct = 0;
		bool zr = true;
		for (int r = l; r <= n; r++) {
            if (e[r] != zero) zr = false;
            if (cnt[e[r]] != l && e[r] != zero) cnt[e[r]] = l, ct++;
            ans[ct]++;
            if (zr) ans[1]++;
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
