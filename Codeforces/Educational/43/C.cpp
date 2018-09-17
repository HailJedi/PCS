#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
struct segment {
	int l, r, id;
	segment() {}
	bool operator < (const segment &s) const {
		if (l != s.l) return l < s.l;
		return r > s.r;
	}
} seg[N];
int n;

bool lie_in(int i, int j) {
	return seg[i].r >= seg[j].r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> seg[i].l >> seg[i].r;
		seg[i].id = i;
	}
	sort(seg, seg+n);
	for (int i = 0; i < n-1; i++) {
		if (lie_in(i, i+1)) {
			cout << seg[i+1].id + 1 << ' ' << seg[i].id + 1 << endl;
			return 0;
		}
	}
	puts("-1 -1");

	return 0;
}