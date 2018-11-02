#include <bits/stdc++.h>

using namespace std;

const int N = 5e3+5;

struct XXX {
	int h, v, s;
	XXX() {}
} x[2][N];

int n;
long long A, B, C;
int mx, mn;

bool cmph(XXX &p1, XXX &p2) {
	return p1.h < p2.h;
}

bool cmps(XXX &p1, XXX &p2) {
	return p1.s < p2.s;
}

int check(int id, int d) {
	return mn <= x[id][d].v && x[id][d].v <= mx;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> A >> B >> C;
	for (int i = 1; i <= n; i++) {
		cin >> x[0][i].h >> x[0][i].v;
		x[0][i].s = A * x[0][i].h + B * x[0][i].v;
		x[1][i] = x[0][i];
	}
	sort(x[0] + 1, x[0] + 1 + n, cmph);
	sort(x[1] + 1, x[1] + 1 + n, cmps);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		mn = x[0][i].v, mx = mn + C / B;
		int lp = 0, rp = 0, cnt = 0;
		for (int j = 1; j <= n; j++) {
			while (rp < n && x[1][rp + 1].s <= A * x[0][j].h + B * x[0][i].v + C) {
				cnt += check(1, ++rp);
			}
			while (lp < n && x[0][lp + 1].h < x[0][j].h) {
				cnt -= check(0, ++lp);
			}
			ans = max(ans, cnt);
		}
	}
	cout << ans << endl;
	return 0;
}